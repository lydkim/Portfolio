/**
 * focaccia.cpp
 *
 * Lydia Kim
 * lydkim
 *
 * EECS 183: Project 1
 * Winter 2022
 * 
 * Project UID: fde244392017fe65ebcc34f01c226b11f113bb3dc6dae8af4cb6ea11bf76f7c8
 */

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

/**
 * Returns the singular or plural form of a word, based on number
 *
 * Requires: singular is the singular form of the word.
 *           plural is the plural form of the word.
 *           number determines how many things there are; must be >= 0.
 * Modifies: Nothing.
 * Effects:  Returns return the singular form of the word if number == 1.
 *           Otherwise, returns the plural form.
 * Examples:
 *           // prints "bag"
 *           cout << pluralize("bag", "bags", 1);
 *
 *           // prints "pounds"
 *           string temp = pluralize("pound", "pounds", 3);
 *           cout << temp;
 */
string pluralize(string singular, string plural, int number);



int main() {
    int people;
    cout << "How many people do you need to serve? ";
    cin >> people;
    cout << endl << endl << endl;

    // this is a double to force double division
    const double peoplePerLoaf = 4.0;
    // calculating the number of loaves needed based on number of people
    int loaves = ceil(people / peoplePerLoaf);
    cout << "You need to make: " << loaves << pluralize("loaf", "loaves", loaves) << " of focaccia" << endl << endl;
    
    // INDLUE THE PHRASE THE INGREDIENTS TO BUY TITLE
    cout << "Shopping List for Focaccia Bread" << endl;
    cout << "--------------------------------" << endl;
    
    // information for flour
    const double flourCupsPerLoaf = 5.0;
    const double flourCupsPerBag = 20;
    // number of flour bags in relation to number of loaves
    int flourBags = ceil(loaves * flourCupsPerLoaf / flourCupsPerBag);
    cout << flourBags << pluralize("bag", "bags", flourBags) << "of flour" << endl;
    
    // information for yeast
    const double yeastTspsPerLoaf = 1.75;
    const double yeastTspsPerPackage = 2.25;
    // number of yeast packages in relation to number of loaves
    int yeastPackages = ceil(loaves * yeastTspsPerLoaf / yeastTspsPerPackage);
    cout << yeastPackages << pluralize("package", "packages", yeastPackages) << " of yeast" << endl;
    
    // information for salt
    const double saltTspsPerLoaf = 1.875;
    const double saltGramsPerTsps = 5;
    const double saltGramsPerCanister = 30;
    // number of salt canisters in relation to number of loaves
    int saltCanisters = ceil(loaves * saltTspsPerLoaf * saltGramsPerTsps / saltGramsPerCanister);
    cout << saltCanisters << pluralize("canister", "canisters", saltCanisters) << " of salt" << endl;
    
    //information for olive oil
    const double oilTbspsPerLoaf = 2;
    const double oilMlPerTbsps = 14.8;
    const double oilMlPerBottle = 500;
    // number of olive oil bottles in relation to number of loaves
    int oliveOilBottles = ceil(loaves * oilTbspsPerLoaf * oilMlPerTbsps / oilMlPerBottle);
    cout << oliveOilBottles << pluralize("bottle", "bottles", oliveOilBottles) << " of olive oil" << endl << endl;

    //information for total cost
    const double flourBagCost = 2.69;
    const double yeastPackageCost = 0.40;
    const double saltCanisterCost = 0.49;
    const double oliveOilBottleCost = 6.39;
    // total cost of all the ingredients to make the focaccia bread
    double totalCost = (flourBags * flourBagCost) + (yeastPackages * yeastPackageCost) + (saltCanisters * saltCanisterCost) + (oliveOilBottles * oliveOilBottleCost);
    cout << "Total expected cost of ingredients: $" << totalCost << endl << endl;
    
    cout << "Have a great party!" << endl;
    return 0;
}

// ----------------------------------------------
// *** DO NOT CHANGE ANYTHING BELOW THIS LINE ***

string pluralize(string singular, string plural, int number) {
    if (number == 1) {
        return singular;
    }
    return plural;
}
