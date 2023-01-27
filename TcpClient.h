#ifndef EX4_TCPCLIENT_H
#define EX4_TCPCLIENT_H
#include <vector>
#include <string>
#include "threadSafeQueue.cpp"

void sendToServer(int sock, const std::string &message);

struct ArgsForDownloadWorker
{
    ThreadSafeQueue<std::string> *q;
    /**
     * q will contain messages like:
     * name-of-file.txt: some line to append to the file
     * name-of-file.txt: another line to append to the file
     * different-file.txt: some line some text blah blah
     * name-of-file.txt: !done (this is a special message meaning - close the file)
     */

    int *noDownloadsHappening;
    // the downloader thread will change this variable to communicate with the main thread
};

void downloadingWorker(struct ArgsForDownloadWorker args);

void uploadFileToServer(const char *path, int sock);

#endif //EX4_TCPCLIENT_H