#include "resources/TextureManager.hpp"
#include "core/Renderer.hpp"
#include <SDL_image.h>

TextureManager::TextureManager(Renderer& renderer) : m_renderer(renderer) {}

TextureManager::~TextureManager() {
    clear();
}

SDL_Texture* TextureManager::get(const std::string& path) {
    auto it = m_cache.find(path);
    if (it != m_cache.end()) return it->second;

    SDL_Texture* tex = IMG_LoadTexture(m_renderer.handle(), path.c_str());
    if (tex) m_cache[path] = tex;
    return tex;
}

void TextureManager::querySize(SDL_Texture* tex, int& w, int& h) const {
    SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
}

void TextureManager::clear() {
    for (auto& [path, tex] : m_cache)
        SDL_DestroyTexture(tex);
    m_cache.clear();
}
