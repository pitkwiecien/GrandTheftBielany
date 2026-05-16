#pragma once
#include "core/GameState.hpp"
#include <vector>
#include <memory>

class Button;
class FontManager;

// Przezroczysta nakładka pauzy. Esc wznawia (pop),
// przyciski: Wznów / Wyjdź do menu.
class PauseState : public GameState {
public:
    PauseState(StateContext ctx, FontManager& fonts);
    ~PauseState();

    void onEnter() override;
    void handleEvent(const SDL_Event& e) override;
    void update(float dt) override;
    void render(Renderer& renderer) override;

    bool isTransparent() const override { return true; }

private:
    StateContext                         m_ctx;
    FontManager&                         m_fonts;
    std::vector<std::unique_ptr<Button>> m_buttons;
};
