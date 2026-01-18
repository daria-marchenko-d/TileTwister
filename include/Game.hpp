#pragma once
#include "Grid.hpp"

class Game {
private:
    Grid grid;
    bool gameRunning;
    
public:
    Game();
    void start();                    // Start new game
    void processInput(int input);    // Process player input (0-3)
    void update();                   // Update game state
    void render() const;             // Display game (console)
    
    bool isRunning() const;
    const Grid& getGrid() const;
};