#include <iostream>
#include <cstdlib>
using namespace std;

const int SIZE = 3;
char Matrix[SIZE][SIZE];

char Player = 'X';

// Ansi escape codes for colored text
const string RED = "\033[1;31m";
const string GREEN = "\033[1;32m";
const string YELLOW = "\033[1;33m";
const string BLUE = "\033[1;34m";
const string RESET = "\033[0m";

void initializeMatrix() {
    char counter = '1';
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Matrix[i][j] = counter++;
        }
    }
}

void printMatrix() {
    system("cls"); //For Clear Screen

    // Print top border
    cout << BLUE;
    for (int i = 0; i < SIZE * 4 + 1; i++) {
        cout << "-";
    }
    cout << RESET << endl;

    // Print matrix with borders
    for (int i = 0; i < SIZE; i++) {
        cout << BLUE << "| " << RESET;
        for (int j = 0; j < SIZE; j++) {
            if (Matrix[i][j] == 'X')
                cout << RED << Matrix[i][j] << " " << RESET;
            else if (Matrix[i][j] == 'O')
                cout << GREEN << Matrix[i][j] << " " << RESET;
            else
                cout << Matrix[i][j] << " ";
            cout << BLUE << "| " << RESET;
        }
        cout << endl;

        // Print separate between rows
        cout << BLUE;
        for (int k = 0; k < SIZE * 4 + 1; k++) {
            cout << "-";
        }
        cout << RESET << endl;
    }
    cout << endl;
}

void play() {
    char pos;
    bool validInput = false;

    cout << "Player " << Player << ", enter your position (1-" << SIZE*SIZE << "): ";
    cin >> pos;

    // Validate input
    while (!validInput) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (Matrix[i][j] == pos) {
                    Matrix[i][j] = Player;
                    validInput = true;
                }
            }
        }
        if (!validInput) {
            cout << "Invalid input. Please enter again: ";
            cin >> pos;
        }
    }

    // Switch player
    Player = (Player == 'X') ? 'O' : 'X';
}

char WhoWin() {
    // Check rows
    for (int i = 0; i < SIZE; i++) {
        if (Matrix[i][0] == Matrix[i][1] && Matrix[i][1] == Matrix[i][2])
            return Matrix[i][0];
    }

    // Check columns
    for (int i = 0; i < SIZE; i++) {
        if (Matrix[0][i] == Matrix[1][i] && Matrix[1][i] == Matrix[2][i])
            return Matrix[0][i];
    }

    // Check diagonals
    if (Matrix[0][0] == Matrix[1][1] && Matrix[1][1] == Matrix[2][2])
        return Matrix[0][0];
    if (Matrix[0][2] == Matrix[1][1] && Matrix[1][1] == Matrix[2][0])
        return Matrix[0][2];

    // Check for tie
    bool fullBoard = true;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (Matrix[i][j] != 'X' && Matrix[i][j] != 'O')
                fullBoard = false;
        }
    }
    if (fullBoard)
        return 'T'; // Tie

    return '.'; // Game still ongoing
}

int main() {
    initializeMatrix();

    char result = '.';
    while (result == '.') {
        printMatrix();
        play();
        result = WhoWin();
    }

    printMatrix();

    if (result == 'T')
        cout << YELLOW << "It's a tie!\n" << RESET;
    else
        cout << BLUE << "Player " << result << " wins!\n" << RESET;

    return 0;
}
