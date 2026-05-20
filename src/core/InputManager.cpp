#include "core/InputManager.hpp"

InputManager::InputManager() {
    m_keyState = SDL_GetKeyboardState(nullptr);
}

void InputManager::beginFrame() {
    m_pressed.fill(false);
    m_released.fill(false);
    m_mouseClicked = 0;
}

void InputManager::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_QUIT) {
        m_quit = true;
    } else if (e.type == SDL_KEYDOWN && !e.key.repeat) {
        m_pressed[e.key.keysym.scancode] = true;
    } else if (e.type == SDL_KEYUP) {
        m_released[e.key.keysym.scancode] = true;
    } else if (e.type == SDL_MOUSEMOTION) {
        m_mousePos = {static_cast<float>(e.motion.x),
                      static_cast<float>(e.motion.y)};
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        m_mouseClicked |= SDL_BUTTON(e.button.button);
    }
    m_mouseState = SDL_GetMouseState(nullptr, nullptr);
}

bool InputManager::isDown(SDL_Scancode key) const {
    return m_keyState[key] != 0;
}

bool InputManager::wasPressed(SDL_Scancode key) const {
    return m_pressed[key];
}

bool InputManager::wasReleased(SDL_Scancode key) const {
    return m_released[key];
}

bool InputManager::mouseDown(Uint8 button) const {
    return (m_mouseState & SDL_BUTTON(button)) != 0;
}

bool InputManager::mouseClicked(Uint8 button) const {
    return (m_mouseClicked & SDL_BUTTON(button)) != 0;
}
