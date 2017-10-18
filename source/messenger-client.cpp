#include <string>
#include <iostream>
#include <vector>
#include <helpers.hpp>
#include <formatter.hpp>
#include "messenger-client.hpp"
#include "communicator.hpp"
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <unistd.h>

messenger_client::messenger_client(const std::string &host, int port) : _sc(host, port), _t_death(false), _user("") {
    _sc.get_connection();
    _event_fd = eventfd(0, 0);
}

bool messenger_client::connect(const std::string &username) {
    std::string formatted = formatter::format_connection(username);
    _sc.send_msg(formatted);
    std::string response = _sc.receive_msg();
    int response_type = formatter::parse(response, TYPE_CLIENT);
    return response_type == C_OK;
}

void messenger_client::_start_incoming() {
    sockets::communicator com = _sc.expose_communicator();
    int fd = _sc.expose_fd();
    struct epoll_event event{};
    struct epoll_event *events;
    int event_fd = epoll_create(2);
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    events = new epoll_event[2];
    int n = epoll_wait(event_fd, events, 2, -1);
    for (int i = 0; i < n; i++) {
        if (_event_fd == events[i].data.fd) {
            std::terminate();
        } else if (fd == events[i].data.fd) {
            std::string msg = com.receive_msg();
            _io_mtx.lock();
            std::cout << _user << msg << std::endl;
            _io_mtx.unlock();
        }
    }
}

void messenger_client::_start_outgoing() {
    while (true) {
        std::string msg;
        std::cin >> msg;

        std::string trimmed = helpers::trim(msg);
        if (msg[0] == '/') {
            if (msg.find("/connect") == 0) {
                if (_user.empty()) {
                    std::cout << "Already connected to a user" << std::endl;
                }
                std::string s;
                std::vector<std::string> v = helpers::split(msg, ' ');
                if (v.size() != 2) {
                    std::cout << "Unknown sequence. Type /help for help" << std::endl;
                    continue;
                } else {
                    msg = formatter::format_connection(v[1]);
                    _user = v[1];
                }
            } else if (msg.find("/disconnect") == 0) {
                std::string formatted = formatter::format_disconnect();
                _sc.send_msg(formatted);
                std::terminate();
            } else if (msg.find("/use") == 0) {
                std::vector<std::string> v = helpers::split(msg, ' ');
                if (v.size() != 2) {
                    std::cout << "Unknown sequence. Type /help for help" << std::endl;
                    continue;
                } else {
                    msg = formatter::format_use(v[1]);
                }
            }
        } else {
            msg = formatter::format_msg(msg);
        }

        _sc.send_msg(msg);
    }
}

void messenger_client::start() {
    if (!_sc.is_open()) {
        std::cerr << "Unable to open connection to host. Please try again later \n "
                "or visit https://github.com/kostaskol/texty for instructions on how to host a conversation yourself"
                  << std::endl;
    }

    std::thread _incoming(&messenger_client::_start_incoming, this);
    std::thread _outgoing(&messenger_client::_start_outgoing, this);
    std::unique_lock<std::mutex> t_death_lock(_t_death_mtx);
    _t_death_cond.wait(t_death_lock);
    // Notify both threads that they should die
    uint64_t u = 2;
    ssize_t s = write(_event_fd, &u, sizeof(uint64_t));
    if (s != sizeof(uint64_t)) {
        std::cerr << "Some error has occurred" << std::endl;
        exit(-1);
    }
    _incoming.join();
    _outgoing.join();
}

bool messenger_client::is_open() {
    return _sc.is_open();
}