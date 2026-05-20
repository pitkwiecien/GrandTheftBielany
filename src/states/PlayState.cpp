#include "states/PlayState.hpp"
#include "core/InputManager.hpp"
#include "core/Renderer.hpp"
#include "resources/TextureManager.hpp"
#include "resources/FontManager.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/PlayerInputSystem.hpp"
#include "systems/EnemyAISystem.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/SpriteDirectionSystem.hpp"
#include "ecs/components/Transform.hpp"
#include "ecs/components/Velocity.hpp"
#include "ecs/components/PlayerTag.hpp"
#include "ecs/components/SpriteComp.hpp"
#include "ecs/components/DirectionComp.hpp"
#include "ecs/components/EnemyTag.hpp"
#include "ecs/components/Collider.hpp"

static const char* kPlayerTextures[8] = {
    "assets/textures/huntsman/idle/rotations/north.png",       // 0 North
    "assets/textures/huntsman/idle/rotations/north-east.png",  // 1 NorthEast
    "assets/textures/huntsman/idle/rotations/east.png",        // 2 East
    "assets/textures/huntsman/idle/rotations/south-east.png",  // 3 SouthEast
    "assets/textures/huntsman/idle/rotations/south.png",       // 4 South
    "assets/textures/huntsman/idle/rotations/south-west.png",  // 5 SouthWest
    "assets/textures/huntsman/idle/rotations/west.png",        // 6 West
    "assets/textures/huntsman/idle/rotations/north-west.png",  // 7 NorthWest
};

static constexpr const char* kBoarTexture =
    "assets/textures/boar/south.png";

PlayState::PlayState(
    StateContext ctx,
    TextureManager& textures,
    FontManager& fonts)
    : m_ctx(ctx),
      m_textures(textures),
      m_fonts(fonts)
{}

PlayState::~PlayState() = default;

void PlayState::onEnter() {
    m_camera.setViewport(1280, 720);

    spawnPlayer();
    spawnBoar();

    buildSystems();

    m_renderSystem = std::make_unique<RenderSystem>(
        *m_ctx.renderer, m_camera);

    m_dirSystem = std::make_unique<SpriteDirectionSystem>();
}

void PlayState::spawnPlayer() {
    m_player = m_registry.create();

    auto& t = m_registry.add<Transform>(m_player);
    t.pos = {0.f, 0.f};

    m_registry.add<PlayerTag>(m_player);

    auto& vel = m_registry.add<Velocity>(m_player);
    vel.maxSpeed = 220.f;

    auto& dir = m_registry.add<DirectionComp>(m_player);
    for (int i = 0; i < 8; ++i)
        dir.textures[i] = m_textures.get(kPlayerTextures[i]);
    dir.facing = Direction8::South;

    auto& sprite = m_registry.add<SpriteComp>(m_player);
    sprite.texture = dir.textures[static_cast<int>(Direction8::South)];
    sprite.w = 64;
    sprite.h = 64;
}

void PlayState::spawnBoar() {
    Entity boar = m_registry.create();

    auto& t = m_registry.add<Transform>(boar);
    t.pos = {300.f, 200.f};

    auto& enemy = m_registry.add<EnemyTag>(boar);
    enemy.touchDamage = 1.f;
    enemy.xpReward    = 2.f;

    auto& vel = m_registry.add<Velocity>(boar);
    vel.maxSpeed = 80.f;

    auto& sprite = m_registry.add<SpriteComp>(boar);
    sprite.texture = m_textures.get(kBoarTexture);
    sprite.w = 64;
    sprite.h = 64;

    auto& col = m_registry.add<Collider>(boar);
    col.radius = 28.f;
}

void PlayState::buildSystems() {
    m_systems.push_back(
        std::make_unique<PlayerInputSystem>(*m_ctx.input, 220.f));

    m_systems.push_back(
        std::make_unique<EnemyAISystem>());

    m_systems.push_back(
        std::make_unique<MovementSystem>());
}

void PlayState::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN &&
        e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
    {
        m_ctx.states->clear();
    }
}

void PlayState::update(float dt) {
    for (auto& s : m_systems)
        s->update(m_registry, dt);

    m_dirSystem->update(m_registry, dt);

    if (auto* t = m_registry.tryGet<Transform>(m_player))
        m_camera.follow(t->pos, dt);

    m_registry.flushDestroyed();
}

void PlayState::render(Renderer& renderer) {
    renderer.clear({40, 140, 40, 255});
    m_renderSystem->render(m_registry);
}