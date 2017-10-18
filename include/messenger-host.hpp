#ifndef TEXTY_MESSENGER_HOST_HPP
#define TEXTY_MESSENGER_HOST_HPP

#include <mutex>
#include "msocket_host.hpp"
#include <condition_variable>
#include <queue>
#include <unordered_map>
#include <thread>

class messenger_host {
private:
    struct user_fd_map {
        int user;
        int fd;
    };
    sockets::socket_host _sh;
    std::mutex _q_mtx;
    std::condition_variable _q_empty_cond;
    bool _q_empty;
    std::queue<int> _fd_queue;

    std::mutex _um_mtx;

    // Maps user_ids to conversation_partner_ids and their descriptors
    std::unordered_map<int, std::shared_ptr<user_fd_map>> _connections;

    // TODO: Write what this does after checking to see if it works
    std::vector<std::shared_ptr<user_fd_map>> _user_fd_map;

    // user_id  -> user_name map
    std::unordered_map<int, std::string> _id_name_map;
    std::thread *_workers;

    void _manage_fd(int fd);
public:
    messenger_host(int port, int num_workers = 10);

    ~messenger_host();

    void start();
};

#endif //TEXTY_MESSENGER_HOST_HPP
