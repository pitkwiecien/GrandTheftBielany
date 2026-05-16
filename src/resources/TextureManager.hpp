#pragma once
#include <SDL.h>
#include <string>
#include <unordered_map>

class Renderer;

class TextureManager {
public:
    explicit TextureManager(Renderer& renderer);
    ~TextureManager();                              // niszczy wszystkie tekstury

    SDL_Texture* get(const std::string& path);      // wczytuje lub zwraca z cache

private:
    Renderer& m_renderer;
    std::unordered_map<std::string, SDL_Texture*> m_cache;
};