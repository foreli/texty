#ifndef TEXTY_FORMATTER_HPP
#define TEXTY_FORMATTER_HPP

#include <string>
#include <vector>
#include <vector>
#include "helpers.hpp"

#define TYPE_HOST 0xB1
#define TYPE_CLIENT 0xB2

#define H_USE 0xA0
#define H_CONNECT 0xA1
#define H_MSG 0xA2
#define H_DISCONNECT 0xA3

#define C_USE 0xA0
#define C_OK 0xE1
#define C_DECLINED 0xE2
#define C_MSG 0xE3
#define C_DISCONNECT 0xE4
#define UNKNOWN 0x0
namespace formatter {
    std::string format_use(const std::string &use) {
        return "user:" + use;
    }

    std::string format_connection(const std::string &user) {
        return "connect:" + user;
    }

    std::string format_msg(const std::string &msg) {
        return "msg:" + msg;
    }

    std::string format_disconnect() {
        return "disconnect:disconnect";
    }

    std::string format_ok(const std::string &type) {
        return type + ":OK";
    }

    std::string format_decline(const std::string &type) {
        return type + ":DECLINED";
    }

    int parse(const std::string &msg, int type = TYPE_HOST, std::string *arg = nullptr) {
        std::vector<std::string> v = helpers::split(msg, ':');
        if (type == TYPE_HOST) {
            if (v[0] == "connect") {
                if (arg != nullptr) {
                    *arg = v[1];
                }
                return H_CONNECT;
            } else if (v[0] == "msg") {
                if (arg != nullptr) {
                    *arg = v[1];
                }
                return H_MSG;
            } else if (v[0] == "disconnect") {
                return H_DISCONNECT;
            } else if (v[0] == "use") {
                return H_USE;
            }
        } else {
            if (v[0] == "connect") {
                if (v[1] == "OK") {
                    return C_OK;
                } else if (v[1] == "DECLINED") {
                    return C_DECLINED;
                }
            } else if (v[0] == "msg") {
                if (arg != nullptr) {
                    *arg = v[1];
                }
                return C_MSG;
            } else if (v[0] == "disconnect") {
                return C_DISCONNECT;
            } else if (v[0] == "use") {
                if (arg != nullptr) {
                    *arg = v[1];
                }
                return C_USE;
            }
        }
        return UNKNOWN;
    }
}

#endif //TEXTY_FORMATTER_HPP
