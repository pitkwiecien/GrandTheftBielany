#pragma once
#include "core/GameState.hpp"
#include <vector>
#include <memory>

class PlayState;
class UpgradeCardUI;
class TextureManager;
class FontManager;
struct Upgrade;

// Przezroczysty stan na wierzchu PlayState. Zatrzymuje grę
// (PlayState pod spodem nie jest updateowany, tylko rysowany),
// pokazuje 3-4 karty z UpgradePool. Wybór aplikuje ulepszenie
// i zdejmuje ten stan ze stosu.
class LevelUpState : public GameState {
public:
    LevelUpState(StateContext ctx, PlayState& play,
                 TextureManager& textures, FontManager& fonts);
    ~LevelUpState();

    void onEnter() override;
    void handleEvent(const SDL_Event& e) override;
    void update(float dt) override;
    void render(Renderer& renderer) override;

    bool isTransparent() const override { return true; }

private:
    void onCardPicked(Upgrade* chosen);

    StateContext    m_ctx;
    PlayState&      m_play;
    TextureManager& m_textures;
    FontManager&    m_fonts;

    std::vector<Upgrade*>                       m_rolled;
    std::vector<std::unique_ptr<UpgradeCardUI>> m_cards;
};
