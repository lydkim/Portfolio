/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Ship.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Anna Torell, Lydia Kim
 * atorell, lydkim
 *
 * Project 4: Battleship
 *
 * Functions are written to represent a certain a battle ship in the game.
 * The length and size of the ship is based off of the start and end coordinated of it.
 */

#include <cmath>

#include "Ship.h"


Ship::Ship() {
   //default constructors
   //setting the start to origin
   start.set_row(0);
   start.set_col(0);
   //setting the end to origin
   end.set_row(0);
   end.set_col(0);
   num_hits = 0;
   size = 0;
}

Ship::Ship(Position start_in, Position end_in) {
   //diagonal is not allowed
   //non default constructor
   start.set_row(start_in.get_row());
   start.set_col(start_in.get_col());
   end.set_row(end_in.get_row());
   end.set_col(end_in.get_col());
   num_hits = 0;
   //for when the ship is horizontal
   if(is_horizontal() == true) {
       size = end.get_col() - start.get_col();
       //it is still valid if the end coordinate is
       //put in before the start
       size = abs(size);
       //the size is determined by the start and end position
       size += 1;
   }
   //for when the ship is vertical
   else {
       size = end.get_row() - start.get_row();
       size = abs(size);
       size += 1;
   }
}

Position Ship::get_start() {
   return start;
}

Position Ship::get_end() {
   return end;
}

int Ship::get_size() {
   return size;
}

bool Ship::is_horizontal() {
   //the row coordinates should be the same when the ship is horizontal
   if(start.get_row() == end.get_row()) {
       return true;
   }
   else {
       return false;
   }
}


bool Ship::has_position(Position pos) {
   //making sure that the position is in range
   int coordRow = pos.get_row();
   int coordCol = pos.get_col();
   int startCoord;
   int endCoord;
   Ship Queen(start, end);
   //passing the example ship for when horizontal is true
   if(Queen.is_horizontal()) {
       if(start.get_col() > end.get_col()) {
           //switching the start and end for the column value
           startCoord = end.get_col();
           endCoord = start.get_col();
       }
       else {
           //when the start col is less than the end col
           startCoord = start.get_col();
           endCoord = end.get_col();
       }
       if (((coordCol <= endCoord) && (coordCol >= startCoord))
           && (coordRow == start.get_row())) {
           return true;
       }
       else {
           return false;
       }
   }
   //passing the example ship for when horizontal is false
   else {
       if (start.get_row() > end.get_row()) {
           //switching the start and end row value
           startCoord = end.get_row();
           endCoord = start.get_row();
       }
       else {
           //when the start is less than the end value for row
           startCoord = start.get_row();
           endCoord = end.get_row();
       }
       if(((coordRow <= endCoord) && (coordRow >= startCoord))
          && (coordCol == start.get_col())) {
           return true;
       }
       else {
           return false;
       }
   }
}

void Ship::hit() {
   if(num_hits < size) {
       num_hits++;
   }
}

bool Ship::has_sunk() {
   //all of the ships have been sunk
   if(num_hits == size) {
       return true;
   }
   else {
       return false;
   }
}
