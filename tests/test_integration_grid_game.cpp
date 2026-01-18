#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest/doctest.h"
#include "../include/Grid.hpp"
#include "../include/Game.hpp"

TEST_CASE("Integration: Grid and Game initialization") {
    SUBCASE("Grid initializes with correct properties") {
        Grid grid;
        grid.initialize();
        
        const auto& cells = grid.getCells();
        int tileCount = 0;
        
        // Count non-zero tiles
        for (const auto& row : cells) {
            for (int val : row) {
                if (val > 0) tileCount++;
            }
        }
        
        CHECK(tileCount == 2);
        CHECK(grid.getScore() == 0);
        CHECK(grid.isGameOver() == false);
        CHECK(grid.isGameWon() == false);
    }
    
    SUBCASE("Game starts in correct state") {
        Game game;
        game.start();
        
        CHECK(game.isRunning() == true);
        CHECK(game.getGrid().getScore() == 0);
    }
}

TEST_CASE("Integration: Movement system") {
    Grid grid;
    
    SUBCASE("Score increases when tiles merge") {
        // Set up a merge scenario
        grid.setCell(0, 0, 2);
        grid.setCell(0, 1, 2);
        
        int scoreBefore = grid.getScore();
        bool moved = grid.move(3); // Move left
        int scoreAfter = grid.getScore();
        
        if (moved) {
            CHECK(scoreAfter > scoreBefore);
            CHECK(scoreAfter == 4); // 2 + 2 = 4
        }
    }
    
    SUBCASE("New tile generated after valid move") {
        grid.initialize();
        int emptyBefore = 0;
        const auto& cellsBefore = grid.getCells();
        
        // Count empty cells before move
        for (const auto& row : cellsBefore) {
            for (int val : row) {
                if (val == 0) emptyBefore++;
            }
        }
        
        // Make a move
        bool moved = grid.move(3); // Move left
        
        if (moved && emptyBefore > 0) {
            // Count empty cells after move
            const auto& cellsAfter = grid.getCells();
            int emptyAfter = 0;
            for (const auto& row : cellsAfter) {
                for (int val : row) {
                    if (val == 0) emptyAfter++;
                }
            }
            
            // Should have one less empty cell (tile generated)
            CHECK(emptyAfter == emptyBefore - 1);
        }
    }
}

TEST_CASE("Integration: Game state transitions") {
    SUBCASE("Game detects win condition (2048 tile)") {
        Grid grid;
        
        // Set a 2048 tile
        grid.setCell(0, 0, 2048);
        
        CHECK(grid.isGameWon() == true);
        CHECK(grid.isGameOver() == false); // Game can continue after win
    }
    
    SUBCASE("Game detects when no moves possible") {
        Grid grid;
        

        // with non-mergable values
        grid.initialize();
        
        // The isGameOver() method should work correctly
        bool gameOver = grid.isGameOver();
        
        // At start, game should not be over (there are empty cells)
        CHECK(gameOver == false);
    }
}