all: server client main

client: TcpClient.cpp TcpClient.h
	 g++ -std=c++11 TcpClient.cpp -o client.out

client.o: TcpClient.cpp
	 g++ -std=c++11 -c TcpClient.cpp

server: server.o distances.o utils.o knn.o
	 g++ -std=c++11 server.o distances.o utils.o knn.o -lpthread -o server.out

server.o: server.cpp server.h
	 g++ -std=c++11 -c server.cpp -lpthread

distances.o: distances.cpp distances.h
	 g++ -std=c++11 -c distances.cpp

utils.o: utils.cpp utils.h
	 g++ -std=c++11 -c utils.cpp

knn.o: knn.cpp knn.h
	 g++ -std=c++11 -c knn.cpp

clean:
	 rm -f *.o




Command.o: Command.cpp Command.h
	 g++ -std=c++11 -c command.cpp

CmdAlgoSettings.o: CmdAlgoSettings.h CmdAlgoSettings.cpp
	 g++ -std=c++11 -c CmdAlgoSettings.cpp

CmdClassify.o: CmdClassify.cpp CmdClassify.h
	 g++ -std=c++11 -c CmdClassify.cpp

CmdDownloadResults.o: CmdDownloadResults.cpp CmdDownloadResults.h
	 g++ -std=c++11 -c CmdDownloadResults.cpp

CmdDisplayResults.o: CmdDisplayResults.cpp CmdDisplayResults.h
	 g++ -std=c++11 -c CmdDisplayResults.cpp

CmdUploadCsv.o: CmdUploadCsv.cpp CmdUploadCsv.h
	 g++ -std=c++11 -c CmdUploadCsv.cpp

main.o: main.cpp
	 g++ -std=c++11 -c main.cpp

main: main.o Command.o CmdAlgoSettings.o CmdClassify.o CmdDownloadResults.o CmdDisplayResults.o CmdUploadCsv.o
	 g++ -std=c++11 main.o Command.o CmdAlgoSettings.o CmdClassify.o CmdDownloadResults.o CmdDisplayResults.o CmdUploadCsv.o -o main.out