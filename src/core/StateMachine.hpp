#pragma once
#include <SDL.h>
#include <memory>
#include <vector>

class GameState;
class Renderer;

// Stos stanów. Pozwala nakładać stany przezroczyste
// (np. LevelUpState na PlayState) bez gubienia gry pod spodem.
class StateMachine {
public:
    StateMachine();
    ~StateMachine();   // zdefiniowany w .cpp, gdzie GameState jest kompletny

    void push(std::unique_ptr<GameState> state);
    void pop();
    void replace(std::unique_ptr<GameState> state);
    void clear();

    // Wykonuje odłożone operacje (push/pop) — wywoływać raz na klatkę,
    // poza pętlą iteracji po stanach, żeby uniknąć inwalidacji.
    void applyPending();

    bool empty() const { return m_states.empty(); }
    GameState* current();

    // Przekazuje zdarzenie/update/render z uwzględnieniem przezroczystości.
    void handleEvent(const SDL_Event& e);
    void update(float dt);
    void render(Renderer& renderer);

private:
    enum class Action { None, Push, Pop, Replace, Clear };

    std::vector<std::unique_ptr<GameState>> m_states;
    std::unique_ptr<GameState>              m_pending;
    Action                                  m_action = Action::None;
};