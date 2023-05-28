// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(factory_and_printing) {
    //human player
    Player * human = Player_factory("Human", "Human");
    //simple player
    Player * simple = Player_factory("simple", "Simple");

    ostringstream oss1;
    oss1 << * human;
    ASSERT_EQUAL(oss1.str(), "Human");

    ostringstream oss2;
    oss2 << *simple;
    ASSERT_EQUAL(oss2.str(), "simple");

    delete human;
    delete simple;
}


//make trump
//upcard ace of diamonds
TEST(make_trump_ace_diamonds){
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));

    Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    string trump;
    bool orderup = first->make_trump(
        ace_diamonds,
        false,
        1,
        trump
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);

    delete first;
}

//upcard nine of spades
TEST(make_trump_nine_spades) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));

    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = first->make_trump(
        nine_spades,
        false,
        2,
        trump
    );

    ASSERT_TRUE(orderup);
    //ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

    delete first;
}


TEST(make_trump_false_only_one) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));

    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    string trump;
    bool orderup = first->make_trump(
        queen_diamonds,
        false,
        1,
        trump
    );

    ASSERT_FALSE(orderup);

    delete first;
}

TEST(make_trump_false_zero) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));

    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    string trump;
    bool orderup = first->make_trump(
        queen_diamonds,
        false,
        1,
        trump
    );

    ASSERT_FALSE(orderup);

    delete first;
}

TEST(make_trump_second_round) {
    Player * first = Player_factory("first", "Simple");
    //if they have the card the same color as the upcard
    first->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));

    Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    string trump;
    bool orderup = first->make_trump (
        ten_diamonds,
        false,
        2,
        trump
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_HEARTS);

    delete first;
}

//not sure what the upcard is 
TEST(make_trump_is_dealer) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));

    Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    string trump;
    bool orderup = first->make_trump(
        ace_diamonds,
        true,
        2,
        trump
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_HEARTS);

    delete first;
}

TEST(make_trump_upcard_trump) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));

    //this is the upcard
    Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
    string trump;
    bool orderup = first->make_trump(
        ten_spades,
        false,
        1,
        trump
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_SPADES);

    delete first;
}

TEST(make_trump_upcard_trump_opposite) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));

    //this is the upcard
    Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
    string trump;
    bool orderup = first->make_trump(
        ten_spades,
        false,
        1,
        trump
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_SPADES);

    delete first;
}

TEST(make_trump_upcard_trump_opposite_another_jack) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));

    //this is the upcard
    Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
    string trump;
    bool orderup = first->make_trump(
        ten_spades,
        false,
        1,
        trump
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_SPADES);

    delete first;
}

TEST(make_trump_upcard_trump_opposite_another_jack_second_round) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));

    //this is the upcard
    Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
    string trump;
    bool orderup = first->make_trump(
        ten_spades,
        false,
        2,
        trump
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

    delete first;
}

// TEST(make_trump_round_two_false) {
//     Player * first = Player_factory("first", "Simple");
//     first->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
//     first->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
//     first->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
//     first->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
//     first->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));

//     //this is the upcard
//     Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
//     string trump;
//     bool orderup = first->make_trump(
//         ten_spades,
//         false,
//         2,
//         trump
//     );

//     ASSERT_FALSE(orderup);

//     delete first;
// }

// TEST(make_trump_round_two_false_again) {
//     Player * first = Player_factory("first", "Simple");
//     first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
//     first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
//     first->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
//     first->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
//     first->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));

//     //this is the upcard
//     Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
//     string trump;
//     bool orderup = first->make_trump(
//         ten_spades,
//         false,
//         2,
//         trump
//     );

//     ASSERT_FALSE(orderup);

//     delete first;
// }

//ADDED LATER
//when the upcard is trump round 1
TEST(make_trump_upcard_trump_round_one) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS)); //this is also considered a heart
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS)); //this is one

    //this is the upcard
    Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    string trump;
    bool orderup = first->make_trump(
        jack_hearts,
        false,
        1,
        trump
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_HEARTS);


    delete first;
}
TEST(make_trump_upcard_trump_round_one_make_false) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS)); //this is also considered a heart
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS)); 

    //this is the upcard
    Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    string trump;
    bool orderup = first->make_trump(
        jack_hearts,
        false,
        1,
        trump
    );

    ASSERT_FALSE(orderup);
    
    Card nine_clubs(Card::RANK_NINE, Card::SUIT_CLUBS);
    string trump_again;
    bool orderup_round_two = first->make_trump(
        nine_clubs,
        false,
        2,
        trump_again
    );

    ASSERT_TRUE(orderup_round_two)

    delete first;
}
//when the upcard is trump round 2
TEST(make_trump_upcard_trump_round_two) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS)); //this is also considered a heart
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS)); //this is one

    //this is the upcard
    Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    string trump;
    bool orderup = first->make_trump(
        jack_hearts,
        false,
        2,
        trump
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);

    delete first;
}
//cards in hand are all trump, upcard is anything round 1
TEST(make_trump_hand_all_trump_round_one) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS)); //left bower
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS)); 

    //this is the upcard
    Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    string trump;
    bool orderup = first->make_trump(
        jack_hearts,
        false,
        1,
        trump
    );

    ASSERT_FALSE(orderup);

    bool orderup_again = first->make_trump(
        jack_hearts,
        false,
        2,
        trump
    );

    ASSERT_TRUE(orderup_again);
    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);

    delete first;
}

TEST(make_trump_hand_all_trump_round_one_different) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS)); //left bower
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    first->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS)); 

    //this is the upcard
    Card ten_hearts(Card::RANK_TEN, Card::SUIT_HEARTS);
    string trump;
    bool orderup = first->make_trump(
        ten_hearts,
        false,
        1,
        trump
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_HEARTS);

    delete first;
}
//cards in hand are all trump, upcard is anything round 2
TEST(make_trump_hand_all_trump_round_two) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS)); //left bower
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS)); //right bower
    first->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS)); 

    //this is the upcard
    Card ten_hearts(Card::RANK_TEN, Card::SUIT_HEARTS);
    string trump;
    bool orderup = first->make_trump(
        ten_hearts,
        false,
        2,
        trump
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);

    delete first;
}

TEST(make_trump_hand_all_trump_round_two_false) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS)); 
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS)); //the only heart
    first->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS)); 

    //this is the upcard
    Card ten_hearts(Card::RANK_TEN, Card::SUIT_HEARTS);
    string trump;
    bool orderup = first->make_trump(
        ten_hearts,
        false,
        2,
        trump
    );
    
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);

    delete first;
}

//add and discard and lead card
TEST(lead_test_nine_diamonds) {
    Player * first = Player_factory("first", "Simple");
    first -> add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    first -> add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    first -> add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    first -> add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS)); //right bower
    first -> add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));


    first->add_and_discard(
        Card(Card::RANK_NINE, Card::SUIT_DIAMONDS) // upcard
    );

    //discards nine diamonds
    Card card_led = first->lead_card(Card::SUIT_DIAMONDS);

    Card jack_diamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(card_led, jack_diamonds);

    delete first;
}

TEST(lead_test_nine_diamonds_non_trump) {
    Player * first = Player_factory("first", "Simple");
    first -> add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    first -> add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    first -> add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    first -> add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    first -> add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));


    first->add_and_discard(
        Card(Card::RANK_NINE, Card::SUIT_DIAMONDS) // upcard
    );
    
    //discards nine diamonds
    Card card_led = first->lead_card(Card::SUIT_SPADES);

    Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(card_led, ace_diamonds);

    delete first;
}

// TEST(lead_non_trump_variety) {
//     Player * first = Player_factory("first", "Simple");
//     first -> add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
//     first -> add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
//     first -> add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
//     first -> add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
//     first -> add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));


//     first->add_and_discard(
//         Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
//     );
    
//     //discards nine hearts
//     Card card_led = first->lead_card(Card::SUIT_SPADES);

//     Card ace_clubs(Card::RANK_ACE, Card::SUIT_CLUBS);
//     ASSERT_EQUAL(card_led, ace_clubs);

//     delete first;
// }

TEST(lead_ace_spades) {
Player * first = Player_factory("first", "Simple");
    first -> add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    first -> add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    first -> add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    first -> add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES)); //left bower
    first -> add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));


    first->add_and_discard(
        Card(Card::RANK_ACE, Card::SUIT_SPADES) // upcard
    );
    //would drop ten hearts

    Card card_led = first->lead_card(Card::SUIT_DIAMONDS);
    //would play the highest card
    Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, ace_spades);

    delete first;
}

TEST(lead_jack_heart) {
Player * first = Player_factory("first", "Simple");
    first -> add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    first -> add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS)); //
    first -> add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    first -> add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    first -> add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS)); //this considered a jack of diamonds


    first->add_and_discard(
        Card(Card::RANK_ACE, Card::SUIT_SPADES) // upcard
    );
    //would drop ten hearts

    Card card_led = first->lead_card(Card::SUIT_DIAMONDS);
    //would play the highest card
    Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, ace_spades);

    delete first;
}

TEST(lead_all_trump_cards_only) {
Player * first = Player_factory("first", "Simple");
    first -> add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    first -> add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    first -> add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    first -> add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    first -> add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS)); //right bower

    //if it doesnt have non trump then it returns trump
    first->add_and_discard(
        Card(Card::RANK_JACK, Card::SUIT_DIAMONDS) // upcard
    );
    //would drop ten hearts
    //this diamond is considered a heart

    Card card_led = first->lead_card(Card::SUIT_HEARTS);
    //would play the highest card
    Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(card_led, jack_hearts);

    delete first;
}
//lead with the left and right in the hand
TEST(lead_left_and_right_bower_in_the_hand) {
    Player * first = Player_factory("first", "Simple");
    first -> add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    first -> add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    first -> add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS)); //left bower
    first -> add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    first -> add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS)); //right bower

    //if it doesnt have non trump then it returns trump
    first->add_and_discard(
        Card(Card::RANK_TEN, Card::SUIT_DIAMONDS) // upcard
    );
    //would discard nine hearts
    //now they do not only have trump
    //would play the highest non-trump -- the only nontrump is ten of diamonds 

    Card card_led = first->lead_card(Card::SUIT_HEARTS);

    Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(card_led, ten_diamonds);

    delete first;
}

//when there is an ace in the hand
TEST(lead_ace_in_hand) {
    Player * first = Player_factory("first", "Simple");
    first -> add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    first -> add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    first -> add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    first -> add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    first -> add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS)); //right bower

    //if it doesnt have non trump then it returns trump
    first->add_and_discard(
        Card(Card::RANK_JACK, Card::SUIT_DIAMONDS) // left bower
    );
    //would drop nine of spades

    Card card_led = first->lead_card(Card::SUIT_HEARTS);
    //would play the highest non-trump
    Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(card_led, ace_diamonds);

    delete first;
}

TEST(lead_nine_in_hand_different) {
    Player * first = Player_factory("first", "Simple");
    first -> add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    first -> add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    first -> add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    first -> add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    first -> add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS)); //right bower

    //if it doesnt have non trump then it returns trump
    first->add_and_discard(
        Card(Card::RANK_JACK, Card::SUIT_DIAMONDS) // left bower
    );
    //would drop nine of spades

    Card card_led = first->lead_card(Card::SUIT_HEARTS);
    //would play the highest non-trump -- diamonds in higher than clubs and spades
    Card nine_clubs(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(card_led, nine_clubs);

    delete first;
}

TEST(lead_two_cards) {
    Player * first = Player_factory("first", "Simple");
    first -> add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    first -> add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));

    Card card_led = first->lead_card(Card::SUIT_DIAMONDS);
    Card nine_clubs(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_EQUAL(card_led, nine_clubs);

    delete first;
}

//play card
TEST(play_card_same_suit) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));

    //hand has all the same suit as the suit led
    Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
    Card card_played = first->play_card(
        ace_spades,
        "Diamonds"
    );

    ASSERT_EQUAL(card_played, Card(Card::RANK_KING, Card::SUIT_SPADES));
    delete first;
}

TEST(play_card_none) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

    //hand has all the same suit as the suit led
    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card card_played = first->play_card(
        ace_hearts,
        "Spades"
    );

    ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    delete first;
}

TEST(play_all_trump) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    //first->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));

    //when the trump suit is spades, then the jack of clubs is considered a spades so it only has trump cards
    //hand has all the same suit as the suit led
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS); //this is considered a spade so it follows suit and plays highest
    Card card_played = first->play_card(
        jack_clubs,
        Card::SUIT_SPADES
    );

    ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_SPADES));
    delete first;
}



TEST(play_all_trump_again) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));

    //hand has all the same suit as the suit led
    Card jack_clubs(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card card_played = first->play_card(
        jack_clubs,
        Card::SUIT_SPADES
    );

    ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
    delete first;
}

TEST(play_mix) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    first->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));

    //hand has all the same suit as the suit led
    Card ten_hearts(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card card_played = first->play_card(
        ten_hearts,
        "Clubs"
    );

    ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    delete first;
}



TEST(play_no_card_in_led_suit) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    first->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));

    //hand has all the same suit as the suit led
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card card_played = first->play_card(
        jack_clubs,
        "Diamonds"
    );

    ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    delete first;
}

TEST(play_following_led) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));

    //hand has all the same suit as the suit led
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card card_played = first->play_card(
        jack_clubs,
        "Diamonds"
    );

    ASSERT_EQUAL(card_played, Card(Card::RANK_KING, Card::SUIT_CLUBS));
    delete first;
}

TEST(play_only_trump_suits) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));

    //hand has all the same suit as the suit led
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card card_played = first->play_card(
        jack_clubs,
        "Diamonds"
    );

    ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    delete first;
}

//lead is left bower and cards are in the trump suit
TEST(play_lead_left_bower_hand_trump) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));

    //hand has all the same suit as the suit led
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS); //considered spades
    Card card_played = first->play_card(
        jack_clubs,
        "Spades"
    );

    ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_SPADES));
    delete first;
}

// TEST(play_lead_left_bower_hand_trump_different) {
//     Player * first = Player_factory("first", "Simple");
//     first->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
//     first->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
//     first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
//     first->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
//     first->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));

//     //hand has all the same suit as the suit led
//     Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS); //considered spades
//     Card card_played = first->play_card(
//         jack_clubs,
//         "Spades"
//     );

//     ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_SPADES));
//     delete first;
// }

TEST(play_lead_left_bower_hand_trump_different_again_play_multiple_times) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES)); //fourth
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES)); //third
    first->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES)); //second
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES)); //fifth
    first->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES)); //played first

    //hand has all the same suit as the suit led
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS); //considered spades
    Card card_played = first->play_card(
        jack_clubs,
        "Spades"
    );
    ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_SPADES));

    Card card_play_second = first->play_card(
        jack_clubs,
        "Spades"
    );
    ASSERT_EQUAL(card_play_second, Card(Card::RANK_KING, Card::SUIT_SPADES));

    Card card_play_third = first->play_card(
        jack_clubs,
        "Spades"
    );
    ASSERT_EQUAL(card_play_third, Card(Card::RANK_QUEEN, Card::SUIT_SPADES));

    Card card_play_fourth = first->play_card(
        jack_clubs,
        "Spades"
    );
    ASSERT_EQUAL(card_play_fourth, Card(Card::RANK_TEN, Card::SUIT_SPADES));

    Card card_play_fifth = first->play_card(
        jack_clubs,
        "Spades"
    );
    ASSERT_EQUAL(card_play_fifth, Card(Card::RANK_NINE, Card::SUIT_SPADES));

    delete first;
}

TEST(play_same_rank_three_cards) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    //first->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));

    //hand has all the same suit as the suit led
    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS); //considered spades
    Card card_played = first->play_card(
        queen_diamonds,
        "Spades"
    );

    ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    delete first;
}

TEST(play_and_add_card_one_card) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));

    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS); //considered spades
    Card card_played = first->play_card(
        queen_diamonds,
        "Spades"
    );

    ASSERT_EQUAL(card_played, Card(Card::RANK_TEN, Card::SUIT_SPADES));
    delete first;
}

TEST(play_and_add_card_two_cards) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    first->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));

    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS); 
    Card card_played = first->play_card(
        queen_diamonds,
        "Spades"
    );
    

    ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));

    Card card_play = first->play_card(
        queen_diamonds,
        "Spades"
    );

    ASSERT_EQUAL(card_play, Card(Card::RANK_TEN, Card::SUIT_SPADES))
    delete first;
}

TEST(lead_four) {
    Player * first = Player_factory("first", "Simple");
    first -> add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    first -> add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    first -> add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    first -> add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    
    //discards nine diamonds
    Card card_led = first->lead_card(Card::SUIT_SPADES);

    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(card_led, queen_diamonds);

    delete first;
}

TEST(lead_one_nontrump) {
    Player * first = Player_factory("first", "Simple");
    first -> add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    
    //discards nine diamonds
    Card card_led = first->lead_card(Card::SUIT_SPADES);

    Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(card_led, queen_hearts);

    delete first;
}

TEST(lead_one_trump) {
    Player * first = Player_factory("first", "Simple");
    first -> add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    
    //discards nine diamonds
    Card card_led = first->lead_card(Card::SUIT_SPADES);

    Card queen_spades(Card::RANK_QUEEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, queen_spades);

    delete first;
}

TEST(play_one_trump) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));

    //hand has all the same suit as the suit led
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card card_played = first->play_card(
        jack_clubs,
        "Diamonds"
    );

    ASSERT_EQUAL(card_played, Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    delete first;
}

TEST(play_one_nontrump) {
    Player * first = Player_factory("first", "Simple");
    first->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));

    //hand has all the same suit as the suit led
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card card_played = first->play_card(
        jack_clubs,
        "Diamonds"
    );

    ASSERT_EQUAL(card_played, Card(Card::RANK_TEN, Card::SUIT_SPADES));
    delete first;
}

TEST_MAIN()

