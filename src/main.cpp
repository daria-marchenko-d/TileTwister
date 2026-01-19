#include <SDL3/SDL.h>
#include <iostream>

#include "Game.hpp"
#include "Direction.hpp"
#include "RendererSDL.hpp"

int main(int, char**) {
    // 1) Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 1) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return 0;
    }

    // 2) Config UI
    UIConfig cfg;

    // 3) Fenêtre
    SDL_Window* window = SDL_CreateWindow(
        "2048 SDL3",
        cfg.windowW,
        cfg.windowH,
        0
    );
    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    // 4) Renderer (SDL3 -> 2 paramètres)
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 5) Jeu + Vue
    Game game;                 // crée la partie (spawn 2 tuiles si tu as suivi Game)
    RendererSDL view(renderer, cfg);

    bool running = true;

    // 6) Boucle principale
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
            else if (e.type == SDL_EVENT_KEY_DOWN) {
                switch (e.key.key) {
                    case SDLK_LEFT:
                        game.move(Direction::Left);
                        break;
                    case SDLK_RIGHT:
                        game.move(Direction::Right);
                        break;
                    case SDLK_UP:
                        game.move(Direction::Up);
                        break;
                    case SDLK_DOWN:
                        game.move(Direction::Down);
                        break;
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    default:
                        break;
                }
            }
        }

        // 7) Rendu
        view.render(game);

        // 8) Limiter un peu la charge CPU
        SDL_Delay(16); // ~60 FPS
    }

    // 9) Nettoyage
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
