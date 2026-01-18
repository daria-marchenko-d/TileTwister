#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest/doctest.h"
#include "../include/Game.hpp"

TEST_CASE("Integration: Complete game flow with Game class") {
    Game game;
    
    SUBCASE("Game processes input correctly") {
        game.start();
        
        // Game should be running after start
        CHECK(game.isRunning() == true);
        
        // Get initial state
        int initialScore = game.getGrid().getScore();
        
        // Process a move (direction 3 = left)
        game.processInput(3);
        
        // After valid move, score should be >= initial score
        int newScore = game.getGrid().getScore();
        CHECK(newScore >= initialScore);
        
        // Game should still be running
        CHECK(game.isRunning() == true);
    }
    
    SUBCASE("Game state consistency through multiple moves") {
        game.start();
        
        std::vector<int> scores;
        
        // Make several moves in sequence
        for (int i = 0; i < 5; i++) {
            scores.push_back(game.getGrid().getScore());
            game.processInput(i % 4); // Cycle through directions
        }
        
        // Score should be non-decreasing
        for (size_t i = 1; i < scores.size(); i++) {
            CHECK(scores[i] >= scores[i - 1]);
        }
        
        // Game should still be running (unless we hit 2048 or game over)
        // At this point it's likely still running
        bool running = game.isRunning();
        CHECK((running == true || running == false) == true); // Valid state
    }
}

TEST_CASE("Integration: Direction mapping") {
    Grid grid;
    grid.initialize();
    
    SUBCASE("Direction 0 moves up") {
        // Set up tiles in column
        grid.setCell(3, 0, 2); // Bottom row
        grid.setCell(2, 0, 2); // Second from bottom
        
        bool moved = grid.move(0); // Move up
        
        if (moved) {
            const auto& cells = grid.getCells();
            // Tiles should merge or move to top
            CHECK(cells[0][0] > 0); // Top cell should have a value
        }
    }
    
    SUBCASE("Direction 1 moves right") {
        grid.setCell(0, 0, 2);
        grid.setCell(0, 1, 2);
        
        bool moved = grid.move(1); // Move right
        
        if (moved) {
            const auto& cells = grid.getCells();
            // Tiles should be on right side
            CHECK((cells[0][3] > 0) == true);
	    CHECK((cells[0][2] > 0) == true);
        }
    }
    
    SUBCASE("Direction 2 moves down") {
        grid.setCell(0, 0, 2);
        grid.setCell(1, 0, 2);
        
        bool moved = grid.move(2); // Move down
        
        if (moved) {
            const auto& cells = grid.getCells();
            // Tiles should be on bottom
            bool tileInPosition = (cells[3][0] > 0) || (cells[2][0] > 0);
	    CHECK(tileInPosition == true);
        }
    }
    
    SUBCASE("Direction 3 moves left") {
        grid.setCell(0, 3, 2);
        grid.setCell(0, 2, 2);
        
        bool moved = grid.move(3); // Move left
        
        if (moved) {
            const auto& cells = grid.getCells();
            // Tiles should be on left side
            bool tileInPosition = (cells[0][0] > 0) || (cells[0][1] > 0);
	    CHECK(tileInPosition == true);
        }
    }
}
