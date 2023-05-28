// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}


TEST(jack_spades) {
    //trump card is the jack of clubs
    Card c = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_JACK);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_SPADES);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_CLUBS), Card::SUIT_CLUBS);
    //the trump suit is clubs
    //the partner is spades
    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_TRUE(c.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_TRUE(c.is_trump(Card::SUIT_CLUBS));
    ASSERT_FALSE(c < c);
    ASSERT_TRUE(c <= c);
    ASSERT_FALSE(c > c);
    ASSERT_TRUE(c >= c);
    ASSERT_TRUE(c == c);
    ASSERT_FALSE(c != c);
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES), Card::SUIT_CLUBS);
    ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "Jack of Spades");
}

TEST(jack_clubs) {
    Card c = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_JACK);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_CLUBS);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_CLUBS), Card::SUIT_CLUBS);
    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_TRUE(c.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_CLUBS)); //the left bower is the jack of spades
    ASSERT_TRUE(c.is_trump(Card::SUIT_CLUBS));
    ASSERT_FALSE(c < c);
    ASSERT_TRUE(c <= c);
    ASSERT_FALSE(c > c);
    ASSERT_TRUE(c >= c);
    ASSERT_TRUE(c == c);
    ASSERT_FALSE(c != c);
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);

    ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "Jack of Clubs");

}

TEST(jack_diamonds) {
    Card c = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_JACK);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_CLUBS), Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_CLUBS)); //the left bower is the spades
    ASSERT_FALSE(c.is_trump(Card::SUIT_CLUBS));
    ASSERT_FALSE(c < c);
    ASSERT_TRUE(c <= c);
    ASSERT_FALSE(c > c);
    ASSERT_TRUE(c >= c);
    ASSERT_TRUE(c == c);
    ASSERT_FALSE(c != c);
     ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);

    ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "Jack of Diamonds");

}

TEST(jack_hearts) {
    Card c = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_JACK);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_DIAMONDS), Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_DIAMONDS));
    ASSERT_TRUE(c.is_left_bower(Card::SUIT_DIAMONDS));
    ASSERT_TRUE(c.is_trump(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(c < c);
    ASSERT_TRUE(c <= c);
    ASSERT_FALSE(c > c);
    ASSERT_TRUE(c >= c);
    ASSERT_TRUE(c == c);
    ASSERT_FALSE(c != c);
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
    ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "Jack of Hearts");
}

TEST(king_spades) {
    Card c = Card(Card::RANK_KING, Card::SUIT_SPADES);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_KING);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_SPADES);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_HEARTS), Card::SUIT_SPADES);
    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(c.is_trump(Card::SUIT_HEARTS));
    ASSERT_FALSE(c < c);
    ASSERT_TRUE(c <= c);
    ASSERT_FALSE(c > c);
    ASSERT_TRUE(c >= c);
    ASSERT_TRUE(c == c);
    ASSERT_FALSE(c != c);
    ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "King of Spades");
}

TEST(nine_spades) {
    Card c = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_NINE);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_SPADES);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_FALSE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(c.is_trump(Card::SUIT_CLUBS));
    ASSERT_FALSE(c < c);
    ASSERT_TRUE(c <= c);
    ASSERT_FALSE(c > c);
    ASSERT_TRUE(c >= c);
    ASSERT_TRUE(c == c);
    ASSERT_FALSE(c != c);
    ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "Nine of Spades");
}

TEST(queen_clubs) {
    Card c = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_QUEEN);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_CLUBS);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_CLUBS), Card::SUIT_CLUBS);
    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_TRUE(c.is_trump(Card::SUIT_CLUBS));
    ASSERT_FALSE(c < c);
    ASSERT_TRUE(c <= c);
    ASSERT_FALSE(c > c);
    ASSERT_TRUE(c >= c);
    ASSERT_TRUE(c == c);
    ASSERT_FALSE(c != c);
    ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "Queen of Clubs");
}

TEST(ten_clubs) {
    Card c = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_TEN);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_CLUBS);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_SPADES), Card::SUIT_CLUBS);
    ASSERT_FALSE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(c.is_trump(Card::SUIT_SPADES));
    ASSERT_FALSE(c < c);
    ASSERT_TRUE(c <= c);
    ASSERT_FALSE(c > c);
    ASSERT_TRUE(c >= c);
    ASSERT_TRUE(c == c);
    ASSERT_FALSE(c != c);
    ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "Ten of Clubs");
}

 TEST(ace_clubs) {
     Card c = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
     ASSERT_EQUAL(c.get_rank(), Card::RANK_ACE);
     ASSERT_EQUAL(c.get_suit(), Card::SUIT_CLUBS);
     ASSERT_EQUAL(c.get_suit(Card::SUIT_HEARTS), Card::SUIT_CLUBS);
     ASSERT_TRUE(c.is_face_or_ace());
     ASSERT_FALSE(c.is_right_bower(Card::SUIT_HEARTS));
     ASSERT_FALSE(c.is_left_bower(Card::SUIT_HEARTS));
     ASSERT_FALSE(c.is_trump(Card::SUIT_HEARTS));
     ASSERT_FALSE(c < c);
     ASSERT_TRUE(c <= c);
     ASSERT_FALSE(c > c);
     ASSERT_TRUE(c >= c);
     ASSERT_TRUE(c == c);
     ASSERT_FALSE(c != c);
     ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "Ace of Clubs");
 }

TEST(ace_diamonds) {
    Card c = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_ACE);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(c.is_trump(Card::SUIT_HEARTS));
    ASSERT_FALSE(c < c);
    ASSERT_TRUE(c <= c);
    ASSERT_FALSE(c > c);
    ASSERT_TRUE(c >= c);
    ASSERT_TRUE(c == c);
    ASSERT_FALSE(c != c);
    ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "Ace of Diamonds");
}

TEST(nine_diamonds) {
    Card c = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_NINE);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_DIAMONDS), Card::SUIT_DIAMONDS);
    ASSERT_FALSE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_DIAMONDS));
    ASSERT_TRUE(c.is_trump(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(c < c);
    ASSERT_TRUE(c <= c);
    ASSERT_FALSE(c > c);
    ASSERT_TRUE(c >= c);
    ASSERT_TRUE(c == c);
    ASSERT_FALSE(c != c);
    ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "Nine of Diamonds");
}

TEST(ten_hearts) {
    Card c = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_TEN);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_CLUBS), Card::SUIT_HEARTS);
    ASSERT_FALSE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(c.is_trump(Card::SUIT_CLUBS));
    ASSERT_FALSE(c < c);
    ASSERT_TRUE(c <= c);
    ASSERT_FALSE(c > c);
    ASSERT_TRUE(c >= c);
    ASSERT_TRUE(c == c);
    ASSERT_FALSE(c != c);
    ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "Ten of Hearts");
}

TEST(king_hearts) {
    Card c = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_KING);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_SPADES), Card::SUIT_HEARTS);
    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(c.is_trump(Card::SUIT_SPADES));
    ASSERT_FALSE(c < c);
    ASSERT_TRUE(c <= c);
    ASSERT_FALSE(c > c);
    ASSERT_TRUE(c >= c);
    ASSERT_TRUE(c == c);
    ASSERT_FALSE(c != c);
    ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "King of Hearts");
}

TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES), Card::SUIT_CLUBS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
}


TEST(card_less) {
    Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card same = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    //testing they're the same -- first if statement
    ASSERT_FALSE(Card_less(ten_hearts, same, Card::SUIT_HEARTS));
    //second if statement
    ASSERT_TRUE(Card_less(nine_hearts, ten_hearts, Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(ten_hearts, nine_hearts, Card::SUIT_HEARTS));
    //fourth
    ASSERT_FALSE(Card_less(nine_hearts, nine_spades, Card::SUIT_HEARTS));
    //fifth
    ASSERT_TRUE(Card_less(nine_spades, nine_hearts, Card::SUIT_HEARTS));
    //sixth
    ASSERT_TRUE(Card_less(nine_hearts, ten_hearts, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(ten_hearts, nine_hearts, Card::SUIT_SPADES));

    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(jack_spades, jack_clubs, Card::SUIT_SPADES));

    ASSERT_FALSE(Card_less(jack_spades, nine_hearts, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(jack_spades, jack_diamonds, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(jack_spades, jack_clubs, Card::SUIT_CLUBS));

    ostringstream oss;
    oss << ten_hearts;
    ASSERT_EQUAL(oss.str(), "Ten of Hearts");
}

TEST(card_less_with_led) {
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card same = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    
    //using as led card
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);

    ASSERT_FALSE(Card_less(ten_diamonds, same, ten_diamonds, Card::SUIT_SPADES));
    ASSERT_TRUE (Card_less(ten_diamonds, king_diamonds, queen_diamonds, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(king_diamonds, ten_diamonds, queen_diamonds, Card::SUIT_SPADES));

    ASSERT_TRUE(Card_less(nine_spades, king_spades, ten_diamonds, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(king_spades, nine_spades, ten_diamonds, Card::SUIT_SPADES));

    //false when the left is the same suit as the trump and the right is not
    ASSERT_FALSE(Card_less(nine_spades, king_diamonds, jack_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ten_diamonds, nine_spades, king_diamonds, Card::SUIT_SPADES));
    //what about when the led and the trump are the same suit
    ASSERT_FALSE(Card_less(nine_spades, ten_diamonds, king_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(queen_diamonds, king_spades, nine_spades, Card::SUIT_SPADES));

    //did not do one that goes through the last else if statments
}

TEST(random_numbers) {
    Card two_diamonds = Card(Card::RANK_TWO, Card::SUIT_DIAMONDS);
    Card three_diamonds = Card(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(two_diamonds.get_rank(), Card::RANK_TWO);
    ASSERT_EQUAL(three_diamonds.get_rank(), Card::RANK_THREE);
    ASSERT_EQUAL(two_diamonds.get_suit(), Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(three_diamonds.get_suit(), Card::SUIT_DIAMONDS);
    ASSERT_FALSE(two_diamonds.is_face_or_ace());
    ASSERT_FALSE(three_diamonds.is_face_or_ace());
    ASSERT_FALSE(two_diamonds.is_right_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(three_diamonds.is_right_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(two_diamonds.is_left_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(three_diamonds.is_left_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(two_diamonds.is_trump(Card::SUIT_SPADES));
    ASSERT_FALSE(three_diamonds.is_trump(Card::SUIT_SPADES));
    ASSERT_TRUE(two_diamonds < three_diamonds);
    ASSERT_FALSE(three_diamonds < two_diamonds);

    //ranks are equal then compare suit

    ASSERT_FALSE(two_diamonds < two_spades);
    ASSERT_TRUE(two_spades < two_diamonds);

    ASSERT_TRUE(Card_less(two_diamonds, two_spades, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(two_diamonds, two_spades, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(two_diamonds, three_diamonds, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(three_diamonds, two_diamonds, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(two_diamonds, three_diamonds, Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(three_diamonds, two_diamonds, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(two_diamonds, king_diamonds, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(two_diamonds, king_diamonds, Card::SUIT_SPADES));
    
    ostringstream oss;
    oss << two_diamonds;
    ASSERT_EQUAL(oss.str(), "Two of Diamonds");
}

// Add more test cases here

TEST_MAIN()
