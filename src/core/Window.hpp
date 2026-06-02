#pragma once
#include <SDL.h>
#include <string>

// owija SDL_Window
class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    SDL_Window* handle() const { return m_window; }
    int width()  const { return m_width; }
    int height() const { return m_height; }

private:
    SDL_Window* m_window = nullptr;
    int m_width  = 0;
    int m_height = 0;
};
