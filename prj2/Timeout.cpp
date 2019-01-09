#include "Timeout.h"

Timeout::Timeout(Server* server) {
    this->server = server;
}

void Timeout::wait(bool& indicator) {
    indicator = false;
    pthread_t wait_thread;
    pthread_create(&wait_thread, nullptr, count, nullptr);
    pthread_join(wait_thread, nullptr);
    if (!indicator) {
        server->stop();
        exit(0);
    }
}

void *Timeout::count(void *arg) {
    //usleep(30000000);
    usleep(10000000);
    pthread_exit(nullptr);
}
