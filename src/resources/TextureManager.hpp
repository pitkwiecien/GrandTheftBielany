#pragma once
#include <SDL.h>
#include <string>
#include <unordered_map>

class Renderer;

// Cache SDL_Texture*. Tekstury są własnością managera —
// kod gry NIGDY ich nie zwalnia, tylko pożycza wskaźnik.
class TextureManager {
public:
    TextureManager(Renderer& renderer);
    ~TextureManager();

    TextureManager(const TextureManager&) = delete;

    SDL_Texture* get(const std::string& path);
    void clear();

private:
    Renderer& m_renderer;
    std::unordered_map<std::string, SDL_Texture*> m_cache;
};
