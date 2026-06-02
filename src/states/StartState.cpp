#include "states/StartState.hpp"
#include "states/PlayState.hpp"
#include "core/Renderer.hpp"
#include "resources/TextureManager.hpp"
#include "resources/FontManager.hpp"

StartState::StartState(StateContext ctx, TextureManager& textures, FontManager& fonts)
    : m_ctx(ctx), m_textures(textures), m_fonts(fonts) {}

void StartState::onEnter() {
    m_bgTexture = m_textures.get("assets/textures/screens/title_1080.png");
}

void StartState::handleEvent(const SDL_Event& event) {
    bool shouldStartGame = false;

    if (event.type == SDL_KEYDOWN) {
        shouldStartGame = true;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN) {
        shouldStartGame = true;
    }

    if (shouldStartGame) {
        m_ctx.states->replace(
            std::make_unique<PlayState>(m_ctx, m_textures, m_fonts));
    }
}

void StartState::update(float) {
}

void StartState::render(Renderer& renderer) {
    renderer.clear({0, 0, 0, 255});

    if (m_bgTexture) {
        SDL_Rect destinationRect{0, 0, 1280, 720};
        renderer.drawTexture(m_bgTexture, nullptr, &destinationRect);
    }
}