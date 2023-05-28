// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include "Player.h"
#include "Card.h"
#include <vector>
#include <algorithm>

using namespace std;

class Simple : public Player {
  public:
  //default constructor
  Simple (){};

  //ctor with input of name 
  Simple (const std::string &name_in):name(name_in){};

  //EFFECTS returns player's name
  const std::string & get_name() const override { return name; };

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c) override { 
    if (hand.size() < MAX_HAND_SIZE) {
      hand.push_back(c); 
    }
  };

  int countNextSuit(const Card &upcard) const {
    std::string currSuit = upcard.get_suit();
    int count = 0;
    for (int i = 0; i < MAX_HAND_SIZE; ++i) {
      if ((hand[i].get_suit() == Suit_next(currSuit) 
      || hand[i].is_left_bower(Suit_next(currSuit))) && hand[i].is_face_or_ace()) {
        count++;
      }
    }
    return count;
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override {
    std::string currSuit = upcard.get_suit();
    int count = 0;
    if (round == 1) {
      for (int i = 0; i < MAX_HAND_SIZE; ++i) {
        if ((hand[i].get_suit() == currSuit || hand[i].is_left_bower(currSuit)) 
        && hand[i].is_face_or_ace()) {
          count++;
        }
      }
      if (count >= 2) {
        order_up_suit = currSuit;
        return true;
      }
      else {
        return false;
      }
    }
    else {
      if (is_dealer) {
        order_up_suit = Suit_next(currSuit);
        return true;
      }
      else {
        if (countNextSuit(upcard) >= 1) {
          order_up_suit = Suit_next(currSuit);
          return true;
        }
        else {
          return false;
        }
      }
    }
  };

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) override { 
    hand.push_back(upcard);
    int handLow = 0;
    Card min = hand[0];
    for (int j = 0; j < MAX_HAND_SIZE + 1; ++j) {
      if (Card_less(hand[j], min, upcard.get_suit())) {
        min = hand[j];
        handLow = j;
      }
    }
    hand.erase(hand.begin()+handLow);
  };

int countNonTrump (const std::string &trump) {
    int nonTrumpCount = 0;
    for (int i = 0; i < hand.size(); ++i) {
      if (!hand[i].is_trump(trump)) {
        nonTrumpCount++;
      }
    }
    return nonTrumpCount;
  }

  void nonTrumpReturn (const std::string &trump, Card &highest, int &highIndex) {
    for (int i = 0; i < hand.size(); ++i) {
        if (!hand[i].is_trump(trump) && operator<=(highest, hand[i])) {
          highest = hand[i];
          highIndex = i;
        }
      }
  }
  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  //play the highest non-trump 
  //if there is only trump, then play the highest trump
  Card lead_card(const std::string &trump) override {
    Card highest;
    Card leftC;
    Card rightC;
    int left = 0;
    int right = 0;
    int highIndex = 0;
    bool rightPresent = false;
    bool leftPresent = false;

    int nonTrumpCount = countNonTrump(trump); 
    if (nonTrumpCount > 0) {
      nonTrumpReturn (trump, highest, highIndex);
      hand.erase(hand.begin() + highIndex);
      return highest;
    }
    else {
      for(int i = 0; i < hand.size(); ++i) {
        if (hand[i].is_right_bower(trump)) {
          rightC = hand[i];
          right = i; 
          rightPresent = true;
        }
        else if (hand[i].is_left_bower(trump)) {
          leftC = hand[i];
          left = i; 
          leftPresent = true;
        }
        else if (Card_less(highest, hand[i], trump)){
          highest = hand[i];
          highIndex = i;
        }
      }
      if (rightPresent) {
        hand.erase(hand.begin() + right);
        return rightC;
      }
      else if (leftPresent) {
        hand.erase(hand.begin() + left);
        return leftC;
      }
      else {
        hand.erase(hand.begin() + highIndex);
        return highest;
      }
    }
  };

void countCards (const std::string &trump, const Card &led_card, 
int &countCardsInLed, int &trumpC) {
  std::string suitLed = led_card.get_suit(); 
  for (int i = 0; i < hand.size(); ++i) {
      if (hand[i].get_suit() == suitLed && !hand[i].is_left_bower(trump) 
      && !led_card.is_left_bower(trump)) {
        countCardsInLed++;
      }
      else if ((led_card.is_trump(trump) && hand[i].is_trump(trump))) {
        countCardsInLed++;
      }
      if (hand[i].is_trump(trump)) {
        trumpC++;
      }
    }
}

void ledAndTrump (const std::string &trump, const Card &led_card, Card &trumpOnly, 
int &indexTrump) {
  std::string suitLed = led_card.get_suit(); 
  for (int i = 0; i < hand.size(); ++i) {
    if ((hand[i].get_suit() == suitLed || (led_card.is_left_bower(trump) 
    && hand[i].get_suit() == Suit_next(suitLed))) 
    && Card_less(trumpOnly, hand[i], trump)) {
      trumpOnly = hand[i];
      indexTrump = i;
    }
  }
}
  //highest trump 
  //vector
Card play_card(const Card &led_card, const std::string &trump) override {
    std::string suitLed = led_card.get_suit();
    int countCardsInLed = 0;
    int indexLed = 0;
    int indexLow = 0;
    int indexTrump = 0;
    //int trumpNum = 0;
    int trumpC = 0;
    Card trumpOnly = hand[0];
    Card cardToPlay;
    Card lowest = hand[0];
    countCards (trump, led_card, countCardsInLed, trumpC);
    if (countCardsInLed > 0 && led_card.is_trump(trump)) {
      ledAndTrump (trump, led_card, trumpOnly, indexTrump);
      hand.erase(hand.begin() + indexTrump); 
      return trumpOnly;
    }
    else if (countCardsInLed > 0 && suitLed != trump) {
      if (trump == "Spades") {
        cardToPlay = Card(Card::RANK_TWO, Card::SUIT_HEARTS);
      }
      for (int i = 0; i < hand.size(); ++i) {
        if (hand[i].get_suit() == suitLed && Card_less(cardToPlay, hand[i], trump) 
        && !hand[i].is_left_bower(trump)) {
          cardToPlay = hand[i];
          indexLed = i;
        }
      }
      hand.erase(hand.begin() + indexLed); 
      return cardToPlay;
    }
    else if (trumpC == hand.size()) {
      for (int i = 0; i < hand.size(); ++i) {
        if (Card_less(hand[i], lowest, trump)) {
          lowest = hand[i];
          indexLow = i;
        }
      }
      hand.erase(hand.begin() + indexLow);
      return lowest;
    }
    else {
      for (int i = 0; i < hand.size(); ++i) {
        if (!hand[i].is_trump(trump) && Card_less(hand[i], lowest, trump)) {
          lowest = hand[i];
          indexLow = i;
        }
      }
      hand.erase(hand.begin() + indexLow);
      return lowest;
    }
  };

  // Maximum number of cards in a player's hand
  static const int MAX_HAND_SIZE = 5;

  private:
  std::string name;
  std::vector<Card> hand;
  //putting the orderup suit in private

};

class Human : public Player {
  public:

  //default constructor
  Human(){};

  //ctor with input of name 
  Human(const std::string &name_in):name(name_in){}

  //EFFECTS returns player's name
  const std::string & get_name() const override {
    return name;
   };

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c) override { 
    hand.push_back(c);
   };

 void print_temp_const() const {
    vector<Card>temp;
    for (int i = 0; i < hand.size(); ++i) {
        temp.push_back(hand[i]);
    }
    sort(temp.begin(), temp.end());
    for (size_t i=0; i < temp.size(); ++i)
      cout << "Human player " << name << "'s hand: "
        << "[" << i << "] " << temp[i] << "\n";
  };
  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override { 
                          std::string user_choice;    
                          if (round == 2) {
                            print_temp_const();
                            cout << "Human player " << name 
                            << ", please enter a suit, or \"pass\":\n";
                            std::cin >> user_choice;
                            return true;
                          }  
                          else {
                            print_temp_const();                          
                            cout << "Human player " << name 
                            << ", please enter a suit, or \"pass\":\n";
                            std::cin >> user_choice;
                            if (user_choice == "pass") {
                              return false;
                            }
                           else {
                              order_up_suit = user_choice;
                              return true;
                            }
                          }           

                          };
                          

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) override {
    int index;
    print_hand();
    cout << "Discard upcard: [-1]\n";
    cout << "Human player " << name << ", please select a card to discard:\n";
    cout << endl;
    cin >> index;

    //when they want to discard the upcard
    if (index != -1) {
      hand.erase(hand.begin() + index);
      hand.push_back(upcard);
    }
  };

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(const std::string &trump) override {
    string playing;
    print_hand();
    cout << "Human player " << name << ", please select a card:\n";
    std::cin >> playing;
    int play = stoi(playing);
    Card temp = hand[play];
    hand.erase(hand.begin()+play);
    return temp;
  };

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, const std::string &trump) override {
    std::string playing;
    print_hand();
    cout << "Human player " << name << ", please select a card:\n";
    std::cin >> playing;
    int playing_index = stoi(playing);
    Card temp = hand[playing_index];
    hand.erase(hand.begin()+playing_index);
    return temp;
  };

  // Maximum number of cards in a player's hand
  static const int MAX_HAND_SIZE = 5;

  private:
  std::string name;
  //std::array<Card, MAX_HAND_SIZE> hand;
  vector<Card>hand;
  vector<Card>cardWithUp;
    void print_hand() {
      std::sort(hand.begin(), hand.end());
      for (size_t i=0; i < hand.size(); ++i)
        cout << "Human player " << name << "'s hand: "
           << "[" << i << "] " << hand[i] << "\n";
    };

    // void print_card_with_up() {
    //   std::sort(cardWithUp.begin(), cardWithUp.end());
    //   for (size_t i=0; i < cardWithUp.size(); ++i)
    //     cout << "Human player " << name << "'s hand: "
    //        << "[" << i << "] " << cardWithUp[i] << "\n";     
    // };
  
  
};

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) {
  if (strategy == "Simple") {
    return new Simple(name);
  }
  else {
    return new Human(name);
  }
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}
