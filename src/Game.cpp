#include "Game.hpp"
#include <iostream>

Game::Game() : gameRunning(false) {}

void Game::start() {
    grid.initialize();
    gameRunning = true;
    std::cout << "Game started!\n";
}

void Game::processInput(int input) {
    if (!gameRunning) return;
    
    bool moved = grid.move(input);
    if (!moved) {
        std::cout << "Invalid move!\n";
    }
    
    update();
}

void Game::update() {
    if (grid.isGameWon()) {
        std::cout << "🎉 YOU WIN! Reached 2048!\n";
        gameRunning = false;
    } else if (grid.isGameOver()) {
        std::cout << "💀 GAME OVER! No more moves.\n";
        gameRunning = false;
    }
}

void Game::render() const {
    grid.print();
    
    if (grid.isGameWon()) {
        std::cout << "🎉 YOU WIN!\n";
    } else if (grid.isGameOver()) {
        std::cout << "💀 GAME OVER\n";
    }
}

bool Game::isRunning() const {
    return gameRunning;
}

const Grid& Game::getGrid() const {
    return grid;
}