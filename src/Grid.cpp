// #include "Grid.hpp"
// #include <cstdlib>
// #include <ctime>

// Grid::Grid() : score(0) {
//     cells.resize(4, std::vector<int>(4, 0));
//     std::srand(std::time(nullptr));
// }

// void Grid::initialize() {
//     // Reset all cells to 0
//     for (auto& row : cells) {
//         std::fill(row.begin(), row.end(), 0);
//     }
//     score = 0;
    
//     // Add two initial tiles
//     addTile();
//     addTile();
// }

// bool Grid::move(int direction) {
//     // Implementation of move logic
//     // Returns true if any tile moved
// }

// void Grid::print() const {
//     for (const auto& row : cells) {
//         for (int val : row) {
//             if (val == 0) std::cout << ".";
//             else std::cout << val;
//             std::cout << "\t";
//         }
//         std::cout << std::endl;
//     }
//     std::cout << "Score: " << score << std::endl;
// }
#include "Grid.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>

// Constructor
Grid::Grid() : score(0) {
    cells.resize(4, std::vector<int>(4, 0));
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

// Initialize new game
void Grid::initialize() {
    // Reset all cells to 0
    for (auto& row : cells) {
        std::fill(row.begin(), row.end(), 0);
    }
    score = 0;
    
    // Add two initial tiles
    addTile();
    addTile();
}

// Add random tile (2 or 4) to empty cell
void Grid::addTile() {
    // Collect all empty cells
    std::vector<std::pair<int, int>> emptyCells;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (cells[row][col] == 0) {
                emptyCells.push_back({row, col});
            }
        }
    }
    
    // If no empty cells, return
    if (emptyCells.empty()) return;
    
    // Choose random empty cell
    int index = std::rand() % emptyCells.size();
    int row = emptyCells[index].first;
    int col = emptyCells[index].second;
    
    // 90% chance for 2, 10% chance for 4
    cells[row][col] = (std::rand() % 10 == 0) ? 4 : 2;
}

// Move tiles horizontally (left or right)
bool Grid::moveHorizontal(bool left) {
    bool moved = false;
    
    for (int row = 0; row < 4; ++row) {
        // Extract non-zero values from current row
        std::vector<int> currentRow;
        for (int col = 0; col < 4; ++col) {
            if (cells[row][col] != 0) {
                currentRow.push_back(cells[row][col]);
            }
        }
        
        // If moving right, reverse the order
        if (!left) {
            std::reverse(currentRow.begin(), currentRow.end());
        }
        
        // Merge adjacent equal tiles
        std::vector<int> newRow;
        for (size_t i = 0; i < currentRow.size(); ++i) {
            if (i + 1 < currentRow.size() && currentRow[i] == currentRow[i + 1]) {
                // Merge tiles
                newRow.push_back(currentRow[i] * 2);
                score += currentRow[i] * 2;  // Add to score
                ++i;  // Skip next tile (already merged)
                moved = true;
            } else {
                newRow.push_back(currentRow[i]);
            }
        }
        
        // Pad with zeros
        while (newRow.size() < 4) {
            newRow.push_back(0);
        }
        
        // If moving right, reverse back
        if (!left) {
            std::reverse(newRow.begin(), newRow.end());
        }
        
        // Check if row changed
        for (int col = 0; col < 4; ++col) {
            if (cells[row][col] != newRow[col]) {
                moved = true;
            }
            cells[row][col] = newRow[col];
        }
    }
    
    return moved;
}

// Move tiles vertically (up or down)
bool Grid::moveVertical(bool up) {
    bool moved = false;
    
    for (int col = 0; col < 4; ++col) {
        // Extract non-zero values from current column
        std::vector<int> currentCol;
        for (int row = 0; row < 4; ++row) {
            if (cells[row][col] != 0) {
                currentCol.push_back(cells[row][col]);
            }
        }
        
        // If moving down, reverse the order
        if (!up) {
            std::reverse(currentCol.begin(), currentCol.end());
        }
        
        // Merge adjacent equal tiles
        std::vector<int> newCol;
        for (size_t i = 0; i < currentCol.size(); ++i) {
            if (i + 1 < currentCol.size() && currentCol[i] == currentCol[i + 1]) {
                // Merge tiles
                newCol.push_back(currentCol[i] * 2);
                score += currentCol[i] * 2;  // Add to score
                ++i;  // Skip next tile
                moved = true;
            } else {
                newCol.push_back(currentCol[i]);
            }
        }
        
        // Pad with zeros
        while (newCol.size() < 4) {
            newCol.push_back(0);
        }
        
        // If moving down, reverse back
        if (!up) {
            std::reverse(newCol.begin(), newCol.end());
        }
        
        // Check if column changed
        for (int row = 0; row < 4; ++row) {
            if (cells[row][col] != newCol[row]) {
                moved = true;
            }
            cells[row][col] = newCol[row];
        }
    }
    
    return moved;
}

// Main move method (0:up, 1:right, 2:down, 3:left)
bool Grid::move(int direction) {
    bool moved = false;
    
    switch (direction) {
        case 0: moved = moveVertical(true); break;    // Up
        case 1: moved = moveHorizontal(false); break; // Right
        case 2: moved = moveVertical(false); break;   // Down
        case 3: moved = moveHorizontal(true); break;  // Left
        default: return false;
    }
    
    // If tiles moved, add new tile
    if (moved) {
        addTile();
    }
    
    return moved;
}

// Display grid to console
void Grid::print() const {
    std::cout << "-----------------------------\n";
    for (const auto& row : cells) {
        std::cout << "|";
        for (int val : row) {
            if (val == 0) {
                std::cout << "     |";
            } else {
                printf(" %4d|", val);
            }
        }
        std::cout << "\n";
        std::cout << "-----------------------------\n";
    }
    std::cout << "Score: " << score << "\n\n";
}

// Check if game is over (no moves possible)
bool Grid::isGameOver() const {
    // If there are empty cells, game is not over
    for (const auto& row : cells) {
        for (int val : row) {
            if (val == 0) return false;
        }
    }
    
    // Check if any adjacent tiles can be merged
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            int current = cells[row][col];
            
            // Check right neighbor
            if (col < 3 && current == cells[row][col + 1]) return false;
            
            // Check bottom neighbor
            if (row < 3 && current == cells[row + 1][col]) return false;
        }
    }
    
    return true;
}

// Check if player won (has 2048 tile)
bool Grid::isGameWon() const {
    for (const auto& row : cells) {
        for (int val : row) {
            if (val == 2048) return true;
        }
    }
    return false;
}

// Get current score
int Grid::getScore() const {
    return score;
}

// Get cells (for testing)
const std::vector<std::vector<int>>& Grid::getCells() const {
    return cells;
}

// Set cell value (for testing)
void Grid::setCell(int row, int col, int value) {
    if (row >= 0 && row < 4 && col >= 0 && col < 4) {
        cells[row][col] = value;
    }
}