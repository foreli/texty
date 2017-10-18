#ifndef TRIES_HELPERS_H
#define TRIES_HELPERS_H

#include <string>
#include <sstream>
#include <vector>


namespace helpers {
    std::vector<std::string> split(const std::string &s,  char delim) {
        std::vector<std::string> v;
        std::stringstream ss(s);
        std::string tmp;
        while(std::getline(ss, tmp, delim)) {
            v.push_back(tmp);
        }
        return v;
    }

    std::vector<std::string> split_quoted(const std::string &s, char delim, bool *contained = nullptr) {
        std::vector<std::string> v;
        bool quoted = false;
        std::string part;
        bool pushed = false;
        bool ctnd = false;
        for (auto c : s) {
            if (c == delim && !quoted) {
                v.push_back(std::move(part));
                part = "";
                pushed = true;
                ctnd = true;
            } else if (c == '"') {
                quoted = !quoted;
                part += c;
            } else {
                pushed = false;
                part += c;
            }
        }

        if (!pushed) {
            v.push_back(part);
        }

        if (contained != nullptr) {
            *contained = ctnd;
        }
        return v;
    }

    std::string join(const std::vector<std::string> &v, const std::string &on) {
        std::string s;
        for (int i = 0; i < v.size() - 1; i++) {
            s += v[i] + on;
        }
        s += v[v.size() - 1];
        return s;
    }

    std::string trim(const std::string &s) {
        const auto begin = s.find_first_not_of(' ');
        if (begin == std::string::npos) return "";
        const auto end = s.find_last_not_of(' ');

        const auto range = end - begin + 1;
        return s.substr(begin, range);
    }
}

#endif //TRIES_HELPERS_H
