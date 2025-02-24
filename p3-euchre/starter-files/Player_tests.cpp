#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

// Creates two players and verifies that get_name()
// returns the player's name
TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;

    Player * obama = Player_factory("Obama", "Human");
    ASSERT_EQUAL("Obama", obama->get_name());

    delete obama;
}

// Creates a player and verifies that player's name
// is printed when using the stream insertion operator
TEST(test_player_insertion) {
    // Create a Human player
    Player * human = Player_factory("NotRobot", "Human");
  
    // Print the player using the stream insertion operator
    ostringstream oss1;
    oss1 << * human;
  
    // Verify that the output is the player's name
    ASSERT_EQUAL(oss1.str(), "NotRobot");
  
    // Create a Simple player
    Player * alice = Player_factory("Alice", "Simple");
  
    // Print the player using the stream insertion operator
    ostringstream oss2;
    oss2 << *alice;
    ASSERT_EQUAL(oss2.str(), "Alice");
  
    // Clean up players that were created using Player_factory()
    delete human;
    delete alice;
  }


  TEST(test_simple_make_trump_round_1)
  {
     // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit

  // If upcard is nine spades, and he has 2 face + ace spades
  // he should order up -> order up is true
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;

  Player * obama = Player_factory("Obama", "Simple");
  obama->add_card(Card(NINE, SPADES));
  obama->add_card(Card(TEN, SPADES));
  obama->add_card(Card(QUEEN, SPADES));
  obama->add_card(Card(KING, SPADES));
  obama->add_card(Card(ACE, SPADES));

  // Obama makes trump
  // Now we will make the upcard something that obama does not have
  // So he should not have 2+ face or ace cards of upcard's suit
  // and order up should return false

  Card nine_hearts(NINE, HEARTS);
  Suit trump2;
  bool orderup2 = obama->make_trump(
    nine_hearts,    //Upcard
    false,          // Obama is not the dealer
    1,              // 1st round
    trump2          // Suit ordered up (if any)
  );

  ASSERT_FALSE(orderup2);

  delete obama;

  }

  TEST(test_simple_make_trump_round_2)
  {
    // Screw the dealer!! Dealer will order up the suit
    // with the same color as the upcard

    // Bob has no face or ace with same suit as upcard or
    // the next suit of the upcard

    // Bob has only spades
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));


    Card nine_hearts(NINE, HEARTS);
    Suit trump;

    bool orderup = bob->make_trump(
        nine_hearts,    // Upcard
        true,           // Is dealer
        2,              // Round 2
        trump           // Suit ordered up
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, DIAMONDS);

    delete bob;

    // Is not the dealer but has at least one card that 
    // is the next suit of the upcard

    Player * obama = Player_factory("Obama", "Simple");
    obama->add_card(Card(NINE, SPADES));
    obama->add_card(Card(TEN, SPADES));
    obama->add_card(Card(QUEEN, SPADES));
    obama->add_card(Card(KING, SPADES));
    obama->add_card(Card(JACK, HEARTS));

    // If the upcard is nine hearts, we would consider
    // next suit in round 2 (diamonds), making jack hearts
    // a left bower -> should order up diamonds

    Suit trump2;

    bool orderup2 = obama->make_trump(
        nine_hearts,    // Upcard
        false,          // is not dealer
        2,              // Round 2
        trump2          // Suit ordered up     
    );

    ASSERT_TRUE(orderup2);
    ASSERT_EQUAL(trump2, DIAMONDS);

    delete obama;


    // Is not the dealer and has no cards that match the 
    // next suit of the upcard -> will pass

    Player * nelson = Player_factory("Nelson", "Simple");
    nelson->add_card(Card(NINE, SPADES));
    nelson->add_card(Card(TEN, SPADES));
    nelson->add_card(Card(QUEEN, SPADES));
    nelson->add_card(Card(KING, SPADES));
    nelson->add_card(Card(ACE, HEARTS));


    Suit trump3;

    bool orderup3 = nelson->make_trump(
        nine_hearts,       // Upcard
        false,              // is not dealer
        2,                  // Round 2
        trump3              // Suit ordered up
    );

    ASSERT_FALSE(orderup3);

    delete nelson;

  }

  TEST(test_simple_player_lead_card) {
    // When a Simple Player leads a trick, they play the 
    // highest non-trump card in their hand. 
    // If they only have trump cards, they pplay the highest
    // trump card in their hand

    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(
        Card(NINE, HEARTS) // upcard
    );

    // Bob leads
    Card card_led = bob->lead_card(HEARTS);

    // Verify the card Bob selected to lead
    Card ace_spades(ACE, SPADES);
    ASSERT_EQUAL(card_led, ace_spades); //check led card

    delete bob;

    // Let's have obama be the dealer that picks up the upcard
    // And let's let them play the highest non-trump card in their hand
    Player * obama = Player_factory("Obama", "Simple");
    obama->add_card(Card(NINE, SPADES));
    obama->add_card(Card(TEN, SPADES));
    obama->add_card(Card(QUEEN, SPADES));
    obama->add_card(Card(KING, SPADES));
    obama->add_card(Card(ACE, HEARTS));

    obama->add_and_discard(
        Card(NINE, HEARTS) // Upcard
    );

    Card card_led2 = obama->lead_card(HEARTS);

    // Highest non trump is King Spades
    Card king_spades(KING, SPADES);
    ASSERT_EQUAL(card_led2, king_spades);

    delete obama;

    // Now let's have someone be the dealer that will pick up
    // the upcard and have them drop it

    Player * charles = Player_factory("Charles", "Simple");
    charles->add_card(Card(TEN, SPADES));
    charles->add_card(Card(QUEEN, SPADES));
    charles->add_card(Card(KING, SPADES));
    charles->add_card(Card(ACE, SPADES));
    charles->add_card(Card(JACK, SPADES));

    // After this the TEN SPADES should be the lowest card
    charles->add_and_discard(
        Card(NINE, SPADES) // Upcard
    );

    // Charles only has trump cards, so he will play highest one
    // ^ Jack of Spades
    Card card_led3 = charles->lead_card(SPADES);

    Card jack_spades(JACK, SPADES);
    ASSERT_EQUAL(card_led3, jack_spades);

}

TEST(test_add_and_discard)
{
    Player * obama = Player_factory("Obama", "Simple");
    obama->add_card(Card(NINE, SPADES));
    obama->add_card(Card(TEN, SPADES));
    obama->add_card(Card(QUEEN, SPADES));
    obama->add_card(Card(KING, SPADES));
    obama->add_card(Card(ACE, SPADES));

    // Nine of spades should have been dropped, 
    // we will test this
    // Hand - 9 Hearts, A Spades, K Spades, Q Spades, 10 Spades
    obama->add_and_discard(
        Card(NINE, HEARTS) // Upcard
    );


    Card card_led2 = obama->lead_card(HEARTS);

    // Highest non trump is Ace Spades
    Card ace_spades(ACE, SPADES);
    ASSERT_EQUAL(card_led2, ace_spades);

    // Next highest non trump is king spades
    Card card_led3 = obama->lead_card(HEARTS);
    Card king_spades(KING, SPADES);
    ASSERT_EQUAL(card_led3, king_spades);

    // Next highest non trump is queen spades
    Card card_led4 = obama->lead_card(HEARTS);
    Card queen_spades(QUEEN, SPADES);
    ASSERT_EQUAL(card_led4, queen_spades);

    // Next highest non trump is 10 Spades
    Card card_led5 = obama->lead_card(HEARTS);
    Card ten_spades(TEN, SPADES);
    ASSERT_EQUAL(card_led5, ten_spades);

    // Now only 9 Hearts should be left. It should be played
    Card card_led6 = obama->lead_card(HEARTS);
    Card nine_hearts(NINE, HEARTS);
    ASSERT_EQUAL(card_led6, nine_hearts);

    delete obama;

    Player * tyler = Player_factory("Tyler", "Simple");
    // testing if the picked up card will be dropped

    tyler->add_card(Card(TEN, SPADES));
    tyler->add_card(Card(QUEEN, SPADES));
    tyler->add_card(Card(KING, SPADES));
    tyler->add_card(Card(ACE, SPADES));
    tyler->add_card(Card(JACK, SPADES));

    // since picked up card is the lowest, it should be dropped
    tyler->add_and_discard(
        Card(NINE, SPADES) // Upcard
    );

    Card card_led7 = tyler->lead_card(SPADES);

    // Play the highest trump card
    Card jack_spades(JACK, SPADES);
    ASSERT_EQUAL(card_led7, jack_spades);

    // Next highest trump is ace spades
    Card card_led8 = tyler->lead_card(SPADES);
    ASSERT_EQUAL(card_led8, ace_spades);

    // Next highest trump is king spades
    Card card_led9 = tyler->lead_card(SPADES);
    ASSERT_EQUAL(card_led9, king_spades);

    // Next highest non trump is 10 Spades
    Card card_led10 = tyler->lead_card(SPADES);
    ASSERT_EQUAL(card_led10, queen_spades);

    // Now only 9 Hearts should be left. It should be played
    Card card_led11 = tyler->lead_card(SPADES);
    ASSERT_EQUAL(card_led11, ten_spades);

    delete tyler;

    // Upcard is in the middle value of the hand
    // hand has all trumps -> lowest value is dropped

    Player * ted = Player_factory("Ted", "Simple");
    ted->add_card(Card(JACK, HEARTS));
    ted->add_card(Card(JACK, DIAMONDS));
    ted->add_card(Card(ACE, HEARTS));
    ted->add_card(Card(QUEEN, HEARTS));
    ted->add_card(Card(TEN, HEARTS));

    ted->add_and_discard(
        Card(KING, HEARTS)      // Upcard
    );
    
    Card card_led12 = ted->lead_card(HEARTS);
    ASSERT_EQUAL(card_led12, Card(JACK, HEARTS));

    Card card_led13 = ted->lead_card(HEARTS);
    ASSERT_EQUAL(card_led13, Card(JACK, DIAMONDS));

    Card card_led14 = ted->lead_card(HEARTS);
    ASSERT_EQUAL(card_led14, Card(ACE, HEARTS));

    Card card_led15 = ted->lead_card(HEARTS);
    ASSERT_EQUAL(card_led15, Card(KING, HEARTS));

    Card card_led16 = ted->lead_card(HEARTS);
    ASSERT_EQUAL(card_led16, Card(QUEEN, HEARTS));
    
    delete ted;

    // Upcard is in the middle of the values of the hand
    // Hand has some trump, some not trump suit

    Player * jerry = Player_factory("Jerry", "Simple");
    jerry->add_card(Card(JACK, HEARTS));
    jerry->add_card(Card(ACE, DIAMONDS));
    jerry->add_card(Card(NINE, SPADES));
    jerry->add_card(Card(TEN, CLUBS));
    jerry->add_card(Card(ACE, CLUBS));

    ted->add_and_discard(
        Card(QUEEN, DIAMONDS)   // Upcard
    );

    Card card_led17 = jerry->lead_card(DIAMONDS);
    ASSERT_EQUAL(card_led17, Card(ACE, CLUBS));

    Card card_led18 = jerry->lead_card(DIAMONDS);
    ASSERT_EQUAL(card_led18, Card(TEN, CLUBS));

    Card card_led19 = jerry->lead_card(DIAMONDS);
    ASSERT_EQUAL(card_led19, Card(JACK, HEARTS));

    Card card_led20 = jerry->lead_card(DIAMONDS);
    ASSERT_EQUAL(card_led20, Card(ACE, DIAMONDS));

    Card card_led21 = jerry->lead_card(DIAMONDS);
    ASSERT_EQUAL(card_led21, Card(QUEEN, DIAMONDS));

}

TEST(test_simple_player_play_card) {
    // Rules are that you should play the same suit as
    // the led card
    // Simple player strategy is to play the highest card
    // possible while following suit

    // If you do not have that suit, you may play any card
    // in your hand
    // Simple player strategy is to play the lowest value card
    // possible considering the trump suit and the led suit



    // Testing when person does not have the suit,
    // if they play the lowest possible suit

    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));

    // Bob plays a card
    Card nine_diamonds(NINE, DIAMONDS);
    Card card_played = bob->play_card(
        nine_diamonds,  // Nine of Diamonds is led
        HEARTS    // Trump suit
    ); 

    // Verify the card Bob played
    ASSERT_EQUAL(card_played, Card(NINE, SPADES));
    delete bob;

    // Testing when person does not have the led suit,
    // if they play the lowest possible suit
    // even if they have all trump cards
    Player * patrick = Player_factory("Patrick", "Simple");
    patrick->add_card(Card(NINE, SPADES));
    patrick->add_card(Card(TEN, SPADES));
    patrick->add_card(Card(QUEEN, SPADES));
    patrick->add_card(Card(KING, SPADES));
    patrick->add_card(Card(ACE, SPADES));

    Card card_played5 = patrick->play_card(
        nine_diamonds,      // led suit
        SPADES          // Trump suit
    );

    ASSERT_EQUAL(card_played5, Card(NINE, SPADES));
    delete patrick;


    // Testing if person will play the highest card possible
    // when following suit
    
    Player * obama = Player_factory("Obama", "Simple");
    obama->add_card(Card(NINE, SPADES));
    obama->add_card(Card(TEN, SPADES));
    obama->add_card(Card(QUEEN, SPADES));
    obama->add_card(Card(KING, SPADES));
    obama->add_card(Card(ACE, SPADES));

    Card jack_spades(JACK, SPADES);
    Card card_played2 = bob->play_card(
        jack_spades,        // Jack Spades is led
        HEARTS      // Trump suit
    );

    ASSERT_EQUAL(card_played2, Card(ACE, SPADES));
    delete obama;

    // Testing if the person will play the highest card possible
    // when following suit, even if they have trump card

    Player * tyler = Player_factory("Tyler", "Simple");
    tyler->add_card(Card(NINE, SPADES));
    tyler->add_card(Card(TEN, SPADES));
    tyler->add_card(Card(QUEEN, SPADES));
    tyler->add_card(Card(KING, SPADES));
    tyler->add_card(Card(ACE, HEARTS));

    // Jack of spades is led, but hearts is trump
    // player should play their highest card while following led suit
    // should be king of spades here

    Card card_played3 = tyler->play_card(
        jack_spades,        // Led card
        HEARTS          // Trump suit
    );

    ASSERT_EQUAL(card_played3, Card(KING, SPADES));
    delete tyler;

    // Testing if the person will play the highest card
    // when following suit if they only have trump cards

    Player * john = Player_factory("John", "Simple");
    john->add_card(Card(NINE, SPADES));
    john->add_card(Card(TEN, SPADES));
    john->add_card(Card(QUEEN, SPADES));
    john->add_card(Card(KING, SPADES));
    john->add_card(Card(ACE, SPADES));

    // Jack of spades is led and SPADES is trump
    // highest card while following led suit should be
    // ACE of spades here

    Card card_played4 = john->play_card(
        jack_spades,        // Led card
        SPADES          // Trump suit
    );

    ASSERT_EQUAL(card_played4, Card(ACE, SPADES));
    delete john;

}   

// Add more tests here

TEST_MAIN()
