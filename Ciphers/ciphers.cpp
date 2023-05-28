/*
 * ciphers.cpp
 * Project UID e98fd45ccce9d7195e89e6171a5451f2
 *
 * Anna Torell, Lydia Kim
 * atorell, lydkim
 *
 * EECS 183: Project 3
 * Winter 2022
 *
 * Runs all 3 of the cipher types according to user input. 
 */

#include "utility.h"
#include "caesar.h"
#include "vigenere.h"
#include "polybius.h"
#include <iostream>
#include <string>
 
using namespace std;
 
string caesarCipher();
string vigenereCipher();
string polybiusSquare();
 
 
void ciphers() {
    string userCipher;
    string cipher;
    string userInput;
    bool input;
    string userMessage;
    string userKey;
    string secretMessage;
    char grid[SIZE][SIZE];
    
    //step one: choosing a cipher
    //asking the user for cipher option
    cout << "Choose a cipher (Caesar, Vigenere, or Polybius): ";
        cin >> userCipher;
        userCipher = toUpperCase(userCipher);
        if(userCipher == "CAESAR" || userCipher == "VIGENERE" || userCipher
           == "POLYBIUS" || userCipher == "C" || userCipher == "V" ||
           userCipher == "P") {
            cipher = userCipher;
        }
        else {
            //invalid if a different letter or number or character is put in
            cout << "Invalid cipher!" << endl;
            return;
        }
    
    //step two: asking the user for encrypt or decrypt
        cout << "Encrypt or decrypt: ";
        cin >> userInput;
        userInput = toUpperCase(userInput);
    // for encrypt
    if(userInput == "ENCRYPT" || userInput == "E") {
        input = true;
    }
    // for decrypt
    else if(userInput == "DECRYPT" || userInput == "D") {
        input = false;
    }
    //invalid if number or character or a different string
    else {
        cout << "Invalid mode!" << endl;
        return;
    }
 
    string line;
    getline(cin, line);
    //step three: getting the message of the user input
    cout << "Enter a message: ";
    getline(cin, userMessage);
    //only the polybius could cause an invalid message
    if(cipher == "POLYBIUS" || cipher == "P") {
        for(int i = 0; i < userMessage.size(); i++) {
            char messageLetter = userMessage.at(i);
            if(ispunct(messageLetter)) {
                //invalid if the characters are not alphabetic characters
                // or spaces
                cout << "Invalid message!" << endl;
                return;
            }
        }
    }
    
    //step four: getting the key
    cout << "What is your key: ";
    getline(cin, userKey);
    
    // the message for caesar cipher
    int newKey = 0;
    if (cipher == "CAESAR" || cipher == "C") {
        newKey = stoi(userKey);
        secretMessage = caesarCipher(userMessage, newKey, input);
    }
    // the message for vigenere cipher
    else if(cipher == "VIGENERE" || cipher == "V") {
        bool letter = false;
        for(int i = 0; i < userKey.size(); i++) {
            if(isalpha(userKey.at(i))) {
                letter = true;
            }
        }
        if(letter == false) {
            //invalid if it does not contain at least one alphabetical letter
            cout << "Invalid key!" << endl;
            return;
        }
        secretMessage = vigenereCipher(userMessage, userKey, input);
    }
    // the message for polybius square
    else if(cipher == "POLYBIUS" || cipher == "P") {
        userKey = toUpperCase(userKey);
        userKey = removeDuplicate(userKey);
        secretMessage = polybiusSquare(grid, userKey, userMessage, input);
    }
    
    //step five: printing message for all caesar, polybius, and vigenere
    if(input) {
        cout << "The encrypted message is: " << secretMessage << endl;
    }
    else {
        cout << "The decrypted message is: " << secretMessage << endl;
    }
}
