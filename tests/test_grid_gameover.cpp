#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest/doctest.h"
#include "../include/Grid.hpp"

TEST_CASE("Game over detection") {
    Grid grid;
    
    SUBCASE("New grid is not game over") {
        grid.initialize();
        CHECK(grid.isGameOver() == false);
    }
}