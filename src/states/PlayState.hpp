#pragma once
#include "math/Math.hpp"
#include "core/GameState.hpp"
#include "ecs/Registry.hpp"
#include "ecs/Entity.hpp"
#include "gameplay/Camera.hpp"
#include "gameplay/WaveDirector.hpp"

#include <SDL_ttf.h>
#include <memory>
#include <vector>

class ISystem;
class RenderSystem;
class SpriteDirectionSystem;
class TextureManager;
class FontManager;

class PlayState : public GameState {
public:
    PlayState(StateContext ctx, TextureManager& textures, FontManager& fonts);
    ~PlayState();
    void onEnter() override;
    void handleEvent(const SDL_Event& e) override;
    void update(float dt) override;
    void render(Renderer& renderer) override;

private:
    void spawnPlayer();
    void buildSystems();
    void spawnWaveEnemy(Vec2 pos);
    Vec2 findSpawnPos();
    int  countLivingEnemies();

private:
    StateContext m_ctx;
    TextureManager& m_textures;
    FontManager& m_fonts;
    Registry m_registry;
    Entity m_player = kNullEntity;
    Camera m_camera;
    WaveDirector m_waveDirector;
    std::vector<std::unique_ptr<ISystem>> m_systems;
    std::unique_ptr<RenderSystem>          m_renderSystem;
    std::unique_ptr<SpriteDirectionSystem> m_dirSystem;
    SDL_Texture* m_bgTexture     = nullptr;
    SDL_Texture* m_bulletTexture = nullptr;
    TTF_Font*    m_hpFont        = nullptr;
};