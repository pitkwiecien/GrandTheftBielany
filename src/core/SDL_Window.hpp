#pragma once
#include <SDL.h>
#include <string>

class Window {
public:
    Window(const std::string& title, int w, int h);
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    SDL_Window* handle() const { return m_window; }
    int width()  const { return m_w; }
    int height() const { return m_h; }

private:
    SDL_Window* m_window = nullptr;
    int m_w, m_h;
};