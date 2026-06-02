#pragma once
#include <SDL_ttf.h>
#include <string>
#include <unordered_map>

// cache TTF_Font*  klucz = ścieżka + rozmiar punktowy
class FontManager {
    public:
        FontManager() =default;
        ~FontManager();

        TTF_Font* get(const std::string& path, int ptSize);
    private:
        std::unordered_map<std::string, TTF_Font*> m_cache;
};
