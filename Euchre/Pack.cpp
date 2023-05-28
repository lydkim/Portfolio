// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "Card.h"
#include <array>
#include <string>
#include <iostream>
#include <cassert>

using namespace std;

  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
  int p = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 6; ++j) {
      Card temp(RANK_NAMES_BY_WEIGHT[j + 7], SUIT_NAMES_BY_WEIGHT[i]);
      cards[p] = temp;
      p++;
    }
  }
  next = 0; 
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input){
  string junk;
  string rank;
  string suit;
  for (int p = 0; p < PACK_SIZE; ++p) {
    pack_input >> rank;
    pack_input >> junk;
    pack_input >> suit;
    Card temp(rank, suit);
    cards[p] = temp;
  }
  next = 0;
}

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    Card nextCard = cards[next];
    next++;
    return nextCard;
}

  // EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
  for (int s = 0; s < 7; ++s) {
    Card temp[24] = {};
    int counterForSpace = 1;
    for (int i = 0; i < 12; ++i) {
      temp[i + counterForSpace] = cards[i];
      counterForSpace++;
    }
    counterForSpace = 1;
    for (int j = cards.size() - 1; j >= 12; --j) {
      temp[j - counterForSpace] = cards[j];
      counterForSpace++;
    }
    //copying back over 
    for (int c = 0; c < cards.size(); ++c) {
      cards[c] = temp[c];
    }
  }
}
//moving to another cards position
//in the top half if it started at i goes to 2i


  // EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
  // if next > 23, that means weve dealt the whole pack 
  if (next > 23) {
    return true;
  }
  else {
    return false;
  }
}
