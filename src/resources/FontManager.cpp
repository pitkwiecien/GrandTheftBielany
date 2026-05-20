#include "resources/FontManager.hpp"

FontManager::~FontManager() {
    clear();
}

TTF_Font* FontManager::get(const std::string& path, int ptSize) {
    std::string key = makeKey(path, ptSize);
    auto it = m_cache.find(key);
    if (it != m_cache.end()) return it->second;

    TTF_Font* font = TTF_OpenFont(path.c_str(), ptSize);
    if (font) m_cache[key] = font;
    return font;
}

void FontManager::clear() {
    for (auto& [key, font] : m_cache)
        TTF_CloseFont(font);
    m_cache.clear();
}

std::string FontManager::makeKey(const std::string& path, int ptSize) {
    return path + "@" + std::to_string(ptSize);
}
