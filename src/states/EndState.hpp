#pragma once
#include "core/GameState.hpp"
#include <SDL.h>
#include <SDL_ttf.h>

class TextureManager;
class FontManager;

class EndState : public GameState {
    public:
        EndState(StateContext ctx, TextureManager& textures, FontManager& fonts, int finalWave);

        void onEnter() override;
        void handleEvent(const SDL_Event& e) override;
        void update(float dt) override;
        void render(Renderer& renderer) override;

    private:
        static bool hitTest(int px, int py, const SDL_Rect& r);

        StateContext m_ctx;
        TextureManager& m_textures;
        FontManager& m_fonts;
        int m_finalWave = 1;

        SDL_Texture* m_bgTexture = nullptr;

        TTF_Font* m_titleFont = nullptr;
        TTF_Font* m_scoreFont = nullptr;
        TTF_Font* m_buttonFont = nullptr;

        SDL_Rect m_playAgainRect{};
        SDL_Rect m_exitRect{};

        bool m_hoverPlayAgain = false;
        bool m_hoverExit = false;
};