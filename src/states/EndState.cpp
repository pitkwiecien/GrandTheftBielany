#include "states/EndState.hpp"
#include "states/PlayState.hpp"
#include "core/Renderer.hpp"
#include "resources/TextureManager.hpp"
#include "resources/FontManager.hpp"
#include <string>

EndState::EndState(StateContext ctx, TextureManager& textures, FontManager& fonts, int finalWave)
    : m_ctx(ctx), m_textures(textures), m_fonts(fonts), m_finalWave(finalWave) {}

void EndState::onEnter() {
    m_titleFont = m_fonts.get("assets/fonts/DejaVuSans-Bold.ttf", 64);
    m_scoreFont = m_fonts.get("assets/fonts/DejaVuSans-Bold.ttf", 36);
    m_buttonFont = m_fonts.get("assets/fonts/DejaVuSans-Bold.ttf", 28);
    m_bgTexture = m_textures.get("assets/textures/screens/wasted_1080.png");

    const int buttonWidth = 220;
    const int buttonHeight = 60;
    const int centerY = 720 / 2 + 80;
    const int buttonGap = 40;

    m_playAgainRect = {1280 / 2 - buttonWidth - buttonGap / 2, centerY, buttonWidth, buttonHeight};
    m_exitRect = {1280 / 2 + buttonGap / 2, centerY, buttonWidth, buttonHeight};
}

bool EndState::hitTest(int px, int py, const SDL_Rect& rect) {
    return px >= rect.x && px < rect.x + rect.w && py >= rect.y && py < rect.y + rect.h;
}

void EndState::handleEvent(const SDL_Event& event) {
    if (event.type == SDL_MOUSEMOTION) {
        int mouseX = event.motion.x;
        int mouseY = event.motion.y;

        m_hoverPlayAgain = hitTest(mouseX, mouseY, m_playAgainRect);
        m_hoverExit = hitTest(mouseX, mouseY, m_exitRect);
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;

        if (hitTest(mouseX, mouseY, m_playAgainRect)) {
            m_ctx.states->replace(
                std::make_unique<PlayState>(m_ctx, m_textures, m_fonts));
        }
        else if (hitTest(mouseX, mouseY, m_exitRect)) {
            m_ctx.states->clear();
        }
    }
}

void EndState::update(float) {
}

void EndState::render(Renderer& renderer) {
    if (m_bgTexture) {
        SDL_Rect destinationRect{0, 0, 1280, 720};
        renderer.drawTexture(m_bgTexture, nullptr, &destinationRect);
    }

    auto drawCentered = [&](TTF_Font* font, const std::string& text, SDL_Color color, int y) {
        if (!font) {
            return;
        }
        
        SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
        if (!surface) {
            return;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.handle(), surface);
        SDL_FreeSurface(surface);
        if (!texture) {
            return;
        }

        int width;
        int height;
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        SDL_Rect destinationRect{(1280 - width) / 2, y, width, height};
        SDL_RenderCopy(renderer.handle(), texture, nullptr, &destinationRect);
        SDL_DestroyTexture(texture);
    };

    std::string scoreText = "You reached wave " + std::to_string(m_finalWave);
    drawCentered(m_scoreFont, scoreText, {255, 255, 255, 255}, 520);

    auto drawButton = [&](const SDL_Rect& rect, SDL_Color backgroundColor, bool isHovered, const std::string& label) {
        if (isHovered) {
            backgroundColor.r = static_cast<unsigned char>(backgroundColor.r * 0.75f);
            backgroundColor.g = static_cast<unsigned char>(backgroundColor.g * 0.75f);
            backgroundColor.b = static_cast<unsigned char>(backgroundColor.b * 0.75f);
        }

        SDL_SetRenderDrawColor(renderer.handle(), backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);
        SDL_RenderFillRect(renderer.handle(), &rect);
        SDL_SetRenderDrawColor(renderer.handle(), 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer.handle(), &rect);

        if (!m_buttonFont) {
            return;
        }

        SDL_Surface* surface = TTF_RenderUTF8_Blended(
            m_buttonFont,
            label.c_str(),
            {255, 255, 255, 255}
        );

        if (!surface) {
            return;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.handle(), surface);
        SDL_FreeSurface(surface);
        if (!texture) {
            return;
        }

        int textWidth;
        int textHeight;
        SDL_QueryTexture(texture, nullptr, nullptr, &textWidth, &textHeight);

        SDL_Rect destinationRect{
            rect.x + (rect.w - textWidth) / 2,
            rect.y + (rect.h - textHeight) / 2,
            textWidth,
            textHeight
        };
        SDL_RenderCopy(renderer.handle(), texture, nullptr, &destinationRect);
        SDL_DestroyTexture(texture);
    };

    drawButton( m_playAgainRect,{34, 139, 34, 255}, m_hoverPlayAgain, "Play Again");
    drawButton(m_exitRect, {180, 30, 30, 255}, m_hoverExit, "Exit");
}