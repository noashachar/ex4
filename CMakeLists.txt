cmake_minimum_required(VERSION 3.23)
project(EX3)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

set(Sources
        Command.cpp
        SocketIO.cpp
        StandardIO.cpp
        TcpClient.cpp
        distances.cpp
        knn.cpp
        server.cpp
        utils.cpp
)

set(Headers
        Command.h
        DefaultIO.h
        SocketIO.h
        StandardIO.h
        TcpClient.h
        distances.h
        knn.h
        server.h
        utils.h
)

add_executable(ex4 ${Sources} ${Headers})
