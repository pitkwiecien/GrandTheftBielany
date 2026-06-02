#pragma once
#include <SDL.h>
#include <string>
#include <unordered_map>

class Renderer;

// cache SDL_Texture*, tekstury są własnością managera
class TextureManager {
    public:
        TextureManager(Renderer& renderer);
        ~TextureManager();

        SDL_Texture* get(const std::string& path);
    private:
        Renderer& m_renderer;
        std::unordered_map<std::string, SDL_Texture*> m_cache;
};
