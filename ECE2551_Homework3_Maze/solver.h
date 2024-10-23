#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <iomanip>
#include <cstring>

// enum to specify the bit type: Maze or Path
enum BitType { Maze, Path };

// arrays to store maze and path data
short mazeRows[16] = {0};
short pathRows[16] = {0};

// function to input test data into mazeRows
void inputTestData(short data[]) {
    std::memcpy(mazeRows, data, sizeof(mazeRows));
}

// function to get a bit value from mazeRows or pathRows
short getBit(BitType type, int x, int y) {
    short row = (type == Maze) ? mazeRows[y] : pathRows[y];
    return (row >> (15 - x)) & 1;
}

// function to set a bit in pathRows
void setPathBit(int x, int y) {
    pathRows[y] |= (1 << (15 - x));
}

// function to clear the pathRows by setting all bits to zero
void clearPath() {
    std::memset(pathRows, 0, sizeof(pathRows));
}

void showMaze() {
    for (int y = 0; y < 16; ++y) {
        for (int x = 0; x < 16; ++x) {
            // ff the position is part of the path, print '*'
            if (getBit(Path, x, y)) {
                std::cout << "* ";
            } else {
                // otherwise, print the original maze value (0 or 1)
                std::cout << getBit(Maze, x, y) << " ";
            }
        }
        std::cout << "\n";
    }
}


// recursive function to solve the maze
bool move(int x, int y) {
    // base case --> if out of bounds or on a wall or visited spot, backtrack
    if (x < 0 || y < 0 || x >= 16 || y >= 16 || getBit(Maze, x, y) == 1 || getBit(Path, x, y) == 1) {
        return false;
    }

    // mark  current position in the path
    setPathBit(x, y);

    // base case --> if  reached the bottom-right corner, solution was found
    if (x == 15 && y == 15) {
        return true;
    }

    // recursive cases --> try to move in the priority order: right, down, left, up
    if (move(x + 1, y) ||  // Move right
        move(x, y + 1) ||  // Move down
        move(x - 1, y) ||  // Move left
        move(x, y - 1)) {  // Move up
        return true;
    }

    // if no valid move is found, backtrack by clearing the current bit in the path
    pathRows[y] &= ~(1 << (15 - x));
    return false;
}

#endif // SOLVER_H