all: server.out client.out

client.out: client.o threadSafeQueue.o
	g++ -std=c++11 client.o threadSafeQueue.o -pthread -o client.out

client.o: TcpClient.cpp TcpClient.h
	g++ -std=c++11 -c TcpClient.cpp -o client.o

threadSafeQueue.o: threadSafeQueue.cpp
	g++ -std=c++11 -c threadSafeQueue.cpp -o threadSafeQueue.o

server.out: server.o distances.o utils.o knn.o StandardIO.o SocketIO.o Command.o CmdUploadCsv.o CmdDownloadResults.o CmdDisplayResults.o CmdClassify.o CmdAlgoSettings.o cli.o DefaultIO.h
	g++ -std=c++11 -pthread server.o distances.o utils.o knn.o StandardIO.o SocketIO.o  Command.o CmdUploadCsv.o CmdDownloadResults.o CmdDisplayResults.o CmdClassify.o CmdAlgoSettings.o cli.o -o server.out

cli.o: cli.cpp cli.h
	g++ -std=c++11 -c cli.cpp

server.o: server.cpp server.h
	g++ -std=c++11 -c -pthread server.cpp

distances.o: distances.cpp distances.h
	g++ -std=c++11 -c distances.cpp

utils.o: utils.cpp utils.h
	g++ -std=c++11 -c utils.cpp

knn.o: knn.cpp knn.h
	g++ -std=c++11 -c knn.cpp

StandardIO.o: StandardIO.cpp StandardIO.h
	g++ -std=c++11 -c StandardIO.cpp

SocketIO.o: SocketIO.cpp SocketIO.h
	g++ -std=c++11 -c SocketIO.cpp

Command.o: Command.cpp Command.h
	g++ -std=c++11 -c Command.cpp

CmdAlgoSettings.o: CmdAlgoSettings.cpp CmdAlgoSettings.h
	g++ -std=c++11 -c CmdAlgoSettings.cpp

CmdClassify.o: CmdClassify.cpp CmdClassify.h
	g++ -std=c++11 -c CmdClassify.cpp

CmdDisplayResults.o: CmdDisplayResults.cpp CmdDisplayResults.h
	g++ -std=c++11 -c CmdDisplayResults.cpp

CmdDownloadResults.o: CmdDownloadResults.cpp CmdDownloadResults.h
	g++ -std=c++11 -c CmdDownloadResults.cpp

CmdUploadCsv.o: CmdUploadCsv.cpp CmdUploadCsv.h
	g++ -std=c++11 -c CmdUploadCsv.cpp

clean:
	rm -f *.o