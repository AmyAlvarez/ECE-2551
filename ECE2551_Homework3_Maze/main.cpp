//Homework 2 - Maze Solver by Amy Alvarez 
#include "solver.h"  // Include the solver header file

int main() {
    // data representing the maze
    short test[16] = {
        8704, static_cast<short>(43967), static_cast<short>(43904),
        static_cast<short>(35774), static_cast<short>(54184), 21419, 
        24456, 18366, 30114, static_cast<short>(55208), 30639, 
        1967, 32303, 16543, 5824, static_cast<short>(62206)
    };

    // load the test data into mazeRows
    inputTestData(test);

    // display the given maze
    std::cout << "Initial Maze:\n";
    showMaze();

    // try to solve the maze starting from (0, 0)
    if (move(0, 0)) {
        std::cout << "\nSolved Maze:\n";
    } else {
        std::cout << "\nNo solution found.\n";
    }

    // display the solved maze (if possible)
    showMaze();

    return 0;
}
