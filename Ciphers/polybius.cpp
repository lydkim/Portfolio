/*
 * polybius.cpp
 * Project UID e98fd45ccce9d7195e89e6171a5451f2
 *
 * Anna Torell, Lydia Kim
 * atorell, lydkim
 *
 * EECS 183: Project 3
 * Winter 2022
 *
 * Creates a string with a key and then the rest of the alphabet, puts this key into a grid, and finds values inside of the grid, all in separate functions. The polybiusSquare function utlizes the other functions to perform the polybiusSquare cipher according to the key and the original message. 
 */


#include "polybius.h"
#include <string>
using namespace std;

string mixKey(string key) {
    // empty string for the mixed key
    string keyALNUM = "";
    // empty string for the back of the string,
    // the leftover alphanumeric characters
    string back = "";
    // boolean if a character is in ALNUM
    bool isInside;
    // tests characters in ALNUM and in key to see if they are equal
    for (int i = 0; i < ALNUM.size(); i++) {
        isInside = false;
        for (int j = 0; j < key.size(); j++) {
            if (key.at(j) == ALNUM.at(i)) {
                isInside = true;
            }
        }
        // if they are not equal, the character is added to the sequence
        if (isInside == false) {
            back = back + ALNUM.at(i);
        }
        
    }
    // adds the key to the rest of the alphanumeric sequence
    keyALNUM = key + back;
    return keyALNUM;
}

void fillGrid(char grid[SIZE][SIZE], string content) {
    // keeps track of the content of the grid
    int i = 0;
    // goes through each spot in the grid, row by column and adds
    // content to eaach spot
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            grid[row][col] = content[i];
            i = i + 1;
        }
    }
}

string findInGrid(char c, char grid[SIZE][SIZE]) {
    // empty string for the coordinates in char
    string coordinates = "";
    // string to change the int row into a string
    string cRow;
    // string to change the int column into a string
    string cCol;
    // goes through each row and column in grid and changes it to a string
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col <= SIZE; col++) {
            if (grid[row][col] == c) {
                cRow = to_string(row);
                cCol = to_string(col);
                coordinates = cRow + cCol;
            }
        }
    }
    return coordinates;
}

string polybiusSquare(char grid[SIZE][SIZE], string key, string original, bool encrypt) {
    // establishes the key and the rest of the grid
    string keyALNUM = mixKey(key);
    fillGrid(grid, keyALNUM);
    if (encrypt) {
        // string for encrypted string
        string encrypted;
        // for each character in original, if it is a space, the space is
        // kept and if it has a character, it is found in the grid and the
        // coordinates are added to the encryption
        for (int i = 0; i < original.size(); i++) {
            if (original.at(i) == ' ') {
                encrypted = encrypted + " ";
            }
            else {
                string coordinates = findInGrid(original.at(i), grid);
                encrypted = encrypted + coordinates;
            }
        }
        return encrypted;
    }
    else {
        // string for decrypted string
        string decrypted;
        // collects 2 coordinates from the original string
        string gather;
        // the length or coordinates to find in grid is 2
        const int COORDINATE = 2;
        // loops through each character in origial, and if it is a space, it
        // is kept, if not, 2 coordinates are gathered
        for (int i = 0; i < original.size(); i++) {
            if (original.at(i) == ' ') {
                decrypted = decrypted + " ";
            }
            else {
                gather = gather + original.at(i);
            }
            // when there are 2 coordinates, they are converted into
            // integers and added to the decrypt string, gather is then set
            // to nothing
            if (gather.size() == COORDINATE) {
                int row = charToInt(gather.at(0));
                int col = charToInt(gather.at(1));
                decrypted = decrypted + grid[row][col];
                gather = "";
            }
            
        }
        return decrypted;
    }
}

