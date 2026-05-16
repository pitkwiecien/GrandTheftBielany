#pragma once
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>

// Cache efektów (Mix_Chunk) i muzyki (Mix_Music).
// Mix_Chunk = krótkie SFX, Mix_Music = ścieżka w tle.
class AudioManager {
public:
    AudioManager() = default;
    ~AudioManager();

    AudioManager(const AudioManager&)            = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    // Efekt dźwiękowy (strzał, trafienie, pickup).
    Mix_Chunk* getSound(const std::string& path);

    // Muzyka w tle.
    Mix_Music* getMusic(const std::string& path);

    // Pomocnicze sterowanie odtwarzaniem.
    void playSound(const std::string& path, int volume = MIX_MAX_VOLUME);
    void playMusic(const std::string& path, bool loop = true);
    void stopMusic();

    void clear();

private:
    std::unordered_map<std::string, Mix_Chunk*> m_sounds;
    std::unordered_map<std::string, Mix_Music*> m_music;
};
