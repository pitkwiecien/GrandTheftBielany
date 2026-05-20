#pragma once
#include "core/GameState.hpp"
#include "ecs/Registry.hpp"
#include "ecs/Entity.hpp"
#include "gameplay/Camera.hpp"
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
    void spawnBoar();
    void buildSystems();

private:
    StateContext m_ctx;
    TextureManager& m_textures;
    FontManager& m_fonts;
    Registry m_registry;
    Entity m_player = kNullEntity;
    Camera m_camera;
    std::vector<std::unique_ptr<ISystem>> m_systems;
    std::unique_ptr<RenderSystem>          m_renderSystem;
    std::unique_ptr<SpriteDirectionSystem> m_dirSystem;
};