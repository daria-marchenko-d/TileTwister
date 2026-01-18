#!/bin/bash
echo "Compiling all integration tests..."
echo "=================================="

# Create build directory
mkdir -p build/tests

echo "1. Compiling test_grid_basic.cpp..."
g++ -std=c++17 -Iinclude -Ilib/doctest tests/test_grid_basic.cpp src/Grid.cpp -o build/tests/test_basic.exe

echo "2. Compiling test_grid_gameover.cpp..."
g++ -std=c++17 -Iinclude -Ilib/doctest tests/test_grid_gameover.cpp src/Grid.cpp -o build/tests/test_gameover.exe

echo "3. Compiling test_integration_grid_game.cpp..."
g++ -std=c++17 -Iinclude -Ilib/doctest tests/test_integration_grid_game.cpp src/Grid.cpp src/Game.cpp -o build/tests/test_integration_grid_game.exe

echo "4. Compiling test_integration_game_flow.cpp..."
g++ -std=c++17 -Iinclude -Ilib/doctest tests/test_integration_game_flow.cpp src/Grid.cpp src/Game.cpp -o build/tests/test_integration_game_flow.exe

echo "5. Compiling test_integration_advanced.cpp..."
g++ -std=c++17 -Iinclude -Ilib/doctest tests/test_integration_advanced.cpp src/Grid.cpp -o build/tests/test_integration_advanced.exe

echo ""
echo "Compilation complete! Files are in build/tests/"
