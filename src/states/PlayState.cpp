#include "states/PlayState.hpp"
#include "core/Renderer.hpp"
#include "resources/TextureManager.hpp"
#include "resources/FontManager.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/PlayerInputSystem.hpp"
#include "systems/EnemyAISystem.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/SpriteDirectionSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "ecs/components/Transform.hpp"
#include "ecs/components/Velocity.hpp"
#include "ecs/components/PlayerTag.hpp"
#include "ecs/components/SpriteComp.hpp"
#include "ecs/components/DirectionComp.hpp"
#include "ecs/components/EnemyTag.hpp"
#include "ecs/components/Collider.hpp"
#include "ecs/components/AnimationComp.hpp"
#include "math/MathUtils.hpp"

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

static const char* kPlayerRunTextures[8] = {
    "assets/textures/huntsman/running/rotations/north.png",
    "assets/textures/huntsman/running/rotations/north-east.png",
    "assets/textures/huntsman/running/rotations/east.png",
    "assets/textures/huntsman/running/rotations/south-east.png",
    "assets/textures/huntsman/running/rotations/south.png",
    "assets/textures/huntsman/running/rotations/south-west.png",
    "assets/textures/huntsman/running/rotations/west.png",
    "assets/textures/huntsman/running/rotations/north-west.png",
};

static constexpr const char* kBoarTexture =
    "assets/textures/boar/south.png";

static constexpr const char* kMapTexture = 
    "assets/textures/maps/map1_m.png";

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

    m_bgTexture = m_textures.get(kMapTexture);
    if (m_bgTexture) {
        m_textures.querySize(m_bgTexture, m_bgWidth, m_bgHeight);
    }

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

    // load the run textures into the DirectionComp
    auto& dir = m_registry.add<DirectionComp>(m_player);
    for (int i = 0; i < 8; ++i) {
        dir.textures[i] = m_textures.get(kPlayerRunTextures[i]);
    }
    dir.facing = Direction8::South;

    // set up the Animation Component
    auto& anim = m_registry.add<AnimationComp>(m_player);
    anim.numFrames = 4;
    anim.frameWidth = 80;
    anim.frameHeight = 80;
    anim.frameTime = 0.1f;
    anim.isPlaying = false;

    // set the initial sprite bounds
    auto& sprite = m_registry.add<SpriteComp>(m_player);
    sprite.texture = dir.textures[static_cast<int>(Direction8::South)];
    sprite.srcRect = {0, 0, 80, 80};
    sprite.w = 80;
    sprite.h = 80;
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
    
    m_systems.push_back(
        std::make_unique<AnimationSystem>());
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

    if (auto* t = m_registry.tryGet<Transform>(m_player)) {
        // m_camera.follow(t->pos, dt);
        const float padding = 32.f; 
        const float minX = -640.f + padding;
        const float maxX =  640.f - padding;
        const float minY = -360.f + padding;
        const float maxY =  360.f - padding;

        t->pos.x = MathUtils::clamp(t->pos.x, minX, maxX);
        t->pos.y = MathUtils::clamp(t->pos.y, minY, maxY);
    }

    m_registry.flushDestroyed();
}

void PlayState::render(Renderer& renderer) {
    renderer.clear({40, 140, 40, 255});
    if (m_bgTexture) {
        // fixed to the world
        // centers the map at world coordinates (0, 0)

        // SDL_Rect dst = m_camera.worldToScreen({0.f, 0.f}, m_bgWidth, m_bgHeight);
        // renderer.drawTexture(m_bgTexture, nullptr, &dst);

        // fixed to the screen
        // fills the entire 1280x720 window regardless of where the player walks

        SDL_Rect screenDst = {0, 0, 1280, 720};
        renderer.drawTexture(m_bgTexture, nullptr, &screenDst);
    }
    m_renderSystem->render(m_registry);
}