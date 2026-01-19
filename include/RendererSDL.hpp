#pragma once
#include <SDL3/SDL.h>
#include <Game.hpp>
#include <array>
#include <cstdint>

struct UIConfig {
    int windowW = 520;
    int windowH = 640;

    int topBarH = 100;
    int padding = 20;
    int gap = 20;

};

class RendererSDL {

    public:
    RendererSDL(SDL_Renderer* r, UIConfig cfg);

    void render(const Game& game);

    private:
    SDL_Renderer* renderer;
    UIConfig cfg;

    SDL_FRect cellRect(int row, int col) const ;

    void drawDigit(int digit, float x, float y, float pixel, float gap);
    void drawNumber( int value, const SDL_FRect& tile);

};
