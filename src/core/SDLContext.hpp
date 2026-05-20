#pragma once

// RAII na inicjalizację bibliotek SDL: SDL, SDL_image,
// SDL_ttf, SDL_mixer. Tworzony raz, jako pierwsze pole Game.
// Konstruktor rzuca std::runtime_error przy błędzie inicjalizacji.
class SDLContext {
public:
    SDLContext();
    ~SDLContext();

    SDLContext(const SDLContext&)            = delete;
    SDLContext& operator=(const SDLContext&) = delete;
    SDLContext(SDLContext&&)                 = delete;
    SDLContext& operator=(SDLContext&&)      = delete;

private:
    bool m_audioOpen = false;
};
