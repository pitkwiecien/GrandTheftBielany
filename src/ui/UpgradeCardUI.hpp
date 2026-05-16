#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include <functional>

class Renderer;
class InputManager;
class Text;
class TextureManager;
struct Upgrade;

// Jedna karta na ekranie level-up: nazwa, opis, ikona, ramka
// kolorowana wg rzadkości. Klik wybiera to ulepszenie.
class UpgradeCardUI {
public:
    UpgradeCardUI(Renderer& renderer, TTF_Font* titleFont,
                  TTF_Font* bodyFont, TextureManager& textures);

    void setUpgrade(Upgrade* upgrade, SDL_Rect bounds);
    void setOnPick(std::function<void(Upgrade*)> cb) { m_onPick = std::move(cb); }

    void update(const InputManager& input);
    void render(Renderer& renderer);

private:
    SDL_Color rarityColor() const;

    Upgrade*                       m_upgrade = nullptr;
    SDL_Rect                       m_bounds{};
    TextureManager&                m_textures;
    std::unique_ptr<Text>          m_title;
    std::unique_ptr<Text>          m_body;
    std::function<void(Upgrade*)>  m_onPick;
    bool                           m_hovered = false;
};
