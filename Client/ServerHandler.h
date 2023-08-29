//
// Created by aniki on 8/26/23.
//

#ifndef SERVER_CLIENTHANDLER_H
#define SERVER_CLIENTHANDLER_H
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
#include "Socket.h"
#include "Package.h"
#include "Person.h"
#include "Table.h"


class ServerHandler {
public:
    explicit ServerHandler(int sock);
    void run();
private:
    void start();
   // Person *DisplayHandler(struct Table &client1);
    void readSocket();
private:
    int fd, pac;
    Package packet_;
    Package packet_type;
    size_t pack_size;
    size_t sizeDisplay;

    std::vector<Person> person_vec;
    struct Table client;
};


#endif //SERVER_CLIENTHANDLER_H
