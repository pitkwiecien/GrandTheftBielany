#pragma once
#include "core/GameState.hpp"
#include <vector>
#include <memory>

class Button;
class TextureManager;
class FontManager;

// Menu główne: tytuł + przyciski (Start, Wyjście).
// Start robi states.replace(PlayState).
class MenuState : public GameState {
public:
    MenuState(StateContext ctx, TextureManager& textures, FontManager& fonts);
    ~MenuState();

    void onEnter() override;
    void handleEvent(const SDL_Event& e) override;
    void update(float dt) override;
    void render(Renderer& renderer) override;

private:
    StateContext                         m_ctx;
    TextureManager&                      m_textures;
    FontManager&                         m_fonts;
    std::vector<std::unique_ptr<Button>> m_buttons;
};
