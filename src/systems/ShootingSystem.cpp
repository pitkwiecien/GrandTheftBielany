#include "systems/ShootingSystem.hpp"
#include "core/InputManager.hpp"
#include "ecs/Registry.hpp"
#include "ecs/Components.hpp"
#include <SDL.h>

// Indeksy zgodne z Direction8: North=0, NE=1, East=2, SE=3, South=4, SW=5, West=6, NW=7
static const Vec2 kDirs[8] = {
    { 0.f,     -1.f    }, // N
    { 0.707f,  -0.707f }, // NE
    { 1.f,      0.f    }, // E
    { 0.707f,   0.707f }, // SE
    { 0.f,      1.f    }, // S
    {-0.707f,   0.707f }, // SW
    {-1.f,      0.f    }, // W
    {-0.707f,  -0.707f }, // NW
};

// Obrót w stopniach dla SDL_RenderCopyEx (0° = prawo/East, rosnące = CW).
// Zakładamy że tekstura naboju wskazuje na prawo (East).
static const double kRotations[8] = {
    270.0, // N
    315.0, // NE
      0.0, // E
     45.0, // SE
     90.0, // S
    135.0, // SW
    180.0, // W
    225.0, // NW
};

ShootingSystem::ShootingSystem(const InputManager& input, SDL_Texture* bulletTex)
    : m_input(input), m_bulletTex(bulletTex) {
    if (bulletTex)
        SDL_QueryTexture(bulletTex, nullptr, nullptr, &m_texW, &m_texH);
}

void ShootingSystem::update(Registry& reg, float dt) {
    m_cooldown -= dt;

    // znajdywanie gracza
    Transform*     pt = nullptr;
    DirectionComp* pd = nullptr;
    PlayerTag*     pTag = nullptr;
    reg.view<PlayerTag, Transform, DirectionComp>(
        [&](Entity, PlayerTag& tag, Transform& t, DirectionComp& d) {
            pt = &t;
            pd = &d;
            pTag = &tag;
        });
    if (!pt || !pd || !pTag) return;

    pTag->isAiming = m_input.mouseDown(SDL_BUTTON_LEFT);

    if (!pTag->isAiming || m_cooldown > 0.f) return;

    int facing = static_cast<int>(pd->facing);
    Vec2 dir   = kDirs[facing];

    Entity proj = reg.create();

    auto& t = reg.add<Transform>(proj);
    t.pos      = pt->pos;
    t.rotation = kRotations[facing];

    auto& vel = reg.add<Velocity>(proj);
    vel.value = dir * kBulletSpeed;

    auto& sprite = reg.add<SpriteComp>(proj);
    sprite.texture = m_bulletTex;
    sprite.w = m_texW / 4;
    sprite.h = m_texH / 4;

    auto& tag = reg.add<ProjectileTag>(proj);
    tag.damage   = kBulletDamage;
    tag.lifetime = kBulletLife;

    m_cooldown = kFireRate;
}
