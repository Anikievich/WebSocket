//
// Created by aniki on 8/26/23.
//

#include "Client.h"

Client::Client(int port, int hport) {

    hostinfo = gethostbyname("127.0.0.1");
    if (hostinfo == NULL) {
        fprintf(stderr, "Unknown host\n");
        exit(EXIT_FAILURE);
    }
    addr_to.sin_family = hostinfo->h_addrtype;
    addr_to.sin_port = htons(hport);
    addr_to.sin_addr = *(struct in_addr *) hostinfo->h_addr;

    addr_this.sin_family = AF_INET;
    addr_this.sin_addr.s_addr = INADDR_ANY;
    addr_this.sin_port = htons(port);

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Server: socket was not created");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof(opt));

    err = connect(sock, (struct sockaddr *) &addr_to, sizeof(addr_to));
    if (err < 0) {
        std::cerr << "Client: cannot connect socket" << std::endl;
        exit(EXIT_FAILURE);
    }

}

void Client::run() const {
    ServerHandler handler(sock);
    handler.run();
}

Client::~Client() {
}

