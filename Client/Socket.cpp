//
// Created by aniki on 8/27/23.
//

#include "Socket.h"

Socket::Socket(int const &fd, struct sockaddr_in const& addr_from,fd_set &read_set, fd_set const &active_set){
    this->fd = fd;
    this->addr_from = addr_from;
    this->read_set = read_set;
    this->active_set = active_set;
}

Socket::Socket() {

}
