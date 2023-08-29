//
// Created by aniki on 8/26/23.
//
#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H
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
#include "ServerHandler.h"


class Client {
public:
    explicit Client(int port, int hport);
    void run() const;
    ~Client();
private:
    int sock;
    int err;

    struct sockaddr_in addr_to;
    struct sockaddr_in addr_this;
    struct hostent *hostinfo;

};


#endif //CLIENT_CLIENT_H
