#pragma once
#include "core/GameState.hpp"
#include "gameplay/PlayerStats.hpp"
#include <vector>
#include <memory>

class Button;
class FontManager;
class Text;

// Ekran po śmierci gracza. Pokazuje wynik (czas przeżycia,
// zabicia, poziom) i pozwala zagrać ponownie lub wyjść do menu.
class GameOverState : public GameState {
public:
    GameOverState(StateContext ctx, FontManager& fonts,
                  const PlayerStats& finalStats, int finalLevel);
    ~GameOverState();

    void onEnter() override;
    void handleEvent(const SDL_Event& e) override;
    void update(float dt) override;
    void render(Renderer& renderer) override;

private:
    StateContext                         m_ctx;
    FontManager&                         m_fonts;
    PlayerStats                          m_finalStats;
    int                                  m_finalLevel;
    std::vector<std::unique_ptr<Button>> m_buttons;
    std::unique_ptr<Text>                m_summary;
};
