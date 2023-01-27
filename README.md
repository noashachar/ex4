# Assignment 4: KNN classifications from CSV files

This project is a C++ implementation of a server-client program using TCP sockets and threads.


Server
---
The server is designed to support multiple clients by using threads. It supports the following functionalities:
- Uploading CSV files for the KNN classifier to train on.
- Uploading CSV files for the KNN classifier to predict labeles for.
- Changing the KNN params (k, metric).
- Display the results.
- Download the results in the background (mutliple simultaneous downloads supported).

Client
---
The client has two threads:

The main thread reads from both stdin and the socket.

Every message from stdin in simply sent to the server; however messages from the server are trickier:

- If a message starts with a dollar symbol, then it is for a download (the message will contain some filename and some line to append to it); the main thread will simply push that message to a thread-safe queue.

- If a message starts with a bang symbol, then it's a call for some file to be uploaded.

- If a message doesn't start with a special symbol, it'll simply be printed to the user.

The client's second thread is responsible for popping messages from the queue, and handling them by appending lines into the appropriate files.

Mutliple concurrent downloads are supported.

How to Run
---

To run the server and client, follow these steps:

```
make
./server.out <port>
./client.out <ip> <port>
```

You'll be greeted be a menu:
```
Welcome to the KNN Classifier Server. Please choose an option:
1. upload an unclassified csv data file
2. algorithm settings
3. classify data
4. display results
5. download results
8. exit
```

Type a number and hit *\<Enter\>*.

---

If you hit `8` to exit, and there are still downloads in the background, you'll see

`
waiting for download(s) to finish...
`

And the client will close itself a couple of seconds later when all downloads are finished.


---

All the menu optoins are pretty self explainatory, except for command 2 🙃

To change the algorithm settings, type `2`, then `k metric`, where k is a number, and k is name of a metric;

The following values for `metrics` are supported:
-   `MAN` for Manhattan distance
-   `AUC` for Euclidean distance
-   `CHB` for Chebyshev distance
-   `MIN` for Minkowski distance
-   `CAN` for Canberra distance


## Limitations

The input data must be in CSV format, with the class label as the last column of each row.

The server and the client only run on UNIX based systems, due to use of pthread.
