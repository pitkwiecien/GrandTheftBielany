#pragma once
#include <SDL.h>

// Mierzy czas między klatkami przez SDL_GetPerformanceCounter.
// Użycie: na początku klatki tick(), potem getDelta() w sekundach.
class Timer {
public:
    Timer() : m_last(SDL_GetPerformanceCounter()) {}

    // Aktualizuje znacznik czasu i zwraca delta time w sekundach.
    float tick() {
        Uint64 now  = SDL_GetPerformanceCounter();
        Uint64 freq = SDL_GetPerformanceFrequency();
        float dt = static_cast<float>(now - m_last) / static_cast<float>(freq);
        m_last = now;
        return dt;
    }

private:
    Uint64 m_last = 0;
};
