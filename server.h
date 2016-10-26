
#ifndef DABURUJANPUSERVER_SERVER_H
#define DABURUJANPUSERVER_SERVER_H


const static int DEFAULT_PORT = 1234;

class Server {
public:
    explicit Server();
    int start(int port);
    void start() { start(DEFAULT_PORT); }
    void stop();
    ~Server() { if (isRunning()) stop(); }

    bool isRunning();
    void loop();

private:
    bool running = false;
    int server_sock;
    void accepting_loop();
  //  void *serve_request(void *arg);



};
void *serve_request(void *arg);

#endif //DABURUJANPUSERVER_SERVER_H
