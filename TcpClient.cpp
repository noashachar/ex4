#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <chrono>
#include <thread>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <deque>
#include <mutex>
#include <condition_variable>

const std::string
        CLOSE_SOCKET_PREFIX = "CLOSE_SOCKET:",
        UPLOAD_PREFIX = "!upload:";

std::vector<std::string> splitBy(const std::string &s, char delimiter)
{
    size_t pos_start = 0, pos_end;
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + 1;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

template <typename T>
class ThreadSafeQueue
{
private:
    std::deque<T> q;
    std::mutex m;
    std::condition_variable cv;

public:
    void push(T item)
    {
        std::unique_lock<std::mutex> lock(m);
        q.push_back(item);
        lock.unlock();
        cv.notify_one();
    }

    T pop()
    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [this]()
        { return !q.empty(); });
        T item = q.front();
        q.pop_front();
        return item;
    }
};

void sendToServer(int sock, const std::string &message)
{
    // also send the \0 so that empty strings can be transmitted!
    int bytes_sent = send(sock, message.c_str(), message.size() + 1, 0);
    if (bytes_sent <= 0)
    {
        std::cerr << "error occurred while writing to server" << std::endl;
        exit(EXIT_FAILURE);
    }

    // to disable msg batching (Nagle's Algorithm)
    // std::cout << "|| sent " << message << " || gonna sleep 100ms" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

struct ArgsForDownloadWorder
{
    ThreadSafeQueue<std::string> *q;
    // q will contains messages like:
    // name-of-file.txt: some line to append to the file
    // name-of-file.txt: another line to append to the file
    // different-file.txt: some line some text blah blah
    // name-of-file.txt: !done (this is a special message meaning - close the file)

    int *noDownloadsHappening;
    // the downloader thread will change this variable to communicate with the main thread
};

// runs in a separate thread
void downloadingWorker(struct ArgsForDownloadWorder args)
{
    int sock_to_close = 0;
    // the main thread will send us its socket number when the user wants to quit.
    // in that case, we will close the socket when there are no more downloads.

    std::unordered_map<std::string, std::ofstream *> openFiles;

    while (!sock_to_close || !openFiles.empty())
    {
        // block this thread until there's a message in it
        std::string msg = args.q->pop();

        if (msg.rfind(CLOSE_SOCKET_PREFIX, 0) == 0)
        {
            // the main threads signals we should start packing our stuff and leave.
            // we'll close the socket and exit as soon as all downloads are finished.
            sock_to_close = std::stoi(msg.substr(CLOSE_SOCKET_PREFIX.length()));
            continue;
        }

        // a message to us will look like this:
        // name-of-file.txt: some line to append to the file

        auto parts = splitBy(msg, ':');
        std::string filename = parts[0];
        std::string lineToAppend = parts[1].substr(1); // start after the space

        // if this file isn't already open
        if (openFiles.find(filename) == openFiles.end())
        {
            std::ofstream *file = new std::ofstream;
            file->open(filename);
            if (file->fail())
            {
                std::cerr << "error: cannot write to: " << filename << std::endl;
            }
            openFiles.emplace(filename, file);
        }

        std::ofstream *filePtr = openFiles[filename];

        if (lineToAppend == "!done")
        {
            if (filePtr->is_open())
            {
                filePtr->close();
            }
            delete openFiles[filename]; // the ofstream ptr has to be freed
            openFiles.erase(filename);  // reduce the map's size by one
        }

        else if (filePtr->is_open())
        {
            // the file might not be open if we had no permissions to write it
            *filePtr << lineToAppend << std::endl;
        }

        *args.noDownloadsHappening = openFiles.empty();
    }

    *args.noDownloadsHappening = true;
    close(sock_to_close);
    exit(EXIT_SUCCESS);
}

bool startsWith(const char *buffer, const std::string &prefix)
{
    return strncmp(buffer, prefix.c_str(), prefix.length()) == 0;
}

void uploadFileToServer(const char *path, int sock)
{
    std::string line;
    std::ifstream myfile;
    myfile.open(path);

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            sendToServer(sock, line);
        }
    }
    else
    {
        std::cout << "could not read file: " << path << std::endl;
    }

    static const std::string DONE = "!done";
    sendToServer(sock, DONE);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "usage: " << argv[0] << " hostname port" << std::endl;
        exit(EXIT_FAILURE);
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        std::cerr << "failed to create socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    hostent *server = gethostbyname(argv[1]);
    if (server == nullptr)
    {
        std::cerr << "failed to resolve hostname" << std::endl;
        exit(EXIT_FAILURE);
    }

    try
    {
        std::stoi(argv[2]);
    }
    catch (std::invalid_argument&)
    {
        std::cerr << "invalid port number" << std::endl;
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(std::stoi(argv[2]));
    memcpy(&server_address.sin_addr.s_addr, server->h_addr, server->h_length);

    if (connect(sock, (sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        std::cerr << "failed to connect to server..." << std::endl;
        std::cerr << "make sure that ip and port are correct, and that the server is up." << std::endl;
        exit(EXIT_FAILURE);
    }

    ThreadSafeQueue<std::string> q;
    int noDownloadsHappening = true;
    struct ArgsForDownloadWorder args = {&q, &noDownloadsHappening};
    std::thread download_thread(downloadingWorker, args);

    int user_wants_to_quit = false;
    // if this is true, stdin/stdout will stop echoing to/from the server,
    // and we'll exit the process as soon as the downloads thread finishes.

    while (true)
    {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);
        if (!user_wants_to_quit)
        {
            FD_SET(STDIN_FILENO, &readfds);
        }

        int max_fd = sock;
        select(max_fd + 1, &readfds, NULL, NULL, NULL);

        if (FD_ISSET(sock, &readfds))
        {
            char buffer[4096];
            int n = recv(sock, buffer, sizeof(buffer), 0);
            if (n == 0)
            {
                std::cerr << "connection closed by server" << std::endl;
                close(sock);
                exit(EXIT_FAILURE);
            }
            if (n < 0)
            {
                if (noDownloadsHappening)
                {
                    // we're probably here because the thread signaled us its done
                    // by closing the socket, hence causing our recv to fail
                    exit(EXIT_SUCCESS);
                }
                else
                {
                    std::cerr << "error reading from the server" << std::endl;
                    close(sock);
                    exit(EXIT_FAILURE);
                }
            }

            if (startsWith(buffer, UPLOAD_PREFIX)) // this implies (buffer[0] == '!')
            {
                const char *path = buffer + UPLOAD_PREFIX.length();
                uploadFileToServer(path, sock);
            }
            else if (buffer[0] == '$') // the msg is some line to append to some file
            {
                q.push(std::move(std::string(buffer + 1)));
            }
            else if (!user_wants_to_quit)
            {
                std::cout << buffer << std::endl;
            }
        }

        if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            std::string input;
            std::getline(std::cin, input);
            if (input == "8")
            {
                user_wants_to_quit = true;
                q.push(CLOSE_SOCKET_PREFIX + std::to_string(sock));
                if (!noDownloadsHappening)
                {
                    std::cout << "waiting for download(s) to finish..." << std::endl;
                }
            }
            else
            {
                sendToServer(sock, input);
            }
        }
    }
}
