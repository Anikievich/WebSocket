//
// Created by aniki on 8/26/23.
//

#include "Server.h"

Server::Server(int port) {


    addr_this.sin_family = AF_INET;
    addr_this.sin_addr.s_addr = INADDR_ANY;
    addr_this.sin_port = htons(port);

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock<0) {
        perror("Server: socket was not created");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    err = bind(sock, (struct sockaddr*)&addr_this, sizeof(addr_this));
    if(err<0){
        perror("Server: cannot connect socket");
        exit(EXIT_FAILURE);
    }

    listen(sock, 3);
    FD_ZERO(&active_set);
    FD_SET(sock, &active_set);
    read_set = active_set;

    socket_ = new Socket(sock, addr_from, read_set, active_set);
}

void Server::run() {
    ClientHandler handler(socket_);
    handler.run();
}

Server::~Server() {
    delete socket_;
    socket_ = nullptr;
}

