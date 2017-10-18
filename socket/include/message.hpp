#ifndef SOCKET_MESSAGE_HPP
#define SOCKET_MESSAGE_HPP

#include <string>
#include <vector>

namespace sockets {
    std::string get_as_sock_msg(const std::string &s);

    std::string strip(std::string &s);

    std::vector<std::string> split_quoted(const std::string &s, char delim = ',', bool *contained = nullptr);
}


#endif //SOCKET_MESSAGE_HPP
