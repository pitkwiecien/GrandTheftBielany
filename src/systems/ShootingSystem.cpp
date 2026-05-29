#include "systems/ShootingSystem.hpp"
#include "core/InputManager.hpp"
#include "ecs/Registry.hpp"
#include "ecs/Components.hpp"

// kierunki
static const Vec2 kDirs[8] = {
    { 0.f,     -1.f    }, // n
    { 0.707f,  -0.707f }, // ne
    { 1.f,      0.f    }, // e
    { 0.707f,   0.707f }, // se
    { 0.f,      1.f    }, // s
    {-0.707f,   0.707f }, // sw
    {-1.f,      0.f    }, // w
    {-0.707f,  -0.707f }, // nw
};

ShootingSystem::ShootingSystem(const InputManager& input, SDL_Texture* bulletTex)
    : m_input(input), m_bulletTex(bulletTex) {}

void ShootingSystem::update(Registry& reg, float dt) {
    m_cooldown -= dt;

    if (!m_input.mouseDown(SDL_BUTTON_LEFT)) return;
    if (m_cooldown > 0.f) return;

    // znajdywanie gracza
    Transform*     pt = nullptr;
    DirectionComp* pd = nullptr;
    reg.view<PlayerTag, Transform, DirectionComp>(
        [&](Entity, PlayerTag&, Transform& t, DirectionComp& d) {
            pt = &t;
            pd = &d;
        });
    if (!pt || !pd) return;

    Vec2 dir = kDirs[static_cast<int>(pd->facing)];

    Entity proj = reg.create();

    auto& t = reg.add<Transform>(proj);
    t.pos = pt->pos;

    auto& vel = reg.add<Velocity>(proj);
    vel.value = dir * kBulletSpeed;

    auto& sprite = reg.add<SpriteComp>(proj);
    sprite.texture = m_bulletTex;
    sprite.w = 10;
    sprite.h = 4;

    auto& tag = reg.add<ProjectileTag>(proj);
    tag.damage   = kBulletDamage;
    tag.lifetime = kBulletLife;

    m_cooldown = kFireRate;
}
