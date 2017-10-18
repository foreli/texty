#include "messenger-host.hpp"

void messenger_host::_manage_fd(int fd);

messenger_host::messenger_host(int port, int num_workers = 10) : _sh(port) {
    _workers = new std::thread[num_workers];
}

messenger_host::~messenger_host() {
    delete[] _workers;
}

void messenger_host::start() {
    _sh.get_connections(300);
    int fd = _sh.expose_fd();
}