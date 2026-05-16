#pragma once
#include <SDL_ttf.h>
#include <string>
#include <unordered_map>

// Cache TTF_Font*. Klucz = ścieżka + rozmiar punktowy,
// bo w SDL_ttf font o innym rozmiarze to osobny zasób.
class FontManager {
public:
    FontManager() = default;
    ~FontManager();

    FontManager(const FontManager&)            = delete;
    FontManager& operator=(const FontManager&) = delete;

    // Wczytuje czcionkę w danym rozmiarze lub zwraca z cache.
    TTF_Font* get(const std::string& path, int ptSize);

    void clear();

private:
    std::unordered_map<std::string, TTF_Font*> m_cache;

    static std::string makeKey(const std::string& path, int ptSize);
};
