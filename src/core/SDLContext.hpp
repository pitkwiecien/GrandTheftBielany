#pragma once

// Inicjuje SDL, SDL_image, SDL_ttf, SDL_mixer w konstruktorze
// i sprząta w destruktorze. Tworzony raz, na początku w Game.
class SDLContext {
public:
    SDLContext();              // rzuca std::runtime_error przy błędzie
    ~SDLContext();
    SDLContext(const SDLContext&) = delete;
    SDLContext& operator=(const SDLContext&) = delete;
};
