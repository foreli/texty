#include <iostream>
#include "messenger.hpp"

int main() {
    messenger msg("localhost", 3000);
    msg.start();
}