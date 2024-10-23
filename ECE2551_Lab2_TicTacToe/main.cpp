#include <iostream>
#include <limits>
#include <string>

using namespace std;

void displayGrid(unsigned short row1, unsigned short row2, unsigned short row3);
bool isValidGame(unsigned short row1, unsigned short row2, unsigned short row3);
char checkWinner(unsigned short row1, unsigned short row2, unsigned short row3);
unsigned short getValidInput(const string& prompt);

int main() {
    unsigned short row1, row2, row3; //store the state of each row in the Tic-Tac-Toe grid --> row is represented as a 3-bit number (a value between 0 and 7).
    char playAgain;

    do {
        // Step 1: User Row Input
        row1 = getValidInput("Input Row #1 (Values between 0-7): ");
        row2 = getValidInput("Input Row #2 (Values between 0-7): ");
        row3 = getValidInput("Input Row #3 (Values between 0-7): ");

        // Step 2: Display 3x3 Grid
        displayGrid(row1, row2, row3);

        // Step 3: Validate Match
        if (!isValidGame(row1, row2, row3)) { //checks if the game setup is valid --> the number of X's should either be equal to the number of O's or  should be exactly one more X than O.
            cout << "Not a valid Tic-Tac-Toe game!\n"; 
            cout << "Play again.\n\n";
            continue; //if not valid prints message to skip the rest of the loop and start again
        }

        // Step 4: Who won?
        // Step 4: Who won?
char winner = checkWinner(row1, row2, row3); // Calls the function to check if there's a winner (either X, O, or T for tie)
if (winner != 'T') { // If the result is not a tie (i.e., someone won)
    string winningCombo;
    if (winner == 'X') { // If X won, figure out how X won
        // Check if any row is entirely filled with X's (binary 111 = 7)
        winningCombo = (row1 == 7 || row2 == 7 || row3 == 7) ? "Row Same" :

        // Check if all the first column values (left-most bit) in the rows are X (binary 1 in that bit position)
        ((row1 & 4) && (row2 & 4) && (row3 & 4)) ? "First Column Same" :

        // Check if all the second column values (middle bit) in the rows are X (binary 1 in that bit position)
        ((row1 & 2) && (row2 & 2) && (row3 & 2)) ? "Second Column Same" :

        // Check if all the third column values (right-most bit) in the rows are X (binary 1 in that bit position)
        ((row1 & 1) && (row2 & 1) && (row3 & 1)) ? "Third Column Same" :

        // Check if the left diagonal (top-left to bottom-right) is filled with X's (binary 100, 010, 001)
        ((row1 & 4) && (row2 & 2) && (row3 & 1)) ? "Left Diagonal Same" : 

        // Check if the right diagonal (top-right to bottom-left) is filled with X's (binary 001, 010, 100)
        "Right Diagonal Same";
    } else { // If O won, figure out how O won
        // Check if any row is entirely filled with O's (binary 000)
        winningCombo = (row1 == 0 || row2 == 0 || row3 == 0) ? "Row Same" :

        // Check if all the first column values (left-most bit) in the rows are O (binary 0 in that bit position)
        (!(row1 & 4) && !(row2 & 4) && !(row3 & 4)) ? "First Column Same" :

        // Check if all the second column values (middle bit) in the rows are O (binary 0 in that bit position)
        (!(row1 & 2) && !(row2 & 2) && !(row3 & 2)) ? "Second Column Same" :

        // Check if all the third column values (right-most bit) in the rows are O (binary 0 in that bit position)
        (!(row1 & 1) && !(row2 & 1) && !(row3 & 1)) ? "Third Column Same" :

        // Check if the left diagonal (top-left to bottom-right) is filled with O's (binary 000)
        (!(row1 & 4) && !(row2 & 2) && !(row3 & 1)) ? "Left Diagonal Same" : 

        // Check if the right diagonal (top-right to bottom-left) is filled with O's (binary 000)
        "Right Diagonal Same";
    }
    cout << winningCombo << endl; // Print the winning combination (row, column, or diagonal)
    cout << "Who won? " << winner << endl; // Print the winner (X or O)
} else {
    cout << "It's a tie!" << endl; // If no one won, it's a tie
}

        // Step 5: Play Again?
        cout << "Would you like to play again? (Y / N): ";
        cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');

    return 0; //signals that the program has finished running sucessfully
}

void displayGrid(unsigned short row1, unsigned short row2, unsigned short row3) { //uses bitwise operations to figure out if a spot is X or O and displays them in the 3x3 grid format
    cout << "The following 3x3 Tic-Tac-Toe was given:\n\n";
    cout << "  C1 C2 C3\n";
    cout << "+---+---+---+\n";
    cout << "| " << ((row1 & 4) ? 'X' : 'O') << " | " << ((row1 & 2) ? 'X' : 'O') << " | " << ((row1 & 1) ? 'X' : 'O') << " |\n";
    cout << "+---+---+---+\n";
    cout << "| " << ((row2 & 4) ? 'X' : 'O') << " | " << ((row2 & 2) ? 'X' : 'O') << " | " << ((row2 & 1) ? 'X' : 'O') << " |\n";
    cout << "+---+---+---+\n";
    cout << "| " << ((row3 & 4) ? 'X' : 'O') << " | " << ((row3 & 2) ? 'X' : 'O') << " | " << ((row3 & 1) ? 'X' : 'O') << " |\n";
    cout << "+---+---+---+\n";
}

bool isValidGame(unsigned short row1, unsigned short row2, unsigned short row3) {
    int xCount = 0, oCount = 0;
    for (int i = 0; i < 3; i++) {
        xCount += (row1 & (1 << i)) ? 1 : 0;
        xCount += (row2 & (1 << i)) ? 1 : 0;
        xCount += (row3 & (1 << i)) ? 1 : 0;
        oCount += (row1 & (1 << i)) ? 0 : 1;
        oCount += (row2 & (1 << i)) ? 0 : 1;
        oCount += (row3 & (1 << i)) ? 0 : 1;
    }
    return (xCount == oCount) || (xCount == oCount + 1);
}

char checkWinner(unsigned short row1, unsigned short row2, unsigned short row3) {
    // Check rows
    if (row1 == 7 || row2 == 7 || row3 == 7) return 'X';
    if (row1 == 0 || row2 == 0 || row3 == 0) return 'O';

    // Check columns
    for (int i = 0; i < 3; i++) {
        if ((row1 & (1 << i)) && (row2 & (1 << i)) && (row3 & (1 << i))) return 'X';
        if (!(row1 & (1 << i)) && !(row2 & (1 << i)) && !(row3 & (1 << i))) return 'O';
    }

    // Check diagonals
    if ((row1 & 4) && (row2 & 2) && (row3 & 1)) return 'X';
    if (!(row1 & 4) && !(row2 & 2) && !(row3 & 1)) return 'O';
    if ((row1 & 1) && (row2 & 2) && (row3 & 4)) return 'X';
    if (!(row1 & 1) && !(row2 & 2) && !(row3 & 4)) return 'O';

    return 'T'; // Tie
}

unsigned short getValidInput(const string& prompt) {
    unsigned short input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.fail() || input > 7) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << prompt;
        } else {
            break;
        }
    }
    return input;
}