#include <iostream>
#include "server.h"

int main(int argc, char *argv[]) {
    Server *server = new Server();
    int port = DEFAULT_PORT;
    if (argc>1) {
        port = atoi(argv[1]);
    }
    int ret = server->start(port);
    if (ret==0) {
        server->loop();
        server->stop();
    }
    delete server;

    return 0;
}