#pragma once
#include <SDL.h>
#include <functional>
#include <string>
#include <memory>
#include "Text.hpp"

class Renderer;
class InputManager;

// Klikalny przycisk (menu, karty ulepszeń). Sam liczy stan
// hover/pressed z pozycji myszy i wywołuje onClick.
class Button {
public:
    Button(Renderer& renderer, TTF_Font* font,
           const std::string& label, SDL_Rect bounds);

    void setOnClick(std::function<void()> cb) { m_onClick = std::move(cb); }
    void setBounds(SDL_Rect b) { m_bounds = b; }

    void update(const InputManager& input);
    void render(Renderer& renderer);

private:
    SDL_Rect              m_bounds{};
    std::unique_ptr<Text> m_label;
    std::function<void()> m_onClick;
    bool                  m_hovered = false;
    bool                  m_pressed = false;
};
