#pragma once
#include <SDL.h>
#include <string>
#include <unordered_map>

class Renderer;

// Cache SDL_Texture*. Tekstury są własnością managera —
// kod gry NIGDY ich nie zwalnia, tylko pożycza wskaźnik.
class TextureManager {
public:
    explicit TextureManager(Renderer& renderer);
    ~TextureManager();

    TextureManager(const TextureManager&)            = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    // Wczytuje z pliku lub zwraca z cache. nullptr przy błędzie.
    SDL_Texture* get(const std::string& path);

    // Zwraca rozmiar tekstury w pikselach.
    void querySize(SDL_Texture* tex, int& w, int& h) const;

    void clear();

private:
    Renderer& m_renderer;
    std::unordered_map<std::string, SDL_Texture*> m_cache;
};
