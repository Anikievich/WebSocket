//
// Created by aniki on 8/27/23.
//

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H
#include <arpa/inet.h>
#include <netdb.h>


struct Socket{
    Socket();
    Socket(int const &fd, struct sockaddr_in const& addr_from,fd_set &read_set, fd_set const &active_set);
    int fd;
    struct sockaddr_in addr_from{};
    fd_set read_set, active_set;
};


#endif //SERVER_SOCKET_H
