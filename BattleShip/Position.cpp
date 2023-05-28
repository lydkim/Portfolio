/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Position.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Anna Torell, Lydia Kim
 * atorell, lydkim
 *
 * Project 4: Battleship
 *
 * Position represents a single set of coordinates on the grid.
 * It can be used to represent ships and moves.
 * Each position has an underlying integer value.
 */

#include "Position.h"
#include "utility.h"

const char ASCII_UPPER = 'A';
const char ASCII_LOWER = 'a';
const char ASCII_1 = '1';

Position::Position() {
    //default constructor
    row = 0;
    col = 0;
}
 
Position::Position(int row_in, int col_in) {
    //constructing a position
    //row and col need to be valid inputs
    row_in = check_range(row_in);
    col_in = check_range(col_in);
    //setting row and col position
    row = row_in;
    col = col_in;
}
 
Position::Position(char row_in, char col_in) {
    //converting the character position into the integer it represents
    row = row_in - ASCII_1;
    //col does not need to be converted
    if (isupper(col_in)) {
        col = col_in - ASCII_UPPER;
    }
    else {
        col = col_in - ASCII_LOWER;
    }
    //checking that these are valid inputs
    row = check_range(row);
    col = check_range(col);
}
 
int Position::get_row() {
    return row;
}
 
void Position::set_row(int row_in) {
    //making sure that the value is valid
    row_in = check_range(row_in);
    row = row_in;
    return;
}
 
int Position::get_col() {
    return col;
}
 
void Position::set_col(int col_in) {
    //making sure that the value is valid
    col_in = check_range(col_in);
    col = col_in;
    return;
}
 
void Position::read(istream &is) {
    char column;
    //reads in the row and column
    is >> row >> column;
    //if the istream goes into a fail state, clear the fail state and read
    //in with junk variables to account for (,)
    if (is.fail()) {
        is.clear();
        char junk;
        is >> junk >> row >> junk >> column >> junk;
    }
    //make the column an uppercase letter and convert to correct range
    column = toupper(column);
    col = check_range(column - ASCII_UPPER);
    row = check_range(row - 1);
    return;
}
 
void Position::write(ostream &os) {
    //change the range of column and row
    char column;
    column = col + ASCII_UPPER;
    int newRow;
    newRow = row + 1;
    //output the row and column in the form (row,col)
    os << "(" << newRow << "," << column << ")";
    return;
}
 
int Position::check_range(int val) {
    //if the value is between 0 and max grid, return the value
    if (val >= 0 && val < MAX_GRID_SIZE) {
        return val;
    }
    //if the value is negative, make it 0
    else if (val < 0) {
        return 0;
    }
    //if the value is positive, make it the index of max grid
    else {
        return (MAX_GRID_SIZE - 1);
    }
}
 
 
// Your code goes above this line.
// Don't change the implementations below!
 
istream &operator>>(istream &is,  Position &pos) {
    pos.read(is);
    return is;
}
 
ostream &operator<<(ostream &os, Position pos) {
    pos.write(os);
    return os;
}
 
