#pragma once
#include "core/GameState.hpp"
#include <SDL.h>

class TextureManager;
class FontManager;

class StartState : public GameState {
    public:
        StartState(StateContext ctx, TextureManager& textures, FontManager& fonts);
        void onEnter() override;
        void handleEvent(const SDL_Event& e) override;
        void update(float dt) override;
        void render(Renderer& renderer) override;

    private:
        StateContext m_ctx;
        TextureManager& m_textures;
        FontManager& m_fonts;
        SDL_Texture* m_bgTexture = nullptr;
};