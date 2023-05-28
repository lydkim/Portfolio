/**
 * Copyright 2019 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Project 4: Battleship
 *
 * Contains functions for testing classes in the project. 
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "Position.h"
#include "Ship.h"
#include "Player.h"
#include "Game.h"
#include "utility.h"

using namespace std;


void test_position();
void test_ship();
void test_player();
void test_game();

void startTests() {
    test_position();
    test_ship();
    test_player();
    test_game();
    
    return;
}

void test_position() {
    // testing Position default constructor here
    Position start_pos;
    Position end_pos;
    cout << "Testing Position::Position() - default constructor\n";
    cout << "start_pos, expected output: (1,A) actual output: " << start_pos
    << endl;
    cout << "end_pos, expected output: (1,A) actual output: " << end_pos
    << endl;
    
    // testing Position setters here
    start_pos.set_row(4);
    start_pos.set_col(5);
    cout << "\nTesting Position::set_row() and Position::set_col()\n";
    cout << "start_pos, expected output: (5,F) actual output: " << start_pos
    << endl;
    
    // testing Position read
    ifstream input_file;
    input_file.open("grid1.txt");
    if (input_file.good()) {
        
        // can use the Position::read() function directly
        start_pos.read(input_file);
        
        // or use the extraction operator
        input_file >> end_pos;
        
        cout << "\nTesting Position::read()\n";
        cout << "start_pos, expected output: (1,A) actual output: " <<
        start_pos << endl;
        cout << "end_pos, expected output: (4,A) actual output: " << end_pos
        << endl;
    }
    else {
        cout << "\nError opening grid1.txt\n";
    }
    
    //position non default contructor tests
    Position start(4, 6);
    Position end(4, 0);
    Position big(980, 780);
    Position small(-908, -708);
    //with integer inputs
    cout << "Testing Position::Position(int row_in, int col_in) - " <<
    "non default constructor\n";
    cout << "start, expected output: (4,G) actual output: " << start << endl;
    cout << "end, expected output: (4,A) actual output: " << end << endl;
    cout << "big, expected output: (8,H) actual output: " << big << endl;
    cout << "small, expected output: (1,A) actual output: " << small << endl;
    //with character inputs
    cout << "Testing Position::Position(char row_in, char col_in) -" <<
    " non default constructor\n";
    Position charStart('0','A');
    cout << "s5, expected output: (0,A) actual output: " << charStart << endl;
    Position charEnd('4', 'd');
    cout << "s6, expected output: (4,D) actual output: " << charEnd << endl;
    Position charBig('8', 'H');
    cout << "s7, expected output: (8,H) actual output: " << charBig << endl;

    return;
}

void test_ship() {
    // Ship default constructor tests
    Ship startingShip;
    cout << "Testing Ship::Ship() - default constructor\n";
    cout << "startingShip, expected output: (1,A) (1,A) 0 actual output: "
    << startingShip.get_start() << " " << startingShip.get_end() << " " <<
    startingShip.get_size() << endl;
    
    //Ship non default constructor tests
    Position start(4, 6);
    Position end(4, 3);
    Position random(6, 2);
    Ship ship1(start, end);
    cout << "Testing Ship::Ship(Position start_in, Position end_in)";
    cout << "s2, expected output: (5,G) (5,A) 3, actual output: " <<
    ship1.get_start() << " " << ship1.get_end() << " " << ship1.get_size()
    << endl;

    // Ship has position tests
    cout << "Testing Ship::has_position(Position pos)";
    cout << "ship1, expected output: true, actual output: " <<
    ship1.has_position(start) << endl;
    cout << "ship1, expected output: true, actual output: " <<
    ship1.has_position(end) << endl;
    cout << "ship1, expected output: false, actual output: " <<
    ship1.has_position(random) << endl;
    
    //ship hit tests
    cout << "Testing Ship::hit()";
    // loop to make hit false and then become true
    for (int i = 0; i < (ship1.get_size() - 1); i++) {
        ship1.hit();
        cout << "ship1, expected output: false, actual output: " <<
        ship1.has_sunk() << endl;
        }
    ship1.hit();
    cout << "ship1, expected output: true, actual output: " <<
    ship1.has_sunk() << endl;
    ship1.hit();
    cout << "ship1, expected output: true, actual output: " <<
    ship1.has_sunk() << endl;
    return;
}

void test_player() {
    //Player default constructor tests
    Player player1;
    cout << "Testing Player::Player() - non default constructor\n";
    cout << "player1, expected output: , 0, 0, actual output: " <<
    player1.get_name() << " " << player1.get_num_ships() << " " <<
    player1.get_remaining_ships() << endl;
    
    //Player non default constructor tests
    Player Nick("Nick");
    cout << "Testing Player::Player(string name_val) - default constructor\n";
    cout << "Nick, expected output: Nick, 0, 0, actual output: " <<
    player1.get_name() << " " << player1.get_num_ships() << " " <<
    player1.get_remaining_ships() << endl;
    
    //Player load grid file tests
    cout << "Testing Player::load_grid_file(string filename)";
    //valid parameters
    cout << "player1, expected output: true, actual output: " <<
    player1.load_grid_file("grid1.txt")<< endl;
    cout << "player1, expected output: true, actual output: " <<
    player1.load_grid_file("grid2.txt")<< endl;
    //parameter doesn't exist
    cout << "player1, expected output: false, actual output: " <<
    player1.load_grid_file("doesntexist.txt")<< endl;
    
    //Player add ship tests
    cout << "Testing Player::add_ship()";
    Player bear;
    Player monkey;
    Player dolphin;
    //using load grid file
    bear.load_grid_file("grid1.txt");
    bear.print_grid();
    Position bearStart(0, 0);
    Position bearEnd(0, 3);
    Ship bearShip(bearStart, bearEnd);
    bear.add_ship(bearShip);
    bear.print_grid();
    //creating own locations
    monkey.add_ship(bearShip);
    Position monkeyStart1(0, 1);
    Position monkeyEnd1(0, 4);
    Position monkeyStart2(3, 4);
    Position monkeyEnd2(3, 1);
    Position monkeyStart3(8, 8);
    Position monkeyEnd3(5, 8);
    Position monkeyStart4(5, 3);
    Position monkeyEnd4(7, 3);
    Ship monkeyShip1(monkeyStart1, monkeyEnd1);
    Ship monkeyShip2(monkeyStart2, monkeyEnd2);
    Ship monkeyShip3(monkeyStart3, monkeyEnd3);
    Ship monkeyShip4(monkeyStart4, monkeyEnd4);
    monkey.add_ship(monkeyShip1);
    monkey.add_ship(monkeyShip2);
    monkey.add_ship(monkeyShip3);
    monkey.add_ship(monkeyShip4);
    monkey.print_grid();
    //addting just one ship
    dolphin.add_ship(bearShip);
    dolphin.print_grid();
    
    //Player attack tests
    cout << "Testing Player::attack(Player &opponent, Position pos)";
    //hit and sink vertical ship
    bear.attack(monkey, monkeyStart1);
    bear.print_guess_grid();
    Position middle1(0, 2);
    bear.attack(monkey, middle1);
    bear.print_guess_grid();
    Position middle2(0, 3);
    bear.attack(monkey, middle2);
    bear.print_guess_grid();
    bear.attack(monkey, monkeyEnd1);
    bear.print_guess_grid();
    //hit and sink horizontal
    bear.attack(monkey, monkeyStart3);
    bear.print_guess_grid();
    Position middle3(7, 8);
    bear.attack(monkey, middle3);
    bear.print_guess_grid();
    Position middle4(6, 8);
    bear.attack(monkey, middle4);
    bear.print_guess_grid();
    bear.attack(monkey, monkeyEnd3);
    bear.print_guess_grid();
    //hit and then miss
    Position random1(3, 1);
    monkey.attack(bear, random1);
    monkey.print_guess_grid();
    Position random2(4, 3);
    monkey.attack(bear, random2);
    monkey.print_guess_grid();
    return;
}

void test_game() {
    //game non default constructor tests
    cout << "Testing Game::Game(Player player1, string grid1, Player" <<
    " player2, string grid2)";
    Player bear("bear");
    Player monkey("monkey");
    Player robot("robot");
    Player dolphin("dolphin");
    //testing blank inputs
    Game animal(bear, "", monkey, "");
    animal.get_p1();
    bear.print_grid();
    animal.get_p2();
    monkey.print_grid();
    //with filenames
    Game animal2(robot, "grid1.txt", dolphin, "grid2.txt");
    animal2.get_p1();
    robot.print_grid();
    animal2.get_p2();
    dolphin.print_grid();
    
    //game getter tests
    cout << "Testing Game::get_p1(), Game::get_p2()" << endl;
    cout << "animal, expected output: bear, actual output: " <<
    animal.get_p1().get_name() << endl;
    cout << "animal, expected output: monkey, actual output: " <<
    animal.get_p2().get_name() << endl;
    
    //game check valid move tests
    cout << "Testing Game::check_valid_move()" << endl;
    //good moves
    string move1 = "1c";
    string move2 = "3b";
    string move3 = "8h";
    //bad moves
    string move4 = "0";
    string move5 = "9F";
    //return true
    cout << "move1, expected output: true, actual output: " <<
    animal.check_valid_move(move1) << endl;
    cout << "move2, expected output: true, actual output: " <<
    animal.check_valid_move(move2) << endl;
    cout << "move3, expected output: true, actual output: " <<
    animal.check_valid_move(move3) << endl;
    //return false 
    cout << "move4, expected output: false, actual output: " <<
    animal.check_valid_move(move4) << endl;
    cout << "move5, expected output: false, actual output: " <<
    animal.check_valid_move(move5) << endl;
    return;
}

