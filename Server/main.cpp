#include "Server.h"


int main() {
    Server server_(9090);
    server_.run();
    return 0;
}
