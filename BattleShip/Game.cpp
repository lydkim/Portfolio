/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Game.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Anna Torell, Lydia Kim
 * atorell, lydkim
 *
 * Project 4: Battleship
 *
 * Implementation of the battleship game for the class Game.
 */

#include <fstream>

#include "Game.h"


Game::Game() {
    p1 = Player();
    p2 = Player();
}

Game::Game(Player player1, string grid1, Player player2, string grid2) {
    p1 = player1;
    p2 = player2;
    //if the string is not empty, use that for the grid
    if (grid1 != "") {
        p1.load_grid_file(grid1);
    }
    //if string is empty, generate a random grid
    else {
        generate_random_grid(p1);
        cout << "Generating random grid for " << p1.get_name();
    }
    //if the string is not empty, use that for the grid
    if (grid2 != "") {
        p2.load_grid_file(grid2);
    }
    //if string is empty, generate a random grid
    else {
        generate_random_grid(p2);
        cout << "Generating random grid for " << p2.get_name();
    }
}

Player Game::get_p1() {
    return p1;
}

Player Game::get_p2() {
    return p2;
}

string Game::get_move(string player_name) {
    string move;
    //player is prompted to enter move
    cout << player_name << " enter your move: ";
    cin >> move;
    return move;
}

bool Game::check_valid_move(string move) {
    //if the size of the string is 2
    if (move.size() == 2) {
        char row;
        row = move.at(0);
        char col;
        col = toupper(move.at(1));
        //if the column is between a and h regardless of case, the
        //move is valid
        if (col >= 'A' && col <= 'H' && row >= '1' && row <= '8') {
            return true;
        }
        //tells user position is invalid
        else {
            cout << p1.get_name() << " you entered an invalid position";
            return false;
        }
    }
    //tells user input is invalid
    else {
        cout << p1.get_name() << " you entered an invalid input";
        return false;
    }
}

void Game::start(char difficulty, int max_num_rounds) {
    //establishes variables for the round number, string of the move,
    //the position of row and column
    string move;
    int numRound = 0;
    char rowPos;
    char colPos;
    //while all ships are not sunk and the game hasnt finished, we get moves
    while (numRound < max_num_rounds && !p1.destroyed() && !p2.destroyed()) {
        move = get_move(p1.get_name());
        cout << endl;
        //repeats while the move is invalid
        while (!check_valid_move(move)) {
            move = get_move(p1.get_name());
            cout << endl;
        }
        //assigns the row and column to the values in move string
        rowPos = move.at(0);
        colPos = move.at(1);
        Position move(rowPos, colPos);
        p1.attack(p2, move);
        //if player 2 ship is not sunk
        if (!p2.destroyed()) {
            opponent_make_move(difficulty);
        }
        //prints both player and opponent grids
        cout << "Your grid" << endl;
        p1.print_grid();
        cout << p2.get_name() << "'s grid" << endl;
        p1.print_guess_grid();
        numRound = numRound + 1;
    }
    //if all ships for either player sunk then announce game over
    if (p1.destroyed()) {
        cout << "Game over, winner is " << p2.get_name() << " in " <<
        numRound << " rounds" << endl;
    }
    else if (p2.destroyed()) {
        cout << "Game over, winner is " << p1.get_name() << " in " <<
        numRound << " rounds" << endl;
    }
    else {
        cout << "Game over, winner is no one in " << numRound <<
        " rounds" << endl;
    }
}

// Your code goes above this line.
// Don't change the implementations below!

void Game::generate_random_grid(Player &p) {
    // grid to check which position has been taken
    bool grid[MAX_GRID_SIZE][MAX_GRID_SIZE] = {{false}};

    for (int k = 0; k < 10 && p.get_num_ships() < 5; k++) {
        // i is the length of the ship to be made
        // decrementing i to create 2 ships of size 3
        int i = p.get_num_ships() + 1;
        if (i > 2) {
            i--;
        }

        // generate random position 1
        int row = get_random_number() % MAX_GRID_SIZE;
        int col = get_random_number() % MAX_GRID_SIZE;
        Position pos1(row, col);

        if (!grid[row][col]) {
            Position pos2;
            // Check if creating position two is not off the grid relative to
            // position 1 inthe order of bottom, right, left, top
            if (row + i < MAX_GRID_SIZE) {
                pos2 = Position(row + i, col);
            } else if (col + i < MAX_GRID_SIZE) {
                pos2 = Position(row, col + i);
            } else if (col - i >= 0) {
                pos2 = Position(row, col - i);
            } else if (row - i >= 0) {
                pos2 = Position(row - i, col);
            } else {
                continue;
            }

            Ship s(pos1, pos2);

            bool pos2_taken = false;
            if (s.is_horizontal()) {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_col() < pos2.get_col() ?
                            pos1.get_col() : pos2.get_col();
                int end = pos1.get_col() < pos2.get_col() ?
                          pos2.get_col() : pos1.get_col();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[pos1.get_row()][j]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[pos1.get_row()][j] = true;
                }
            } else {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_row() < pos2.get_row() ?
                            pos1.get_row() : pos2.get_row();
                int end = pos1.get_row() < pos2.get_row() ?
                          pos2.get_row() : pos1.get_row();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[j][pos1.get_col()]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[j][pos1.get_col()] = true;
                }
            }

            // Restart from beginning
            if (pos2_taken) {
                continue;
            }

            // Add the ship to p2's ships
            p.add_ship(s);
        }
    }
}

void Game::opponent_make_move(char difficulty) {
    if (difficulty == EMULATE) {
        Position next;
        cout << "Enter CPU emulation move: ";
        cin >> next;
        cout << endl;
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
    } else if (difficulty == EASY) {
#ifndef NOCPU
        int randRow = get_random_number() % MAX_GRID_SIZE;
        int randCol = get_random_number() % MAX_GRID_SIZE;
        Position randCoord(randRow, randCol);
        p2.attack(p1, randCoord);
        cout << "You received an attack at " << randCoord << endl << endl;
#else
        Position next;
        cin >> next;
        if (cin.fail()) {
            cin.clear();
            next = Position(7, 4);
        }
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
#endif
    } else if (difficulty == MEDIUM) {
        // Simple AI that checks right, bottom, left, top of hit position
        // TODO: implement for S'more version
    }
}

