#ifndef TEXTY_MESSENGER_HPP
#define TEXTY_MESSENGER_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include "msocket_client.hpp"

class messenger_client {
private:
    sockets::socket_client _sc;
    std::mutex _io_mtx;

    std::mutex _t_death_mtx;
    std::condition_variable _t_death_cond;
    bool _t_death;
    int _t_death_num;

    int _event_fd;

    std::string _user;

    void _start_incoming();
    void _start_outgoing();
public:
    messenger_client(const std::string &host, int port);

    bool connect(const std::string &username);

    void start();

    bool is_open();
};


#endif //TEXTY_MESSENGER_HPP
