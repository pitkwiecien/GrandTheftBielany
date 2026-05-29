#include "systems/RenderSystem.hpp"
#include "ecs/Components.hpp"
#include "core/Renderer.hpp"
#include "gameplay/Camera.hpp"
#include "ecs/Registry.hpp"

RenderSystem::RenderSystem(
    Renderer& renderer,
    Camera& camera)
    : m_renderer(renderer),
      m_camera(camera)
{}

void RenderSystem::render(Registry& reg) {

    reg.view<Transform, SpriteComp>(
        [&](Entity /*e*/,
            Transform& t,
            SpriteComp& s)
    {
        if (!s.visible || !s.texture)
            return;

        SDL_Rect dst = m_camera.worldToScreen(t.pos, s.w, s.h);

        const SDL_Rect* src = (s.srcRect.w == 0) ? nullptr : &s.srcRect;

        SDL_RendererFlip flip = s.flipHorizontal
            ? SDL_FLIP_HORIZONTAL
            : SDL_FLIP_NONE;

        SDL_RenderCopyEx(
            m_renderer.handle(),
            s.texture,
            src,
            &dst,
            t.rotation,
            nullptr,
            flip);
    });
}