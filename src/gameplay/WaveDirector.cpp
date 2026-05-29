#include "gameplay/WaveDirector.hpp"
#include "util/Random.hpp"

static constexpr float kHalfW = 608.f;
static constexpr float kHalfH = 328.f;

Vec2 WaveDirector::randomEdgePos() const {
    switch (Random::range(0, 3)) {
    case 0: return {-kHalfW, Random::range(-kHalfH, kHalfH)};
    case 1: return { kHalfW, Random::range(-kHalfH, kHalfH)};
    case 2: return {Random::range(-kHalfW, kHalfW), -kHalfH};
    default:return {Random::range(-kHalfW, kHalfW),  kHalfH};
    }
}

int WaveDirector::update(float dt, int livingEnemies) {
    int spawns = 0;

    if (!m_idle) {
        m_spawnTimer -= dt;
        if (m_spawnTimer <= 0.f && m_toSpawn > 0) {
            ++spawns;
            --m_toSpawn;
            m_spawnTimer = kSpawnInterval;
        }
        if (m_toSpawn == 0)
            m_idle = true;
    } else {
        if (livingEnemies == 0 && m_allDeadTimer < 0.f)
            m_allDeadTimer = kAllDeadCooldown;

        if (m_allDeadTimer >= 0.f) {
            m_allDeadTimer -= dt;
            if (m_allDeadTimer <= 0.f) {
                ++m_wave;
                m_toSpawn      = m_wave;
                m_spawnTimer   = 0.f;
                m_idle         = false;
                m_allDeadTimer = -1.f;
            }
        }
    }

    return spawns;
}
