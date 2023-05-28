/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Player.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Anna Torell, Lydia Kim
 * atorell, lydkim
 *
 * Project 4: Battleship
 *
 * Player is representing an actual player in the Battleship hame
 * There will be two players
 * Each player has a grid with their ship.
 */

#include <fstream>

#include "Player.h"

Player::Player() {
    //default constructors
    name = "";
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}
 
Player::Player(string name_val) {
    //non-default constructors
    name = name_val;
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}
 
void Player::init_grid() {
    //going through each of the spots on the grid through an array
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            //each spot on the grid should be empty
            grid[i][j] = EMPTY_LETTER;
            //other players grid should be empty as well
            guess_grid[i][j] = EMPTY_LETTER;
        }
    }
    return;
}
 
string Player::get_name() {
    return name;
}
 
int Player::get_num_ships() {
    return num_ships;
}
 
int Player::get_remaining_ships() {
    return remaining_ships;
}
 
char Player::get_grid_at(int row, int col) {
    return grid[row][col];
}
 
char Player::get_guess_grid_at(int row, int col) {
    return guess_grid[row][col];
}
 
void Player::add_ship(Ship ship) {
    //the position of the ship needs to be valid
    //and not intersecting with another
    int startColumn = ship.get_start().get_col();
    int startRow = ship.get_start().get_row();
    int endColumn = ship.get_end().get_col();
    int endRow = ship.get_end().get_row();
    //no changes occur when the number of ships is the max number
    if(num_ships == MAX_NUM_SHIPS) {
        return;
    }
    else {
        for(int i = 0; i < MAX_NUM_SHIPS; i++) {
            //incrementing the number of ships
            if(ships[i].get_size() == 0) {
                ships[i] = ship;
                //addinging the ship to the next available index
                num_ships++;
                remaining_ships++;
                break;
        }
    }
        //when ship is horizontal
        if(ship.is_horizontal()) {
            if(startColumn < endColumn) {
                //going through the column
                for(int j = startColumn; j <= endColumn; j++) {
                    //incremented
                    Position pos(startRow, j);
                    if(ship.has_position(pos)) {
                        grid[startRow][j] = SHIP_LETTER;
                    }
                }
            }
            //still going through the column
            else if (startColumn > endColumn) {
                for(int j = startColumn; j >= endColumn; j--) {
                    //decremented
                    Position pos(startRow, j);
                    if (ship.has_position(pos)) {
                        grid[startRow][j] = SHIP_LETTER;
                    }
                }
            }
        }
        //when ship is vertical
        else {
            //going through the row
            if (startRow < endRow) {
                for (int i = startRow; i <= endRow; i++) {
                    //incremented
                    Position pos(i, startColumn);
                    if(ship.has_position(pos)) {
                        grid[i][startColumn] = SHIP_LETTER;
                    }
                }
            }
            //going through thr row
            else if(startRow > endRow) {
                for (int i = startRow; i >= endRow; i--) {
                    //it is decremented
                    Position pos(i, startColumn);
                    if(ship.has_position(pos)) {
                        grid[i][startColumn] = SHIP_LETTER;
                    }
                }
            }
        }
    }
}
 
 
void Player::attack(Player &opponent, Position pos) {
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            //setting the row and column for when they call it
            // int i is the row
            //int j is the column
            if ((pos.get_row() == i) && (pos.get_col() == j)) {
                //when it is a miss
                if(opponent.get_grid_at(i, j) == EMPTY_LETTER) {
                    guess_grid[i][j] = MISS_LETTER;
                    opponent.grid[i][j] = MISS_LETTER;
                    cout << name << " " << pos << " miss" << endl;
                }
                //when it is a hit
                else if(opponent.get_grid_at(i, j) == SHIP_LETTER) {
                    guess_grid[i][j] = HIT_LETTER;
                    opponent.grid[i][j] = HIT_LETTER;
                    cout << name << " " << pos << " hit" << endl;
                    //when the hit results in the ship sinking
                    for(int k = 0; k < MAX_NUM_SHIPS; k++) {
                        if(opponent.ships[k].has_position(pos)) {
                            opponent.ships[k].hit();
                            if(opponent.ships[k].has_sunk()) {
                                announce_ship_sunk(opponent.ships[k].get_size());
                                //need to decrement the number of ships remaining
                                opponent.remaining_ships--;
                            }
                        }
                    }
                }
                //when the hit is already one that has been marked
                else {
                    cout << name << " " << pos << " miss" << endl;
                }
            }
        }
    }
}
 
void Player::announce_ship_sunk(int size) {
    //ship named destroyer
    if (size == 2) {
        cout << "Congratulations " << name << "! You sunk a Destroyer"
        << endl;
    }
    //ship named submarine
    else if (size == 3) {
        cout << "Congratulations " << name << "! You sunk a Submarine"
        << endl;
    }
    //ship named battleship
    else if (size == 4) {
        cout << "Congratulations " << name << "! You sunk a Battleship"
        << endl;
    }
    else if (size == 5) {
    //ship named carrier
        cout << "Congratulations " << name << "! You sunk a Carrier"
        << endl;
    }
    return;
}
 
 
bool Player::load_grid_file(string filename) {
    Position read;
    Position end;
    ifstream positions;
    positions.open(filename);
    //successfully opening the file
    if(positions.is_open()) {
        positions >> read >> end;
        while(positions.good()) {
            //add_ship(Ship ship)
            Ship ship(read, end);
            add_ship(ship);
            positions >> read >> end;
        }
        return true;
    }
    else {
        return false;
    }
}
 
bool Player::destroyed() {
    //all ships have been sunk
    if (remaining_ships == 0) {
        return true;
    }
    else {
        return false;
    }
}

// Your code goes above this line.
// Don't change the implementations below!

void Player::print_grid() {
    ::print_grid(grid);
    
}

void Player::print_guess_grid() {
    ::print_grid(guess_grid);
    
}
