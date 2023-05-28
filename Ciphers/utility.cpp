/*
 * utility.cpp
 * Project UID e98fd45ccce9d7195e89e6171a5451f2
 *
 * Anna Torell, Lydia Kim
 * atorell, lydkim
 *
 * EECS 183: Project 3
 * Winter 2022
 *
 * Includes helper functions that are used for the other functioms implemented in this project. 
 */

#include "utility.h"
#include <iostream>


string toUpperCase(string original) {
    // string to store the uppercase string
    string newString;
    // runs through all of the characters in original string 1 by 1, changing
    // alphabetical characters to uppercase
    for (int i = 0; i < original.size(); i++) {
        // assigns a variable to the character being tested
        char characterTest = original.at(i);
        if (isalpha(characterTest) && !isupper(characterTest)) {
            // assigns a variable to the new uppercase character
            char uppercase = toupper(characterTest);
            newString = newString + uppercase;
        }
        else {
            newString = newString + original.at(i);
        }
    }
    return newString;
}

string removeNonAlphas(string original) {
    // string to store the new string without the non alpha characters
    string newString;
    // tests each cahracter in original to see if it is alphabetical
    for (int i = 0; i < original.size(); i++) {
        // assigns a variable to the character being tested
        char characterTest = original.at(i);
        if (isalpha(characterTest)) {
            newString = newString + characterTest;
        }
    }
    return newString;
}

string removeDuplicate(string original) {
    // empty string to store the string without duplicates
    string newString = "";
    // boolean to measure if the strings are the same
    bool isSame = true;
    // tests each character in original and compares it with each
    // character in newString
    for (int i = 0; i < original.size(); i++) {
        for (int j = 0; j < newString.size(); j++) {
            // depending on if the characters or the same or not, set
            // isSame true or false
            if (original.at(i) == newString.at(j)) {
                isSame = false;
                break;
            }
            if (original.at(i) != newString.at(j)) {
                isSame = true;
            }
        }
        // if isSame is true, add the character to the new string
        if (isSame) {
            newString = newString + original.at(i);
        }
    }
    return newString;
}

int charToInt(char original) {
    //value of 0 on ascii table
    const int ASCII_VALUE_ZERO = 48;
    int num = original - ASCII_VALUE_ZERO;
    
    return num;
}

////////////////////////////////////////////////////////////////////////////////
// Do not touch code below. ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void printGrid(const char grid[SIZE][SIZE]) {
    for (int col = 0; col < SIZE; col++) {
        cout << " ---";
    }
    cout << endl;
    for (int row = 0; row < SIZE; row++) {
        cout << "| ";
        for (int col = 0; col < SIZE; col++) {
            cout << string(1, grid[row][col]) + " | ";
        }
        cout << endl;
        for (int col = 0; col < SIZE; col++) {
            cout << " ---";
        }
        cout << endl;
    }
}
