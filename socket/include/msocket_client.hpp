#ifndef SOCKET_MSOCKET_CLIENT_H
#define SOCKET_MSOCKET_CLIENT_H

#include <string>
#include <vector>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <cstring>
#include "message.hpp"

namespace mstd {
    class socket_client {
    private:
        bool _opened;
        bool _host_found;
        int _sock_fd;
        struct sockaddr_in _serv;
    public:
        socket_client(std::string host, int port);

        bool get_connection();

        bool is_open();

        bool send_msg(std::string m, int flags = 0);

        std::string receive_msg(int flags = 0);

        void close_connection();
    };
}


#endif //SOCKET_MSOCKET_CLIENT_H
