#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest/doctest.h"
#include "../include/Grid.hpp"

TEST_CASE("Grid Initialization") {
    Grid grid;
    grid.initialize();
    
    SUBCASE("Score starts at 0") {
        CHECK(grid.getScore() == 0);
    }
    
    SUBCASE("Has exactly two tiles after initialization") {
        const auto& cells = grid.getCells();
        int tileCount = 0;
        for (const auto& row : cells) {
            for (int val : row) {
                if (val > 0) tileCount++;
            }
        }
        CHECK(tileCount == 2);
    }
    
    SUBCASE("Initial tiles are 2 or 4") {
        const auto& cells = grid.getCells();
        for (const auto& row : cells) {
            for (int val : row) {
                if (val > 0) {
                    bool validValue = (val == 2 || val == 4);
                    CHECK(validValue == true);
                }
            }
        }
    }
}