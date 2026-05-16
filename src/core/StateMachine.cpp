#include "StateMachine.hpp"
#include "GameState.hpp"   // pełna definicja — kluczowe dla unique_ptr<GameState>

// Konstruktor i destruktor MUSZĄ być tutaj (nie w nagłówku),
// bo to tu GameState jest typem kompletnym i unique_ptr
// może wygenerować poprawny kod niszczący stany.
StateMachine::StateMachine()  = default;
StateMachine::~StateMachine() = default;

void StateMachine::push(std::unique_ptr<GameState> state) {
    m_pending = std::move(state);
    m_action  = Action::Push;
}

void StateMachine::pop() {
    m_action = Action::Pop;
}

void StateMachine::replace(std::unique_ptr<GameState> state) {
    m_pending = std::move(state);
    m_action  = Action::Replace;
}

void StateMachine::clear() {
    m_action = Action::Clear;
}

void StateMachine::applyPending() {
    switch (m_action) {
        case Action::Push:
            if (!m_states.empty() && m_states.back())
                m_states.back()->onExit();
            m_states.push_back(std::move(m_pending));
            m_states.back()->onEnter();
            break;

        case Action::Pop:
            if (!m_states.empty()) {
                m_states.back()->onExit();
                m_states.pop_back();
                if (!m_states.empty())
                    m_states.back()->onEnter();
            }
            break;

        case Action::Replace:
            if (!m_states.empty()) {
                m_states.back()->onExit();
                m_states.pop_back();
            }
            m_states.push_back(std::move(m_pending));
            m_states.back()->onEnter();
            break;

        case Action::Clear:
            while (!m_states.empty()) {
                m_states.back()->onExit();
                m_states.pop_back();
            }
            break;

        case Action::None:
        default:
            break;
    }
    m_action  = Action::None;
    m_pending = nullptr;
}

GameState* StateMachine::current() {
    return m_states.empty() ? nullptr : m_states.back().get();
}

void StateMachine::handleEvent(const SDL_Event& e) {
    if (!m_states.empty())
        m_states.back()->handleEvent(e);
}

void StateMachine::update(float dt) {
    if (!m_states.empty())
        m_states.back()->update(dt);
}

void StateMachine::render(Renderer& renderer) {
    if (m_states.empty()) return;

    // Znajdź najniższy stan, od którego trzeba zacząć rysowanie:
    // stany przezroczyste (pauza, level-up) pokazują to, co pod nimi.
    std::size_t start = m_states.size() - 1;
    while (start > 0 && m_states[start]->isTransparent())
        --start;

    for (std::size_t i = start; i < m_states.size(); ++i)
        m_states[i]->render(renderer);
}