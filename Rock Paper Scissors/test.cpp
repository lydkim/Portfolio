/**
 * test.cpp
 * Project UID 24b93ce4a6274610f4c3f3e31fe17277t
 *
 * Lydia Kim
 * lydkim
 *
 * EECS 183: Project 2
 * Winter 2022
 *
 * Testing functions for your rps.cpp implementation.
 * Holds the definitions of required testing functions.
 * We have stubbed all required functions for you.
 */

#include <iostream>
#include <string>

using namespace std;


//************************************************************************
// You should have implemented the following functions in rps.cpp
//************************************************************************
string getName(int playerNumber);
int getMenuChoice();
bool isMoveGood(char move);
char getMove(string playerName);
bool isRoundWinner(char move, char opponentMove);
void announceRoundWinner(string winnerName);
int doRound(string p1Name, string p2Name);
void announceWinner(string winnerName);
string doGame(string p1Name, string p2Name, int gameType);

//************************************************************************
// The following functions were already implemented for you in rps.cpp
//************************************************************************
void printInitialHeader();
void printMenu();
void printErrorMessage(int errorNumber);
void printCloser();

//************************************************************************
// Testing function declarations. Function definition is below main.
//************************************************************************
void test_isMoveGood();
void test_isRoundWinner();
void test_announceRoundWinner();
void test_announceWinner();


void startTests() {
    cout << "\nExecuting your test cases\n";

    test_isMoveGood();
    test_isRoundWinner();
    test_announceRoundWinner();
    test_announceWinner();

    return;
}

//************************************************************************
// Put all your test function implementations below here.
// We have stubbed all required functions for you
// to recieve full points when submitting test.cpp
// NOTE: We will only grade your tests for the following functions
//       * isMoveGood
//       * isRoundWinner
//       * announceRoundWinner()
//       * announceWinner()
//************************************************************************

void test_isMoveGood() {
    cout << "Now testing function isMoveGood()\n";
    //outcome is 1
    cout << "'r': Expected: 1, Actual: " << isMoveGood('r') << endl;
    cout << "'R': Expected: 1, Actual: " << isMoveGood('R') << endl;
    cout << "'p': Expected: 1, Actual: " << isMoveGood('p') << endl;
    cout << "'P': Expected: 1, Actual: " << isMoveGood('P') << endl;
    cout << "'s': Expected: 1, Actual: " << isMoveGood('s') << endl;
    cout << "'S': Expected: 1, Actual: " << isMoveGood('S') << endl;
    //outcome is 0
    cout << "'q': Expected: 0, Actual: " << isMoveGood('q') << endl;
    cout << "' ': Expected: 0, Actual: " << isMoveGood(' ') << endl;
    cout << "'+': Expected: 0, Actual: " << isMoveGood('+') << endl;
    
    return;
}

void test_isRoundWinner() {
    //outcomes that are true
    cout << "'R', 'S': Expected: true, Actual: " << isRoundWinner('R', 'S') << endl;
    cout << "'r', 's': Expected: true, Actual: " << isRoundWinner('r', 's') << endl;
    cout << "'R', 's': Expected: true, Actual: " << isRoundWinner('R', 's') << endl;
    cout << "'r', 'S': Expected: true, Actual: " << isRoundWinner('r', 'S') << endl;
    cout << "'P', 'R': Expected: true, Actual: " << isRoundWinner('P', 'R') << endl;
    cout << "'p', 'r': Expected: true, Actual: " << isRoundWinner('p', 'r') << endl;
    cout << "'P', 'r': Expected: true, Actual: " << isRoundWinner('P', 'r') << endl;
    cout << "'p', 'R': Expected: true, Actual: " << isRoundWinner('p', 'R') << endl;
    cout << "'S', 'P': Expected: true, Actual: " << isRoundWinner('S', 'P') << endl;
    cout << "'s', 'p': Expected: true, Actual: " << isRoundWinner('s', 'p') << endl;
    cout << "'S', 'p': Expected: true, Actual: " << isRoundWinner('S', 'p') << endl;
    cout << "'s', 'P': Expected: true, Actual: " << isRoundWinner('s', 'P') << endl;
    //outcomes that are false
    cout << "'S', 'R': Expected: false, Actual: " << isRoundWinner('S', 'R') << endl;
    cout << "'s', 'r': Expected: false, Actual: " << isRoundWinner('s', 'r') << endl;
    cout << "'R', 'P': Expected: false, Actual: " << isRoundWinner('R', 'P') << endl;
    cout << "'r', 'p': Expected: false, Actual: " << isRoundWinner('r', 'p') << endl;
    cout << "'P', 'S': Expected: false, Actual: " << isRoundWinner('P', 'S') << endl;
    cout << "'p', 's': Expected: false, Actual: " << isRoundWinner('p', 's') << endl;
  
    return;
}

void test_announceRoundWinner() {
    cout << "Now testing function announceRoundWinner()\n";
    cout <<"Expected: draw, Actual: ";
    announceRoundWinner("");
    cout << endl;
    cout << "Expected: winnerName, Actual: ";
    announceRoundWinner("winnerName");
    cout << endl;
    return;
}

void test_announceWinner() {
    cout << "Now testing function announceWinner()\n";
    cout << "'': Expected: No Winner!, Actual: ";
    announceWinner("");
    cout << endl;
    
    cout << "Lydia Kim: Expected: Congratulations Lydia Kim!" << endl;
    cout << "You won EECS 183 Rock-Paper-Scissors!, Actual:";
    announceWinner("Lydia Kim");
    cout << endl;
    
    cout << "mother: Expected: Congratulations mother!" << endl;
    cout << "You won EECS 183 Rock-Paper-Scissors!, Actual:";
    announceWinner("mother");
    cout << endl;

    return;
}
