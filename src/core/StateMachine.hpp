#pragma once
#include <SDL.h>
#include <memory>
#include <vector>

class GameState;
class Renderer;

// Stos stanów, pozwala nakładać stany przezroczyste (np. LevelUpState na PlayState)
class StateMachine {
public:
    StateMachine();
    ~StateMachine();

    void push(std::unique_ptr<GameState> state);
    void pop();
    void replace(std::unique_ptr<GameState> state);
    void clear();
    // wykonanie odlozonych operacji (push/pop)
    void applyPending();
    bool empty() const { return m_states.empty(); }

    // przekazuje zdarzenie/update/render z uwzględnieniem przezroczystości.
    void handleEvent(const SDL_Event& e);
    void update(float dt);
    void render(Renderer& renderer);

private:
    enum class Action { None, Push, Pop, Replace, Clear };

    std::vector<std::unique_ptr<GameState>> m_states;
    std::unique_ptr<GameState> m_pending;
    Action m_action = Action::None;
};