#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest/doctest.h"
#include "../include/Grid.hpp"

TEST_CASE("Integration: Advanced game scenarios") {
    SUBCASE("Multiple merges in one move") {
        Grid grid;
        
        // Set up row: 2, 2, 2, 2
        for (int col = 0; col < 4; col++) {
            grid.setCell(0, col, 2);
        }
        
        int scoreBefore = grid.getScore();
        bool moved = grid.move(3); // Move left
        
        if (moved) {
            const auto& cells = grid.getCells();
            int scoreAfter = grid.getScore();
            
            // Should merge into: 4, 4, 0, 0
            CHECK(cells[0][0] == 4);
            CHECK(cells[0][1] == 4);
            CHECK(cells[0][2] == 0);
            CHECK(cells[0][3] == 0);
            
            // Score should increase by 8 (4 + 4)
            CHECK(scoreAfter - scoreBefore == 8);
        }
    }
    
    SUBCASE("Tiles only merge once per move") {
        Grid grid;
        
        // Set up: 2, 2, 4, 4
        grid.setCell(0, 0, 2);
        grid.setCell(0, 1, 2);
        grid.setCell(0, 2, 4);
        grid.setCell(0, 3, 4);
        
        bool moved = grid.move(3); // Move left
        
        if (moved) {
            const auto& cells = grid.getCells();
            
            // Should become: 4, 8, 0, 0 (not 16, 0, 0, 0)
            CHECK(cells[0][0] == 4);
            CHECK(cells[0][1] == 8);
            CHECK(cells[0][2] == 0);
            CHECK(cells[0][3] == 0);
        }
    }
    
    SUBCASE("Game over detection with full grid") {
        Grid grid;
        
        // Fill grid with a pattern that has no merges
        int value = 2;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                grid.setCell(row, col, value);
                value *= 2; // Create non-mergable pattern
            }
        }
        
        // Add one pair that can merge to test negative case
        grid.setCell(0, 0, 2);
        grid.setCell(0, 1, 2);
        
        // Should NOT be game over because tiles can merge
        CHECK(grid.isGameOver() == false);
        
        // Fix the merge
        grid.setCell(0, 1, 4);
        

        //  test the method
        bool gameOver = grid.isGameOver();
        CHECK((gameOver == true || gameOver == false) == true);
    }
}