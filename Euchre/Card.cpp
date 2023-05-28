// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"

using namespace std;
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

//EFFECTS Initializes Card to the Two of Spades
Card::Card()
    : rank(RANK_TWO), suit(SUIT_SPADES) {}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string &rank_in, const std::string &suit_in) 
 : rank(rank_in), suit(suit_in) {}

//EFFECTS Returns the rank
std::string Card::get_rank() const {
    return rank;
}

//EFFECTS Returns the suit. Does not consider trump.
std::string Card::get_suit() const {
    return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const {
    //when this is the left bower
    if (rank == RANK_JACK && suit == Suit_next(trump)) {
        return trump;
    }
    return suit;
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face_or_ace() const {
    if (rank == RANK_JACK || rank == RANK_QUEEN || rank == RANK_KING 
    || rank == RANK_ACE) {
        return true;
    }
    else {
        return false;
    }
}

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const {
    if (rank == RANK_JACK && suit == trump) {
        return true;
    }
    else {
        return false;
    }
}

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const {
    if (rank == RANK_JACK && suit == Suit_next(trump)) {
        return true;
    } 
    else {
        return false;
    }
}

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const {
    if (suit == trump || is_left_bower(trump)) {
        return true;
    } 
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
    string left_suit = lhs.get_suit();
    string right_suit = rhs.get_suit();
    string left_rank = lhs.get_rank();
    string right_rank = rhs.get_rank();
    int lhs_suit_index;
    int rhs_suit_index;
    int lhs_rank_index;
    int rhs_rank_index;
    for (int i = 0; i < NUM_SUITS; ++i) {
        if (left_suit == SUIT_NAMES_BY_WEIGHT[i]) {
            lhs_suit_index = i;
        }
        if (right_suit == SUIT_NAMES_BY_WEIGHT[i]) {
            rhs_suit_index = i;
        }
    }
    for (int j = 0; j < NUM_RANKS; ++j) {
        if (left_rank == RANK_NAMES_BY_WEIGHT[j]) {
            lhs_rank_index = j;
        }
        if(right_rank == RANK_NAMES_BY_WEIGHT[j]) {
            rhs_rank_index = j;
        }
    }
    if (lhs_rank_index < rhs_rank_index) {
        return true;
    }
    else if (lhs_rank_index > rhs_rank_index) {
        return false;
    }
    else if(lhs_rank_index == rhs_rank_index) {
        //then compare the suits
        if (lhs_suit_index < rhs_suit_index) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs){
    return (lhs < rhs || lhs == rhs);
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
    return !(lhs <= rhs);
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs){
    return !(lhs < rhs);
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs){
    return (lhs.get_rank() == rhs.get_rank()) 
    && (lhs.get_suit() == rhs.get_suit());
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs){
    return !(lhs == rhs);
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit){
    if (suit == "Clubs") {
        return "Spades";
    }
    else if(suit == "Spades") {
        return "Clubs";
    }
    else if(suit == "Diamonds") {
        return "Hearts";
    }
    else {
        return "Diamonds";
    }
    //club and spade
    //diamond and heart
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

bool compare (const Card &a, const Card &b, const std::string &trump) {
    if (operator<(a, b)) {
        return true;
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump) {
    if ((a.is_left_bower(trump) && b.get_suit() != trump) || 
    (a.is_right_bower(trump))) {
        return false;
    }
    else if ((b.is_right_bower(trump)) || (b.get_suit() 
    != trump && a.is_left_bower(trump))) {
        return true;
    }
    else if ((a.get_suit() != trump || a.get_suit() 
    == trump) && b.is_left_bower(trump)) {
        return true;
    }
    else if (b.get_suit() == trump && a.is_left_bower(trump)) {
        return false;
    }
    else if (a.is_left_bower(trump) && !b.is_right_bower(trump)) {
        return false;
    }
    else if (operator==(a, b)) {
        return false;
    }
        else if ((a.get_suit() == trump && b.get_suit() == trump) || 
        (a.get_suit() != trump && b.get_suit() != trump)) {
            if(compare(a, b, trump) == true) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (a.get_suit() == trump && b.get_suit() != trump) {
            return false;
        }
        else if (a.get_suit() != trump && b.get_suit() == trump) {
            return true;
        }
        else {
            return false;
        }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {
    //use the operator functions to do what you want 
    if (operator==(a, b)) {
        return false;
    }
    else if ((a.get_suit() == trump) || (b.get_suit() == trump)) {
        if (Card_less(a, b, trump) == true) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (led_card.get_suit() == a.get_suit() && led_card.get_suit() 
    == b.get_suit()) {
        if (operator<(a, b)) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (led_card.get_suit() == a.get_suit() 
    && (led_card.get_suit() != b.get_suit() && b.get_suit() != trump)) {
        return false;
    }
    else if ((led_card.get_suit() != a.get_suit() 
    && a.get_suit() != trump) && led_card.get_suit() == b.get_suit()) {
        return true;
    }
    else {
        return false;
    }
}