#ifndef SOCKET_SOCKET_H
#define SOCKET_SOCKET_H

#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <cstring>
#include <vector>

namespace mstd {
    class socket_host {
    private:
        int _port;
        bool _opened;
        bool _bound;
        int _sock_fd;
        int _client_fd;
    public:
        explicit socket_host(int port);

        socket_host(const socket_host &) = delete;

        bool is_open();

        void get_connections(int max_queue = 5);

        void close_client();

        void stop();

        bool send_msg(std::string message, int flags = 0);

        std::string receive_msg();
    };

}

#endif //SOCKET_SOCKET_H
