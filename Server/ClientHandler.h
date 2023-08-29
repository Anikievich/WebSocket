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

#define NUM_THREAD 4
#define DELAY 10



class ClientHandler {
public:
    explicit ClientHandler(Socket const *socket);
    void run();
private:
    void start();
    Person *DisplayHandler(struct Table &client1);

private:
    int fd;
    struct sockaddr_in addr_from;
    fd_set  active_set, read_set;

    struct timeval tv;
    std::vector<std::shared_ptr<std::thread>> thread_vec;
    std::vector<Person> person_vec;
    Table client[FD_SETSIZE]{};
};


#endif //SERVER_CLIENTHANDLER_H
