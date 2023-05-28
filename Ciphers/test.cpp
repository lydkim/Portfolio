//
//  test.cpp
//  Project 3
//
//  Anna Torell, Lydia Kim
//  atorell, lydkim

#include "utility.h"
#include "caesar.h"
#include "vigenere.h"
#include "polybius.h"
#include <iostream>
#include <string>
 
using namespace std;
 
void testShiftAlphaCharacter();
void testToUpperCase();
void testRemoveNonAlphas();
void testRemoveDuplicate();
void testCharToInt();
void testCaesarCipher();
void testVigenereCipher();
void testFillGrid();
void testMixKey();
void testFindInGrid();
void testPolybiusSquare();
 
 
void startTests() {
    testShiftAlphaCharacter();
    testToUpperCase();
    testRemoveNonAlphas();
    testRemoveDuplicate();
    testCharToInt();
    testCaesarCipher();
    testVigenereCipher();
    testFillGrid();
    testMixKey();
    testFindInGrid();
    testPolybiusSquare();
    return;
}
 
void testShiftAlphaCharacter() {
    cout << "Now testing function ShiftAlphaCharacter()" << endl;
    cout << "Expected: 'a', Actual: '" << shiftAlphaCharacter('a', 0)
    << "'" << endl;
    cout << "Expected: 'b', Actual: '" << shiftAlphaCharacter('a', 1)
    << "'" << endl;
    cout << "Expected: 'd', Actual: '" << shiftAlphaCharacter('f', -2)
    << "'" << endl;
    cout << "Expected: 'C', Actual: '" << shiftAlphaCharacter('X', 5)
    << "'" << endl;
    cout << "Expected: 'V', Actual: '" << shiftAlphaCharacter('X', 50)
    << "'" << endl;
    return;
}
 
void testToUpperCase() {
    cout << "Now testing function ToUpperCase()" << endl;
    cout << "Expected: DIAG @ 11 P.M., Actual: " <<
    toUpperCase("Diag @ 11 p.m.") << endl;
    cout << "Expected: EECS, Actual: " << toUpperCase("eEcs") << endl;
    cout << "Expected: CHICKEN, Actual: " << toUpperCase("chicken") << endl;
    cout << "Expected: CHICKEN NUGGETS!, Actual: " <<
    toUpperCase("cHIckEN NUGGETS!") << endl;
    cout << "Expected: 1234ABC, Actual: " << toUpperCase("1234abc") << endl;
    cout << "Expected: !!!, Actual: " << toUpperCase("!!!") << endl;
    return;
}
 
void testRemoveNonAlphas() {
    cout << "Now testing function RemoveNonAlphas()" << endl;
    cout << "Expected: Diagpm, Actual: " << removeNonAlphas("Diag @ 11 p.m.")
    << endl;
    cout << "Expected: monkey, Actual: " << removeNonAlphas("monkey1") <<
    endl;
    cout << "Expected: chicken, Actual: " << removeNonAlphas("chicken") <<
    endl;
    cout << "Expected: , Actual: " << removeNonAlphas("12345") << endl;
    cout << "Expected: , Actual: " << removeNonAlphas("!!!") << endl;
    return;
}
 
void testRemoveDuplicate() {
    cout << "Now testing function RemoveDuplicate()" << endl;
    cout << "Expected: HELOWRD, Actual: " << removeDuplicate("HELLOWORLD")
    << endl;
    cout << "Expected: E, Actual: " << removeDuplicate("EEEEEE") << endl;
    cout << "Expected: LOSE, Actual: " << removeDuplicate("LLOOSSEE") << endl;
    cout << "Expected: 123, Actual: " << removeDuplicate("112233") << endl;
    return;
}
 
void testCharToInt() {
    cout << "Now testing function CharToInt()" << endl;
    cout << "Expected: 1, Actual: " << charToInt('1') << endl;
    cout << "Expected: 2, Actual: " << charToInt('2') << endl;
    cout << "Expected: 0, Actual: " << charToInt('0') << endl;
    return;
}
 
void testCaesarCipher() {
    cout << "Now testing function CaesarCipher()" << endl;
    cout << "Expected: Cuuj cu qj jxu Tyqw qj 11 f.c., Actual: " <<
    caesarCipher("Meet me at the Diag at 11 p.m.", 42, true) << endl;
    cout << "Expected: Meet me at the Diag at 11 p.m., Actual: " <<
    caesarCipher("Cuuj cu qj jxu Tyqw qj 11 f.c.", 42, false) << endl;
    cout << "Expected: b , Actual: " << caesarCipher("a", 1, true) << endl;
    cout << "Expected: bcd, Actual: " << caesarCipher("abc", 1, true) <<
    endl;
    cout << "Expected: abc, Actual: " << caesarCipher("bcd", 1, false) <<
    endl;
    cout << "Expected: a, Actual: " << caesarCipher("a", 0, true) << endl;
    cout << "Expected: a, Actual: " << caesarCipher("a", 0, false) << endl;
    cout << "Expected: C, Actual: " << caesarCipher("M", 42, true) << endl;
    return;
}
 
void testVigenereCipher() {
    cout << "Now testing function VigenereCipher()" << endl;
    cout << "Expected: Euyb dv ee lxy Lzrk ll 11 f.g., Actual: " <<
    vigenereCipher("Meet me at the Diag at 11 p.m.", "Squirrel!", true) << endl;
    cout << "Expected: Meet me at the Diag at 11 p.m., Actual: " <<
    vigenereCipher("Euyb dv ee lxy Lzrk ll 11 f.g.", "Squirrel!", false) << endl;
    cout << "Expected: abuaeql, Actual: " << vigenereCipher("chicken",
    "yum", true) << endl;
    cout << "Expected: chicken, Actual: " << vigenereCipher("abuaeql",
    "yum", false) << endl;
    cout << "Expected: abuaeql, Actual: " << vigenereCipher("chicken",
    "yum!!", true) << endl;
    cout << "Expected: chicken, Actual: " << vigenereCipher("abuaeql",
    "yum!!", false) << endl;
    return;
}
 
void testFillGrid() {
    cout << "Now testing function FillGrid()" << endl;
    char grid [SIZE][SIZE];
    fillGrid(grid, ALNUM);
    printGrid(grid);
 
    string RANDOM = "QWERTYUIOPASDFGHJKLZXCVBNM1234567890";
    fillGrid(grid,RANDOM);
    printGrid(grid);
    return;
 
}
 
void testMixKey() {
    cout << "Now testing function MixKey()" << endl;
    cout << "Expected: POLYBIUSACDEFGHJKMNQRTVWXZ0123456789, Actual: " <<
    mixKey("POLYBIUS") << endl;
    cout << "Expected: YUMABCDEFGHIJKLNOPQRSTVWXZ0123456789, Actual: " <<
    mixKey("YUM") << endl;
    cout << "Expected: 123ABCDEFGHIJKLMNOPQRSTUVWXYZ0456789 , Actual: " <<
    mixKey("123") << endl;
 
    
    return;
}
 
void testFindInGrid() {
    cout << "Now testing function FindInGrid()" << endl;
    char grid[SIZE][SIZE];
    fillGrid(grid, ALNUM);
    cout << "Expected: 00, Actual: " << findInGrid('A', grid) << endl;
    cout << "Expected: 01, Actual: " << findInGrid('B', grid) << endl;
    cout << "Expected: 33, Actual: " << findInGrid('O', grid) << endl;
    cout << "Expected: 66, Actual: " << findInGrid('9', grid) << endl;
    cout << "Expected:  36, Actual: " << findInGrid('R', grid) << endl;
    return;
}
 
void testPolybiusSquare() {
    cout << "Now testing function PolybiusSquare()" << endl;
    char grid[SIZE][SIZE];
    cout << "Expected: 11110533 000102 1533 341411 04113334, Actual: " <<
    polybiusSquare(grid, "183", "EECS 183 IS THE BEST", true) << endl;
    cout << "Expected: EECS 183 IS THE BEST, Actual: " <<
    polybiusSquare(grid, "183", "11110533 000102 1533 341411 04113334", false)
    << endl;
    cout << "Expected: 05141505211123, Actual: " <<
    polybiusSquare(grid, "YUM", "CHICKEN", true) << endl;
    cout << "Expected: CHICKEN, Actual: " <<
    polybiusSquare(grid, "YUM", "05141505211123", false) << endl;
    return;
}


