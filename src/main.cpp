// #include <SDL3/SDL.h>
// #include <SDL3_ttf/SDL_ttf.h>
// #include <iostream>

// int main() {
//     std::cout << "Tile Twister starting...\n";
    
//     if (SDL_Init(SDL_INIT_VIDEO) != 0) {
//         std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
//         return 1;
//     }
    
//     // SDL3 TTF має іншу назву функції помилки
//     if (TTF_Init() != 0) {
//         std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
//         SDL_Quit();
//         return 1;
//     }
    
//     std::cout << "SDL3 initialized successfully!\n";
    
//     // Create a window
//     SDL_Window* window = SDL_CreateWindow("Tile Twister", 640, 480, 0);
//     if (!window) {
//         std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
//         TTF_Quit();
//         SDL_Quit();
//         return 1;
//     }
    
//     std::cout << "Window created. Closing in 2 seconds...\n";
//     SDL_Delay(2000);
    
//     SDL_DestroyWindow(window);
//     TTF_Quit();
//     SDL_Quit();
    
//     std::cout << "Game closed successfully.\n";
//     return 0;
// }
#include "Game.hpp"
#include <iostream>

// Test function (separate, not inside main)
void testGrid() {
    Grid grid;
    grid.initialize();
    
    std::cout << "Initial grid:\n";
    grid.print();
    
    // Test move right
    std::cout << "Moving RIGHT...\n";
    grid.move(1);
    grid.print();
    
    // Test move down
    std::cout << "Moving DOWN...\n";
    grid.move(2);
    grid.print();
    
    // Check game state
    if (grid.isGameOver()) {
        std::cout << "Game Over!\n";
    }
}

int main() {
    // Uncomment to run quick test first
    // testGrid();
    
    Game game;
    game.start();
    
    std::cout << "=== 2048 Console Test ===\n";
    std::cout << "WASD to move, Q to quit\n";
    
    char input;
    while (game.isRunning()) {
        game.render();
        
        std::cin >> input;
        
        switch (input) {
            case 'w': case 'W': game.processInput(0); break; // Up
            case 'd': case 'D': game.processInput(1); break; // Right
            case 's': case 'S': game.processInput(2); break; // Down
            case 'a': case 'A': game.processInput(3); break; // Left
            case 'q': case 'Q': return 0;
            default: std::cout << "Invalid input!\n";
        }
    }
    
    return 0;
}