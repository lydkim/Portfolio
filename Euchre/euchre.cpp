// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "Card.h"
#include "Player.h"
#include <iostream>
#include <fstream>

using namespace std;

class Game {
  public:
    Game(const std::vector<Player*> players_in, const int dealer_in, 
    const bool shuffle_in, const int numPlayed_in) 
      :players(players_in), dealer(dealer_in), 
      shuffleBool(shuffle_in), numPlayed(numPlayed_in) {}
    // set the players and shuffle and variables

    //plays one round 
    void play() {
      if ((dealer + 1) % 4 == 0) {
          left = 0; 
        }
        else {
          left = dealer + 1;
        }
      if (shuffleBool == true) {
        for (int i = 0; i < numPlayed; ++i) {
          pack.reset();
          pack.shuffle(); 
        }
        pack.reset();
        pack.shuffle(); 
      }
      else {
        pack.reset();
      }
      deal(dealer, left);
      make_trump(dealer, left, upcard);
      std::vector<int> winHand;
      for (int i = 0; i < 5; ++i) {
        if (i == 0) {
          play_hand(dealer, left, trump);
        }
        else {
          play_hand(dealer, winTrick, trump);
        }
        winHand.push_back(winTrick);
      }
      int teamOne = 0;
      int teamTwo = 0;
      for (int i = 0; i < 5; ++i) {
        if (winHand[i] == 0 || winHand[i] == 2) {
          teamOne++;
        }
        else {
          teamTwo++;
        }
      }
      points (teamOne, teamTwo);
      //does pack reset need to be called after every round 
      //pack.reset();
    }

    void points (int &teamOne, int &teamTwo) {
      pointsOne = 0; 
      pointsTwo = 0;
      //team one
      if ((teamOne == 3 || teamOne == 4) && (orderedUp == 0 || orderedUp == 2)) {
        pointsOne++;
      }
      else if (teamOne == 5 && (orderedUp == 0 || orderedUp == 2)) {
        //march
        pointsOne = pointsOne + 2; 
      }
      else if (teamOne >= 3 && (orderedUp == 1 || orderedUp == 3)) {
        //euchred
        pointsOne = pointsOne + 2; 
      }
      //team two
      else if ((teamTwo == 3 || teamTwo == 4) && (orderedUp == 1 || orderedUp == 3)) {
        pointsTwo ++;
      }
      else if (teamTwo == 5 && (orderedUp == 1 || orderedUp == 3)) {
        pointsTwo = pointsTwo + 2;
      }
      else { //teamTwo >= 3 && orderedUp == false;
        pointsTwo = pointsTwo + 2;
      }
    }

    int get_pointsOne() {
      return pointsOne;
    }

    int get_pointsTwo() {
      return pointsTwo;
    }

    int get_orderedUp() {
      return orderedUp;
    }

    void afterGame(Game game, std::vector<Player*> playerName) {
      if (game.get_pointsOne() > game.get_pointsTwo()) {
      cout << playerName[0]->get_name() << " and " 
      << playerName[2]->get_name() << " win the hand" << endl;
      if (game.get_pointsOne() == 2 && (game.get_orderedUp() == 0 
      || game.get_orderedUp() == 2)) {
        cout << "march!" << endl;
      }
      if (game.get_orderedUp() == 1 || game.get_orderedUp() == 3) {
        cout << "euchred!" << endl;
      }
    }
    else {
      cout << playerName[1]->get_name() << " and " 
      << playerName[3]->get_name() << " win the hand" << endl;
      if (game.get_pointsTwo() == 2 && (game.get_orderedUp() == 1 
      || game.get_orderedUp() == 3)) {
        cout << "march!" << endl;
      }
      if (game.get_orderedUp() == 0 || game.get_orderedUp() == 2) {
        cout << "euchred!" << endl;
      }
    }
    }

  private:
    //array of player pointers goes to simple or human because of polymorphism
    std::vector<Player*> players;
    Pack pack;
    const int TOTAL_PLAYERS = 4;
    int dealer;
    int left;
    bool shuffleBool = false; 
    int numPlayed;
    Card upcard;
    int orderedUp;
    string trump;
    int winTrick = 0;
    int pointsOne = 0; 
    int pointsTwo = 0;

    // void shuffle() {
    //   pack.shuffle(); 
    // }
    
    //use mod to be able to get indexes
    void deal(int &dealer, int next) {
      for (int i = 0; i < TOTAL_PLAYERS; ++i) {
        if (i == 0 || i == 2) {
          players[next]->add_card(pack.deal_one());
          players[next]->add_card(pack.deal_one());
          players[next]->add_card(pack.deal_one());
        }
        else {
          players[next]->add_card(pack.deal_one());
          players[next]->add_card(pack.deal_one());
        }
        if ((next + 1) % 4 == 0) {
          next = 0; 
        }
        else {
          next++;
        }
      }
      //round 2 
      for (int i = 0; i < TOTAL_PLAYERS; ++i) {
        if (i == 0 || i == 2) {
          players[next]->add_card(pack.deal_one());
          players[next]->add_card(pack.deal_one());
        }
        else {
          players[next]->add_card(pack.deal_one());
          players[next]->add_card(pack.deal_one());
          players[next]->add_card(pack.deal_one());
        }
        if ((next + 1) % 4 == 0) {
          next = 0; 
        }
        else {
          next++;
        }
      }
      upcard = pack.deal_one();
      cout << upcard << " turned up" << endl;
    }

    void roundTwo (bool &orderedR2, int &next) {
      int diff_count = 0;
      string upcard_suit = upcard.get_suit();
      while (diff_count < TOTAL_PLAYERS) {
          //players[next]->make_trump(upcard, false, 2, upcard_suit);
          if (players[next]->make_trump(upcard, false, 2, upcard_suit)) {
            orderedR2 = true;
            orderedUp = next;
            trump = Suit_next(upcard.get_suit());
            cout << players[next]->get_name() << " orders up " << trump << endl;
            cout << endl;
            break; 
          }
          else {
            cout << players[next]->get_name() << " passes" << endl;
          }
          diff_count++;
          if ((next + 1) % 4 == 0) {
            next = 0; 
          }
          else {
            next++;
          }
        }
    }

    void make_trump(int &dealer, int next, Card &upcard) {
      //int last = (next + 3) % 4;
      string upcard_suit = upcard.get_suit();
      bool ordered = false;
      bool orderedR2 = false;
      int count = 0;

      while(count < TOTAL_PLAYERS) {
        //players[next]->make_trump(upcard, false, 1, upcard_suit);
        if (players[next]->make_trump(upcard, false, 1, upcard_suit)) {
          ordered = true;
          orderedUp = next;
          trump = upcard.get_suit();
          cout << players[next]->get_name() << " orders up " << trump << endl;
          cout << endl;
          break; 
        }
        else {
          cout << players[next]->get_name() << " passes" << endl;
        }
        count++;
        if ((next + 1) % 4 == 0) {
          next = 0; 
        }
        else {
          next++;
        }
      }
      if (ordered) {
        players[dealer]->add_and_discard(upcard);
      }
      else {
        roundTwo (orderedR2, next);
        if (!orderedR2) {
          players[dealer]->make_trump(upcard, true, 2, upcard_suit);
          orderedUp = dealer;
          trump = Suit_next(upcard.get_suit());
          cout << players[dealer]->get_name() << " orders up " << trump << endl;
          cout << endl;
        }
        
      }
    }
    
    void play_hand(int dealer, int next, const std::string &trump) {
      //int last = (next + 4) % 4;
      std::vector<Card> played;
      int count = 1;
      Card led_card = players[next]->lead_card(trump);
      played.push_back(led_card);
      cout << led_card << " led by " << *players[next] << endl; 
      Card current_highest = played[0];
      int highest_index = next;
      if ((next + 1) % 4 == 0) {
        next = 0; 
      }
      else {
        next++;
      }

      while(count < 4) {
        Card playing = players[next]->play_card(led_card, trump);
        played.push_back(playing);
        cout << playing << " played by " << *players[next] << endl;
        if (Card_less(current_highest, played[count], led_card, trump)) {
          current_highest = played[count];
          highest_index = next;
        }
        count++;
        if ((next + 1) % 4 == 0) {
          next = 0; 
        }
        else {
          next++;
        }
      }

      cout << *players[highest_index] << " takes the trick" << endl;
      cout << endl;
      winTrick = highest_index; 
      //delete everything in played
    }
};


void error() {
      cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
      << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
      << "NAME4 TYPE4" << endl;
}

void printScore (int &scoreOne, int &scoreTwo, std::vector<Player*> &playerName) {
    cout << playerName[0]->get_name() << " and " << playerName[2]->get_name() 
    << " have " << scoreOne << " points" << endl;
    cout << playerName[1]->get_name() << " and " << playerName[3]->get_name() 
    << " have " << scoreTwo << " points" << endl;
    cout << endl;
}

void printFinal (int &scoreOne, int &scoreTwo, std::vector<Player*> &playerName) {
    if (scoreOne > scoreTwo) {
    cout << playerName[0]->get_name() << " and " 
    << playerName[2]->get_name() << " win!" << endl;
    }
    else {
    cout << playerName[1]->get_name() << " and " 
    << playerName[3]->get_name() << " win!" << endl;
  }
}

void increaseDealer(int &dealer) {
  if ((dealer + 1) % 4 == 0) {
      dealer = 0;
    }
    else {
      dealer++;
    }
}

void printBegin (int &numPlayedMain, int &dealer, std::vector<Player*> &playerName) {
  cout << "Hand " << numPlayedMain << endl;
  cout << playerName[dealer]->get_name() << " deals" << endl;
}

void deletePlay (std::vector<Player*> &playerName) {
  for (size_t i = 0; i < playerName.size(); ++i) {
    delete playerName[i];
  }
}

void makeShuffle(string &shuffle_argument, bool &shuffle) {
  if (shuffle_argument == "shuffle") {
    shuffle = true; 
  }
  else {
    shuffle = false;
  }
}

int main(int argc, char *argv[]) { 
  string shuffle_argument = argv[2];
  int points = atoi(argv[3]);
  string first_person = argv[5];
  string second_person = argv[7];
  string third_person = argv[9];
  string fourth_person = argv[11];
  //print command line
  for (int i = 0; i < argc; ++i) {
    cout << argv[i] << " ";
  }
  cout << endl;

  //error 1: checking there are 12 arguments and executable name
  if ((argc != 12) || ((points < 1) || (points > 100)) || 
  ((shuffle_argument != "shuffle") && (shuffle_argument != "noshuffle")) || 
  ((first_person != "Simple") && (first_person != "Human")) || 
  ((second_person != "Simple") && (second_person != "Human")) || 
  ((third_person != "Simple") && 
  (third_person != "Human")) || ((fourth_person != "Simple") && 
  (fourth_person != "Human"))) {
    error();
    return 1;
  }

  //checking the file opened
  ifstream fin(argv[1]);
  if (!fin.is_open()) {
    cout << "Error opening " << argv[1] << endl;
    return 1;
  }
  //close file but no errors if you dont

  std::vector<Player*> playerName;
  playerName.push_back(Player_factory(argv[4], argv[5]));
  playerName.push_back(Player_factory(argv[6], argv[7]));
  playerName.push_back(Player_factory(argv[8], argv[9]));
  playerName.push_back(Player_factory(argv[10], argv[11]));

  int scoreOne = 0;
  int scoreTwo = 0;
  int dealer = 0; 
  bool shuffle;
  
  makeShuffle(shuffle_argument, shuffle);
  
  int numPlayedMain = 0; 
  
  while (scoreOne < points && scoreTwo < points) {
    Game game(playerName, dealer, shuffle, numPlayedMain);
    printBegin (numPlayedMain, dealer, playerName);
    game.play();

    game.afterGame(game, playerName);

    //add points to score 
    scoreOne = scoreOne + game.get_pointsOne();
    scoreTwo = scoreTwo + game.get_pointsTwo();

    //print score 
    printScore (scoreOne, scoreTwo, playerName); 

    //updates to be able to play the next round 
    increaseDealer(dealer);


    numPlayedMain++;
  }
    
    printFinal (scoreOne, scoreTwo, playerName);

  //say who wins the game 

  //play the game for the correct amount of rounds based on points 
  //remember to assign variables needed for the functions 
  //reset the pack everytime, leave the shuffled but reset the index 
  //return 0
  deletePlay (playerName);

}