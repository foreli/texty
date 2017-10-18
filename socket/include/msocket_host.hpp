#ifndef SOCKET_SOCKET_H
#define SOCKET_SOCKET_H

#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <cstring>
#include <vector>
#include "communicator.hpp"

namespace sockets {
    class socket_host {
    private:
        int _port;
        bool _opened;
        bool _bound;
        int _sock_fd;
        int _client_fd;
        communicator _communicator;
    public:
        explicit socket_host(int port);

        socket_host(const socket_host &) = delete;

        bool is_open();

        int get_connections(int max_queue = 5);

        void close_client();

        void stop();

        bool send_msg(std::string message);

        std::string receive_msg();

        int expose_fd();

        communicator &expose_communicator();
    };

}

#endif //SOCKET_SOCKET_H
