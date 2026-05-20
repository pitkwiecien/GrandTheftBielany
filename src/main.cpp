#include <iostream>
#include "core/Game.hpp"

int main(int /*argc*/, char* /*argv*/[]) {
    try {
        Game game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "[FATAL] " << e.what() << '\n';
        return 1;
    }
    return 0;
}