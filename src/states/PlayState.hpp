#pragma once
#include "core/GameState.hpp"
#include "ecs/Registry.hpp"
#include "ecs/Entity.hpp"
#include "gameplay/Camera.hpp"
#include "gameplay/PlayerStats.hpp"
#include "gameplay/WeaponDatabase.hpp"
#include "gameplay/WaveDirector.hpp"
#include "gameplay/UpgradePool.hpp"
#include <memory>
#include <vector>

class ISystem;
class CollisionSystem;
class RenderSystem;
class HUD;
class TextureManager;
class FontManager;
class InputManager;

// Serce gry. Posiada Registry, wszystkie systemy, kamerę, HUD.
// update() uruchamia systemy w stałej kolejności; gdy gracz
// awansuje, wrzuca LevelUpState na stos (przezroczysty).
class PlayState : public GameState {
public:
    PlayState(StateContext ctx,
              TextureManager& textures,
              FontManager& fonts);
    ~PlayState();

    void onEnter() override;
    void handleEvent(const SDL_Event& e) override;
    void update(float dt) override;
    void render(Renderer& renderer) override;

    // Wywoływane przez LevelUpState po wyborze ulepszenia.
    UpgradePool&     upgrades()  { return m_upgrades; }
    Registry&        registry()  { return m_registry; }
    Entity           player() const { return m_player; }
    PlayerStats&     stats()     { return m_stats; }

private:
    void spawnPlayer();
    void buildSystems();
    void checkLevelUp();
    void checkGameOver();

    StateContext     m_ctx;
    TextureManager&  m_textures;
    FontManager&     m_fonts;

    Registry         m_registry;
    Entity           m_player = kNullEntity;

    Camera           m_camera;
    PlayerStats      m_stats;
    WeaponDatabase   m_weaponDb;
    WaveDirector     m_waveDirector;
    UpgradePool      m_upgrades;

    std::vector<std::unique_ptr<ISystem>> m_systems;
    CollisionSystem* m_collisions = nullptr; // współdzielony z DamageSystem
    std::unique_ptr<RenderSystem> m_renderSystem;
    std::unique_ptr<HUD>          m_hud;

    float m_gameTime = 0.f;
    bool  m_paused   = false;
};
