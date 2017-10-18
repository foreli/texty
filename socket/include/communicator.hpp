#ifndef SOCKET_COMMUNICATOR_HPP
#define SOCKET_COMMUNICATOR_HPP

namespace sockets {
    class communicator {
    private:
        int _fd;
        bool _set;
    public:
        communicator();

        explicit communicator(int fd);

        bool send_msg(const std::string &msg);

        std::string receive_msg();

        void set_fd(int fd);

        int get_fd();
    };
}

#endif //SOCKET_COMMUNICATOR_HPP
