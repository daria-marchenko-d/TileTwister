#pragma once
#include "Grid.hpp"
#include "Direction.hpp"


class Game {

    public:

    Game();
    
    bool move(Direction dir);

    bool isWon() const;
    bool isLost() const;

    int getScore() const {return score;}
    const Grid& getGrid() const {return grid;}

    private:

    Grid grid;
    int score;
    
    bool has2048() const;

};