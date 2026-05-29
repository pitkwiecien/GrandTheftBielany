#pragma once
#include "math/Vec2.hpp"

// Steruje falami wrogów:
// - fala N spawuje N wrogów, co 2 sekundy na krawędziach mapy
// - kolejna fala startuje po 5 s od śmierci ostatniego wroga
//   lub po kMaxIdleTime sekundach (cokolwiek nastąpi pierwsze)
class WaveDirector {
public:
    static constexpr float kSpawnInterval   = 2.f;  // s między kolejnymi spawnami w fali
    static constexpr float kAllDeadCooldown = 5.f;  // s przerwy po wyczyszczeniu fali
    static constexpr float kMaxIdleTime     = 30.f; // max s między falami

    // Wywołaj co klatkę. livingEnemies = aktualna liczba żywych wrogów na planszy.
    // Zwraca liczbę wrogów do zespawnowania w tej klatce.
    int update(float dt, int livingEnemies);

    int  currentWave() const { return m_wave; }
    bool isSpawning()  const { return !m_idle; }

    Vec2 randomEdgePos() const;

private:
    int   m_wave         = 1;
    int   m_toSpawn      = 1;
    float m_spawnTimer   = 0.f;
    bool  m_idle         = false;
    float m_maxIdleTimer = 0.f;
    float m_allDeadTimer = -1.f;
};
