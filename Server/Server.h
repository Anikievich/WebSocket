//
// Created by aniki on 8/26/23.
//
#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <sys/time.h>
#include <cstring>
#include <sys/select.h>
#include <iostream>
#include <vector>
#include <thread>
#include <optional>
#include <algorithm>
#include <memory>
#include "ClientHandler.h"


class Server {
public:
    explicit Server(int port);
    void run();
    ~Server();
private:
    int sock;
    int err;

    struct sockaddr_in addr_from;
    struct sockaddr_in addr_this;
    fd_set  active_set, read_set;

    Socket *socket_;

};


#endif //SERVER_SERVER_H
