#include "RendererSDL.hpp"
#include <algorithm>
#include <string>
#include <array>
#include <cstdint>

static constexpr std::array<std::array<uint8_t, 7>, 10> DIGITS = {{
    // 0
    { 0b01110,
      0b10001,
      0b10011,
      0b10101,
      0b11001,
      0b10001,
      0b01110 },
    // 1
    { 0b00100,
      0b01100,
      0b00100,
      0b00100,
      0b00100,
      0b00100,
      0b01110 },
    // 2
    { 0b01110,
      0b10001,
      0b00001,
      0b00010,
      0b00100,
      0b01000,
      0b11111 },
    // 3
    { 0b01110,
      0b10001,
      0b00001,
      0b00110,
      0b00001,
      0b10001,
      0b01110 },
    // 4
    { 0b00010,
      0b00110,
      0b01010,
      0b10010,
      0b11111,
      0b00010,
      0b00010 },
    // 5
    { 0b11111,
      0b10000,
      0b11110,
      0b00001,
      0b00001,
      0b10001,
      0b01110 },
    // 6
    { 0b00110,
      0b01000,
      0b10000,
      0b11110,
      0b10001,
      0b10001,
      0b01110 },
    // 7
    { 0b11111,
      0b00001,
      0b00010,
      0b00100,
      0b01000,
      0b01000,
      0b01000 },
    // 8
    { 0b01110,
      0b10001,
      0b10001,
      0b01110,
      0b10001,
      0b10001,
      0b01110 },
    // 9
    { 0b01110,
      0b10001,
      0b10001,
      0b01111,
      0b00001,
      0b00010,
      0b01100 }
}};

RendererSDL::RendererSDL(SDL_Renderer* r, UIConfig cfg)
    : renderer(r), cfg(cfg) {}

SDL_FRect RendererSDL::cellRect(int row, int col) const {
    int gridAreaW = cfg.windowW - 2 * cfg.padding;
    int gridAreaH = cfg.windowH - cfg.topBarH - 2 * cfg.padding;

    int gridSide = std::min(gridAreaW, gridAreaH);

    const int N = Grid::N;
    float cellSize = (gridSide - (N + 1) * cfg.gap) / float(N);

    float originX = float(cfg.padding);
    float originY = float(cfg.topBarH + cfg.padding);

    float x = originX + cfg.gap + col * (cellSize + cfg.gap);
    float y = originY + cfg.gap + row * (cellSize + cfg.gap);

    return SDL_FRect{ x, y, cellSize, cellSize };
}


void RendererSDL::drawDigit(int digit, float x, float y, float pixel, float gap) {
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);

    const auto& rows = DIGITS[digit];
    for (int r = 0; r < 7; ++r) {
        uint8_t bits = rows[r];
        for (int c = 0; c < 5; ++c) {
            bool on = ((bits >> (4 - c)) & 1) != 0;
            if (!on) continue;

            SDL_FRect p{
                x + c * (pixel + gap),
                y + r * (pixel + gap),
                pixel,
                pixel
            };
            SDL_RenderFillRect(renderer, &p);
        }
    }
}

void RendererSDL::drawNumber(int value, const SDL_FRect& tile) {
    if (value <= 0) return;

    std::string s = std::to_string(value);

    
    float pixel = tile.w / 24.0f;
    float gap   = pixel * 0.25f;

    float digitW  = 5 * pixel + 4 * gap;
    float digitH  = 7 * pixel + 6 * gap;
    float spacing = pixel * 2.0f;

    float totalW = float(s.size()) * digitW + float(s.size() - 1) * spacing;

    float startX = tile.x + (tile.w - totalW) / 2.0f;
    float startY = tile.y + (tile.h - digitH) / 2.0f;

    for (size_t i = 0; i < s.size(); ++i) {
        char ch = s[i];
        if (ch < '0' || ch > '9') continue;
        int d = ch - '0';

        float x = startX + float(i) * (digitW + spacing);
        float y = startY;
        drawDigit(d, x, y, pixel, gap);
    }
}

void RendererSDL::render(const Game& game) {
    SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
    SDL_RenderClear(renderer);

    const Grid& g = game.getGrid();

    for (int r = 0; r < Grid::N; ++r) {
        for (int c = 0; c < Grid::N; ++c) {
            int v = g.at(r, c);
            SDL_FRect rect = cellRect(r, c);

            if (v == 0) SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
            else        SDL_SetRenderDrawColor(renderer, 200, 160, 60, 255);

            SDL_RenderFillRect(renderer, &rect);

            
            if (v != 0) {
                drawNumber(v, rect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}
