#pragma once
#include "ISystem.hpp"
#include "ecs/Entity.hpp"

class WaveDirector;
class TextureManager;

// Spawnuje wrogów poza ekranem wokół gracza wg decyzji WaveDirector.
// Trzyma referencje do directora (co/ile) i tekstur (jak wyglądają).
class SpawnSystem : public ISystem {
public:
    SpawnSystem(WaveDirector& director, TextureManager& textures);
    void update(Registry& reg, float dt) override;

private:
    Entity spawnEnemy(Registry& reg, int enemyTypeId, Entity player);

    WaveDirector&   m_director;
    TextureManager& m_textures;
    float           m_gameTime = 0.f;
};
