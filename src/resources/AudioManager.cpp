#include "resources/AudioManager.hpp"

AudioManager::~AudioManager() {
    clear();
}

Mix_Chunk* AudioManager::getSound(const std::string& path) {
    auto it = m_sounds.find(path);
    if (it != m_sounds.end()) return it->second;

    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if (chunk) m_sounds[path] = chunk;
    return chunk;
}

Mix_Music* AudioManager::getMusic(const std::string& path) {
    auto it = m_music.find(path);
    if (it != m_music.end()) return it->second;

    Mix_Music* mus = Mix_LoadMUS(path.c_str());
    if (mus) m_music[path] = mus;
    return mus;
}

void AudioManager::playSound(const std::string& path, int volume) {
    Mix_Chunk* chunk = getSound(path);
    if (!chunk) return;
    int ch = Mix_PlayChannel(-1, chunk, 0);
    if (ch != -1) Mix_Volume(ch, volume);
}

void AudioManager::playMusic(const std::string& path, bool loop) {
    Mix_Music* mus = getMusic(path);
    if (mus) Mix_PlayMusic(mus, loop ? -1 : 0);
}

void AudioManager::stopMusic() {
    Mix_HaltMusic();
}

void AudioManager::clear() {
    stopMusic();
    for (auto& [key, chunk] : m_sounds) Mix_FreeChunk(chunk);
    for (auto& [key, mus]   : m_music)  Mix_FreeMusic(mus);
    m_sounds.clear();
    m_music.clear();
}
