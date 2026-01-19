#pragma once
#include <array>
#include <vector>
#include <utility>
#include <random>

class Grid {
    
    public:
        static constexpr int N = 4;

        Grid();

        int at(int row, int col) const;
        
        void set(int row, int col, int value);

        void clear();

        std::vector<std::pair<int,int>> emptyCells() const;

        bool spawnTile();

        bool moveLeft(int& scoreGained);

        bool moveUp(int& scoreGained);

        bool moveRight(int& scoreGained);

        bool moveDown(int& scoreGained);

        private:

        static void reverseLine(std::array<int, N>& line);

        static bool slideAndMergeLeft(std::array<int, N>& line, int& scoreGained);

        std::array<std::array<int,N>, N> cells;

        static bool inBounds(int row, int col);

        std::mt19937 rng;
};