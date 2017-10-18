#include <iostream>
#include <string>
#include "messenger-client.hpp"

int main() {
    std::string user;
    std::cout << "Please enter your username: ";
    std::cin >> user;

    messenger_client client("localhost", 3000);
    if (!client.is_open()) {
        std::cout << "Server is not running. Please visit https://github.com/kostaskol/texty "
                "for more information on how to set up a local host (requires port forwarding)"
                  << std::endl;
        return 1;
    }

    while (!client.connect(user)) {
        std::cout << "That username is taken. Please use another one: ";
        std::cin >> user;
    }
    client.start();
}