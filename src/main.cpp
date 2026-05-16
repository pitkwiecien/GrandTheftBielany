#include <SDL.h>          // SDL wymaga sygnatury int main(int, char**)
#include <exception>
#include "core/Game.hpp"
#include "util/Logger.hpp"

int main(int /*argc*/, char* /*argv*/[]) {
    try {
        Game game;
        game.run();
    } catch (const std::exception& e) {
        Logger::error(std::string("Krytyczny blad: ") + e.what());
        return 1;
    }
    return 0;
}
