#include "resources/FontManager.hpp"

FontManager::~FontManager() {
    for (auto& [key, font] : m_cache)
        TTF_CloseFont(font);
}

TTF_Font* FontManager::get(const std::string& path, int ptSize) {
    std::string key = path + "@" + std::to_string(ptSize);
    auto it = m_cache.find(key);
    if (it != m_cache.end()) return it->second;

    TTF_Font* font = TTF_OpenFont(path.c_str(), ptSize);
    if (font) m_cache[key] = font;
    return font;
}
