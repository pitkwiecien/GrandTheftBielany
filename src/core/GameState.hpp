#pragma once
#include <SDL.h>
#include "core/StateMachine.hpp"

class Renderer;
class InputManager;

// Kontekst przekazywany do stanów, żeby nie były globalne.
struct StateContext {
    StateMachine* states   = nullptr;
    Renderer*     renderer = nullptr;
    InputManager* input    = nullptr;
};

// Interfejs każdego stanu (menu, gra, level-up, pauza, koniec).
class GameState {
public:
    virtual ~GameState() = default;

    virtual void onEnter() {}
    virtual void onExit()  {}

    virtual void handleEvent(const SDL_Event& e) = 0;
    virtual void update(float dt)                = 0;
    virtual void render(Renderer& renderer)      = 0;

    // true => stan pod spodem nadal jest rysowany
    // (level-up / pauza renderowane na wierzchu gry).
    virtual bool isTransparent() const { return false; }
};
