#include "Game.hpp"

Game::Game()
    : score(0)
{
    grid.spawnTile();
    grid.spawnTile();
}


bool Game::move(Direction dir){
    int gained = 0;
    bool changed = false;

    switch (dir) {
        case Direction::Left:
        changed = grid.moveLeft(gained);
        break;

        case Direction::Right:
        changed = grid.moveRight(gained);
        break;

        case Direction::Up:
        changed = grid.moveUp(gained);
        break;

        case Direction::Down:
        changed = grid.moveDown(gained);
        break;
    }

    if (changed){
        score += gained;
        grid.spawnTile();
    }

    return changed;
}

bool Game::has2048() const{
    for (int r = 0; r < Grid::N; ++r){
        for (int c = 0; c < Grid::N; ++c){
            if (grid.at(r, c) ==2048){
                return true;
            }
        }
    }
    return false;
}

bool Game::isWon() const {
    return has2048();
}

bool Game::isLost()const{

    int dummy = 0;

    Grid test = grid;
    if(test.moveLeft(dummy)) return false;
    
    test = grid;
    if(test.moveRight(dummy)) return false;

    test = grid;
    if(test.moveUp(dummy)) return false;

    test = grid;
    if(test.moveDown(dummy)) return false;

    return true;
}