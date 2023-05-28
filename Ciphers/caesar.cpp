/*
 * caesar.cpp
 * Project UID e98fd45ccce9d7195e89e6171a5451f2
 *
 * Anna Torell, Lydia Kim
 * atorell, lydkim
 *
 * EECS 183: Project 3
 * Winter 2022
 *
 * Shifting letters on the ascii table, limited to only 25 spaces. Using these shifts to perform a caesar cipher where the letters are shifted according to a key. 
 */

#include "caesar.h"
#include <iostream>

// moving the spaces of letters based off of the ascii chart
char shiftAlphaCharacter(char c, int n) {
    //number of letters in the alphabet
    const int TOTAL_LETTERS = 26;
    const char LOWER_CASE_A = 'a';
    //97
    const char UPPER_CASE_A = 'A';
    //65
    char newC;
    // shifting the letters backwards
    // if it over the total letters in the alphabet, it goes back to the
    // beginning
    if (n < 0) {
        n = TOTAL_LETTERS + (n % TOTAL_LETTERS);
    }
    // for lower case letters
    if (islower(c)) {
        newC = (c + n - LOWER_CASE_A) % TOTAL_LETTERS + LOWER_CASE_A;
        return newC;
    }
    // for upper case letters
    else {
        newC = (c + n -  UPPER_CASE_A) % TOTAL_LETTERS +  UPPER_CASE_A;
        return newC;
    }
}
 
string caesarCipher(string original, int key, bool encrypt){
    string encrypted = "";
    char letter;
    //steps for excrypting a message
    if (encrypt) {
        //shifts the letter according to the user key to a scrambled message
        for (int i = 0; i < original.size(); i++) {
            if (isalpha(original.at(i))) {
                letter = shiftAlphaCharacter(original.at(i), key);
                encrypted = encrypted + shiftAlphaCharacter
                (original.at(i), key);
            }
            else {
                encrypted = encrypted + original.at(i);
            }
        }
        return encrypted;
    }
    //steps for decrypting a message
    else {
        //decrypting unscrambles the message based off of the user key
        for (int i = 0; i < original.size(); i++) {
            if (isalpha(original.at(i))) {
                letter = shiftAlphaCharacter(original.at(i), -key);
                encrypted = encrypted + shiftAlphaCharacter
                (original.at(i), -key);
            }
            else {
                encrypted = encrypted + original.at(i);
            }
        }
        return encrypted;
    }
    return encrypted;
}
