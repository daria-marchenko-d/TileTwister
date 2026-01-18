#pragma once
#include <vector>
#include <iostream>

class Grid {
private:
    std::vector<std::vector<int>> cells;  // 4x4 grid
    int score;
    
    bool moveHorizontal(bool left);       // left/right movement
    bool moveVertical(bool up);           // up/down movement
    void addTile();                       // add 2 or 4 to random empty cell
    bool canMove() const;                 // check if any move possible
    
public:
    Grid();
    
    // Core methods
    void initialize();                    // start new game
    bool move(int direction);             // 0:up, 1:right, 2:down, 3:left
    void print() const;                   // display grid to console
    
    // Game state
    bool isGameOver() const;
    bool isGameWon() const;               // check for 2048 tile
    int getScore() const;
    
    // Accessors for testing
    const std::vector<std::vector<int>>& getCells() const;
    void setCell(int row, int col, int value);  // for testing
};