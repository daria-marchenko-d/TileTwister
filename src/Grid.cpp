#include "Grid.hpp"
#include <stdexcept>
#include <algorithm>
#include <utility>

Grid::Grid()
    : rng(std::random_device{}())
{
    clear();
}

void Grid::reverseLine(std::array<int, N>& line){
    for (int i = 0; i < Grid::N / 2; ++i){
        std::swap(line[i], line[Grid::N - 1 - i]);
    }
}
bool Grid::inBounds(int row, int col) {
    return row >= 0 && row < N && col >= 0 && col < N;
}

int Grid::at(int row, int col) const {

    if (!inBounds(row, col )) {
        throw std::out_of_range("Grid::at - index out of bounds");
    }
    return cells[row][col];
}

void Grid::set(int row, int col, int value) {

    if (!inBounds(row, col )) {
        throw std::out_of_range("Grid::set - index out of bounds");
    }
    cells[row][col] = value;
}

void Grid::clear() {

    for (auto& row : cells){
        row.fill(0);
    }
}

bool Grid::spawnTile() {
    auto empties = emptyCells();
    if (empties.empty()) {
        return false;
    }

    std::uniform_int_distribution<int> pickIndex(
        0, static_cast<int>(empties.size()) - 1
    );
    auto [r, c] = empties[pickIndex(rng)];

    std::uniform_int_distribution<int> pickPercent(1, 100);
    int value = (pickPercent(rng) <= 90) ? 2 : 4;

    cells[r][c] = value;
    return true;
}

bool Grid::slideAndMergeLeft(std::array<int, N>& line, int& scoreGained){

    auto original = line;

    std::array<int, N> tmp{};
    int k = 0;
    for (int i = 0; i < N; ++i){
        if (line[i] != 0){
            tmp[k++] = line[i];
        }
    }

    for (int i = 0; i < N -1; ++i){
        if (tmp[i] != 0 && tmp[i] ==tmp[i + 1]) {
            tmp[i] *= 2;
            scoreGained += tmp[i];
            tmp[i + 1] = 0;
        }
    }

    line.fill(0);
    k = 0;
    for (int i = 0; i < N; ++i){
        if (tmp[i != 0]) {
            line[k++] = tmp[i];
        }
    }

    return line != original;
}

bool Grid::moveLeft(int& scoreGained){
    bool changed = false;

    for (int r = 0; r < N; ++r) {
        changed |= slideAndMergeLeft(cells[r], scoreGained);
    }

    return changed;
}


bool Grid::moveRight(int& scoreGained) {
    bool changed = false;

    for ( int r = 0; r< N; ++r) {
        std::array<int, N> line = cells[r];
        reverseLine(line);

        bool linechanged = slideAndMergeLeft(line, scoreGained);

        reverseLine(line);
        cells[r] = line;

        changed |= linechanged;
    }

    return changed;
}

bool Grid::moveUp(int& scoreGained){
    bool changed = false;

    for (int c = 0; c < N; ++c) {
        std::array<int, N> col{};
        for (int r = 0; r < N; ++r) {
            col[r] = cells[r][c];
        }

        bool colchanged = slideAndMergeLeft(col, scoreGained);

        for (int r = 0; r < N; ++r){
            cells[r][c] = col[r];
        }
        changed |= colchanged;
    }

    return changed;
}

bool Grid::moveDown(int& scoreGained) {
    bool changed = false;

    for (int c = 0; c < N; ++c){
        std::array<int, N> col{};
        for (int r = 0; r < N; ++r){
            col[r]= cells[r][c];
        }

        reverseLine(col);
        bool colChanged = slideAndMergeLeft(col, scoreGained);
        reverseLine(col);

        for (int r = 0; r < N; ++r){
            cells[r][c] = col[r];
        }

        changed |= colChanged;
    }

    return changed;
}

std::vector<std::pair<int,int>> Grid::emptyCells() const {

    std::vector<std::pair<int,int>> out ;
    out.reserve(N *N);

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (cells[r][c] == 0) {
                out.emplace_back(r, c);
            }
        }
    }
    return out;
}




