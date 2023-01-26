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

void send_to_server(int sock, const std::string &message)
{
  // also send the \0 so that empty strings can be transmitted!
  int bytes_sent = send(sock, message.c_str(), message.size() + 1, 0);
  if (bytes_sent <= 0)
  {
    std::cerr << "error occurred while writing to server" << std::endl;
    exit(EXIT_FAILURE);
  }

  // to disable msg batching (Nagle's Algorithm)
  std::this_thread::sleep_for(std::chrono::milliseconds(75));
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
      send_to_server(sock, line);
    }
  }
  else
  {
    std::cout << "could not read file: " << path << std::endl;
  }

  static const std::string DONE = "!done";
  send_to_server(sock, DONE);
}

struct DownloadThread_Args {
  std::string path;
  int sock;
  std::ofstream* filePtr;

  DownloadThread_Args(std::string path, int sock, std::ofstream* filePtr) 
    : path(path), sock(sock), filePtr(filePtr) { }
};

void downloadFileFromServer(DownloadThread_Args args)
{
  const std::string this_thread_prefix = "$" + args.path + ": ";
  char buffer[4096];

  std::ofstream& file = *args.filePtr;

  while (true)
  {
    int bytes_received = recv(args.sock, buffer, sizeof(buffer), MSG_PEEK);
    if (bytes_received <= 0)
    {
      std::cerr << "error while downloading: recv failed" << std::endl;
      break;
    }

    // the message is promised to end with '\0' by the server!
    const std::string raw_msg(buffer);

    // if it doesn't start with our prefix, it's not for us
    if (raw_msg.rfind(this_thread_prefix, 0) != 0) continue;

    // pop the message from the queue
    int raw_msg_len = recv(args.sock, buffer, sizeof(buffer), 0);
    if (raw_msg_len <= 0)
    {
      std::cerr << "error while downloading: recv with no flags failed" << std::endl;
      break;
    }

    const std::string msg = raw_msg.substr(this_thread_prefix.length());

    if (msg == "!done") break;

    if (args.filePtr->is_open()) *args.filePtr << msg << std::endl;
  }

  if (args.filePtr->is_open()) args.filePtr->close();

  delete args.filePtr;
}

void handleSpecialCommands(int sock, const char *cmd, std::vector<std::thread*>& downloads)
{
  static const std::string UPLOAD_PREFIX = "!upload:";

  if (startsWith(cmd, UPLOAD_PREFIX))
  {
    const char *path = cmd + UPLOAD_PREFIX.length();
    uploadFileToServer(path, sock);
  }

  static const std::string DOWNLOAD_PREFIX = "!download:";

  if (startsWith(cmd, DOWNLOAD_PREFIX))
  {
    std::string path = cmd + DOWNLOAD_PREFIX.length();

    std::ofstream* filePtr = new std::ofstream(path);
    if (!filePtr->is_open())
    {
      std::cerr << "error: cannot write to: `" << path << "`" << std::endl;
      // no return,
      // becuase the thread must pull its "$download messages from the socket queue
    }

    auto args = DownloadThread_Args(path, sock, filePtr);
    downloads.push_back( new std::thread(downloadFileFromServer, args) );
  }
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
    std::cout << "failed to create socket" << std::endl;
    exit(EXIT_FAILURE);
  }

  hostent *server = gethostbyname(argv[1]);
  if (server == nullptr)
  {
    std::cout << "failed to resolve hostname" << std::endl;
    exit(EXIT_FAILURE);
  }

  sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(std::stoi(argv[2]));
  memcpy(&server_address.sin_addr.s_addr, server->h_addr, server->h_length);

  if (connect(sock, (sockaddr *)&server_address, sizeof(server_address)) < 0)
  {
    std::cout << "failed to connect to server" << std::endl;
    exit(EXIT_FAILURE);
  }

  fd_set readfds, writefds;
  int max_fd = std::max(sock, STDIN_FILENO) + 1;

  std::vector<std::thread*> downloads;
  std::string input;

  while (true)
  {
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);

    // Add the socket and standard input to the read set
    FD_SET(sock, &readfds);
    FD_SET(STDIN_FILENO, &readfds);

    // Add the socket to the write set if there is data to send
    if (!input.empty())
    {
      FD_SET(sock, &writefds);
    }

    // Wait for data to be available on any of the file descriptors
    int result = select(max_fd, &readfds, &writefds, nullptr, nullptr);
    if (result < 0)
    {
      std::cout << "error occurred during select" << std::endl;
      break;
    }

    if (FD_ISSET(STDIN_FILENO, &readfds))
    {
      std::getline(std::cin, input);

      // normally it'd be set if there's something in std;
      // we want to set it even if the user has typed an empty line,
      // so that empty lines, too, will be sent to the server.
      if (input.empty()) FD_SET(sock, &writefds);
    
      else if (input == "8") break;
    }

    if (FD_ISSET(sock, &writefds))
    {
      send_to_server(sock, input);
      input.clear();
    }

    if (FD_ISSET(sock, &readfds))
    {
      char buffer[4096];
      int bytes_received = recv(sock, buffer, sizeof(buffer), MSG_PEEK);
      if (bytes_received <= 0)
      {
        // std::cout << "connection closed by server" << std::endl;
        exit(EXIT_FAILURE);
      }

      // the message is promised to end with '\0' by the server!

      if (buffer[0] == '$') continue;

      // pop the message from the queue
      if (recv(sock, buffer, sizeof(buffer), 0) <= 0)
      {
        std::cout << "error reading from server: recv with no flags failed" << std::endl;
        break;
      }

      if (buffer[0] == '!')
      {
        handleSpecialCommands(sock, buffer, downloads);
      }
      else
      {
        std::cout << buffer << std::endl;
      }
    }
  }

  // if we want to quit, let's just finish the downloads first
  // todo only print if some threads are still alive
  std::cout << "waiting for downloads to finish..." << std::endl;
  for (const auto downloadThread : downloads)
  {
    downloadThread->join();
    delete downloadThread;
  }

  close(sock);
  return 0;
}