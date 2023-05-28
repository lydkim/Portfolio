/*
 * vigenere.cpp
 * Project UID e98fd45ccce9d7195e89e6171a5451f2
 *
 * Anna Torell, Lydia Kim
 * atorell, lydkim
 *
 * EECS 183: Project 3
 * Winter 2022
 *
 * Builds upon the caesar cipher by shifting letters via different keywords from the user input. 
 */

#include "utility.h"
#include "caesar.h"
#include "vigenere.h"
#include <iostream>

string vigenereCipher(string original, string keyword, bool encrypt) {
    // total amount of letters in the alphabet
    const int TOTAL_LETTERS = 26;
    // ascii value of uppercase Z
    const int ASCII_UPPER_Z = 90;
    // ascii value of uppercase A
    const int ASCII_UPPER_A = 65;
    // amount that the characters will be shifted
    int shift;
    // saves the original string to be able to change the original
    // to the right case
    string originalForCase = original;
    // to make keyword the same length as original
    int key = -1;
    keyword = removeNonAlphas(keyword);
    keyword = toUpperCase(keyword);
    original = toUpperCase(original);
    if (encrypt) {
        // each character in original is tested and if it is a letter in the
        // ascii table it uses the key, and adds to it if needed and then
        // shifts the character appropriately according to the key
        for (int i = 0; i < original.size(); i++) {
            if ((original.at(i) >= ASCII_UPPER_A) && (original.at(i)
                <= ASCII_UPPER_Z)) {
                key++;
                while (key >= keyword.size()) {
                    key = key - keyword.size();
                }
                shift = ((original.at(i) + (keyword.at(key) - ASCII_UPPER_A)));
                while (shift > ASCII_UPPER_Z) {
                    shift = shift - TOTAL_LETTERS;
                }
                original.at(i) = shift;
                if (original.at(i) > ASCII_UPPER_Z) {
                    original.at(i) = tolower(original.at(i));
                }
            }
        }
    }
    else {
        // each character in original is tested and if it is a letter in the
        // ascii table it uses the key, and adds to it if needed and then
        // shifts the character the opposite way according to the key to
        // decrypt the message
        for (int i = 0; i < original.size(); i++) {
            if ((original.at(i) >= ASCII_UPPER_A) && (original.at(i)
                <= ASCII_UPPER_Z)) {
                key++;
                while (key >= keyword.size()) {
                    key = key - keyword.size();
                }
                shift = ((original.at(i) - (keyword.at(key) - ASCII_UPPER_A)));
                while (shift < ASCII_UPPER_A) {
                    shift = shift + TOTAL_LETTERS;
                }
                original.at(i) = shift;
                if (original.at(i) > ASCII_UPPER_Z) {
                    original.at(i) = tolower(original.at(i));
                }
            }
        }
    }
    // to change the encrypted or decrypted message, this changes the
    // characters to their original case
    for (int i = 0; i < original.size(); i++) {
        if (islower(originalForCase.at(i)) && isalpha(original.at(i))) {
            original.at(i) = tolower(original.at(i));
        }
    }
    return original;
}
