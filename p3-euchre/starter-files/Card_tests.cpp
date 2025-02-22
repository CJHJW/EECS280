#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_card_suit_and_rank_basic) {
    Card c(ACE, SPADES);
    ASSERT_EQUAL(c.get_rank(), ACE);
    ASSERT_EQUAL(c.get_suit(), SPADES);

    Card c2(NINE, DIAMONDS);
    ASSERT_EQUAL(c2.get_rank(), NINE);
    ASSERT_EQUAL(c2.get_suit(), DIAMONDS);
}

TEST(test_card_suit_with_parameters) {
    
    // Should return the suit of c
    Card c(ACE, SPADES);
    ASSERT_EQUAL(c.get_suit(SPADES), SPADES);

    Card c2(JACK, HEARTS);
    // Should return diamond since c2 is a lower bower = trump
    ASSERT_EQUAL(c2.get_suit(DIAMONDS), DIAMONDS);
    // Should be hearts since c2 is hearts
    ASSERT_EQUAL(c2.get_suit(HEARTS), HEARTS);
    // Although trump is spades, c2 is still hearts
    ASSERT_EQUAL(c2.get_suit(SPADES), HEARTS);

}

TEST(test_card_type)
{
    Card three_spades = Card(THREE, SPADES);
    ASSERT_FALSE(three_spades.is_face_or_ace());
    ASSERT_FALSE(three_spades.is_right_bower(CLUBS));
    ASSERT_FALSE(three_spades.is_left_bower(CLUBS));
    ASSERT_FALSE(three_spades.is_trump(CLUBS));
    
    Card ace_hearts = Card(ACE, HEARTS);
    ASSERT_TRUE(ace_hearts.is_face_or_ace());
    // Not a jack so should be false
    ASSERT_FALSE(ace_hearts.is_right_bower(HEARTS));
    // Not a jack so should be false
    ASSERT_FALSE(ace_hearts.is_left_bower(DIAMONDS));
    // Of the trump suit so should be true
    ASSERT_TRUE(ace_hearts.is_trump(HEARTS));
    // Not of the trump suit so should be false
    ASSERT_FALSE(ace_hearts.is_trump(SPADES));

    Card jack_hearts = Card(JACK, HEARTS);
    ASSERT_TRUE(jack_hearts.is_face_or_ace());
    ASSERT_TRUE(jack_hearts.is_right_bower(HEARTS));
    ASSERT_FALSE(jack_hearts.is_left_bower(HEARTS));
    ASSERT_TRUE(jack_hearts.is_left_bower(DIAMONDS));
    ASSERT_FALSE(jack_hearts.is_right_bower(DIAMONDS));

    // Jack of trump suit so should be true
    ASSERT_TRUE(jack_hearts.is_trump(HEARTS));
    
    // Jack of the same color as trump so true
    ASSERT_TRUE(jack_hearts.is_trump(DIAMONDS));

    ASSERT_FALSE(jack_hearts.is_trump(SPADES));
    ASSERT_FALSE(jack_hearts.is_trump(CLUBS));
}

TEST(test_card_self_comparison) {
    Card three_spades = Card(THREE, SPADES);
    ASSERT_FALSE(three_spades < three_spades);
    ASSERT_TRUE(three_spades <= three_spades);
    ASSERT_FALSE(three_spades > three_spades);
    ASSERT_TRUE(three_spades >= three_spades);
    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_FALSE(three_spades != three_spades);
}

TEST(test_card_to_card_comparison)
{
    Card three_spades = Card(THREE, SPADES);
    Card ace_spades = Card(ACE, SPADES);
    Card ace_hearts = Card(ACE, HEARTS);

    // Comparing 3 of Spades and Ace of Spades
    ASSERT_TRUE(three_spades < ace_spades);
    ASSERT_TRUE(three_spades <= ace_spades);
    ASSERT_FALSE(three_spades > ace_spades);
    ASSERT_FALSE(three_spades >= ace_spades);
    ASSERT_TRUE(ace_spades >= three_spades);
    ASSERT_TRUE(ace_spades > three_spades);
    ASSERT_FALSE(ace_spades == three_spades);
    ASSERT_TRUE(three_spades != ace_spades);

    // Comapring Ace of Spades with Ace of Hearts
    // * note heart is greater than spades
    ASSERT_FALSE(ace_spades > ace_hearts);
    ASSERT_FALSE(ace_spades >= ace_hearts);
    ASSERT_TRUE(ace_spades < ace_hearts);
    ASSERT_TRUE(ace_spades <= ace_hearts);
    ASSERT_FALSE(ace_spades == ace_hearts);
    ASSERT_TRUE(ace_spades != ace_hearts);
    
}

TEST(test_card_extraction_ace_hearts)
{
    istringstream iss("Ace of Hearts");
    Card c;
    iss >> c;
    ASSERT_EQUAL(c, Card(ACE, HEARTS));
}

TEST(test_card_extraction_two_spades)
{
    istringstream iss("Two of Spades");
    Card c;
    iss >> c;
    ASSERT_EQUAL(c, Card(TWO, SPADES));
}

TEST(test_card_extraction_jack_clubs)
{
    istringstream iss("Jack of Clubs");
    Card c;
    iss >> c;
    ASSERT_EQUAL(c, Card(JACK, CLUBS));
}

TEST(test_card_extraction_king_diamonds)
{
    istringstream iss("King of Diamonds");
    Card c;
    iss >> c;
    ASSERT_EQUAL(c, Card(KING, DIAMONDS));
}

TEST(test_card_insertion)
{
    Card three_spades = Card(THREE, SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
}


TEST(test_suit_next)
{
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
}

TEST(test_compare_suit) {
    Card ace_hearts(ACE, HEARTS);
    Card ace_diamonds(ACE, DIAMONDS);
    ASSERT_TRUE(ace_hearts < ace_diamonds);
}

TEST(test_3_param_card_less)
{
    Card three_spades = Card(THREE, SPADES);
    Card five_spades = Card(FIVE, SPADES);
    Card king_diamonds = Card(KING, DIAMONDS);
    Card jack_spades = Card(JACK, SPADES);
    Card jack_clubs = Card(JACK, CLUBS);

    // Testing identical cards
    ASSERT_FALSE(Card_less(three_spades, three_spades, CLUBS));

    // Testing trump vs non-trump suit
    ASSERT_FALSE(Card_less(five_spades, king_diamonds, SPADES));

    // Testing non-trump vs trump suit
    ASSERT_TRUE(Card_less(five_spades, king_diamonds, DIAMONDS));

    // Testing both are trump suits...

    // Testing first param right bower
    ASSERT_FALSE(Card_less(jack_spades, jack_clubs, SPADES));

    // Testing second param right bower
    ASSERT_TRUE(Card_less(jack_spades, jack_clubs, CLUBS));

    // Testing first param left bower and second is lower card
    ASSERT_FALSE(Card_less(jack_clubs, five_spades, SPADES));
    
    // Testing first param is lower card and second is left bower
    ASSERT_TRUE(Card_less(five_spades, jack_clubs, SPADES));

    // Testing both are not bowers but of trump suit
    ASSERT_TRUE(Card_less(three_spades, five_spades, SPADES));
    ASSERT_FALSE(Card_less(five_spades, three_spades, SPADES));


    // Both not trump suits
    ASSERT_TRUE(Card_less(three_spades, five_spades, DIAMONDS));
    ASSERT_FALSE(Card_less(five_spades, three_spades, DIAMONDS));
    ASSERT_TRUE(Card_less(five_spades, king_diamonds, HEARTS));
}


TEST(test_4_param_card_less)
{
    Card three_spades = Card(THREE, SPADES);
    Card five_spades = Card(FIVE, SPADES);
    Card six_spades = Card(SIX, SPADES);
    Card king_diamonds = Card(KING, DIAMONDS);
    Card three_diamonds = Card(THREE, DIAMONDS);
    Card jack_spades = Card(JACK, SPADES);
    Card jack_clubs = Card(JACK, CLUBS);

    // Testing identical Cards of trump
    ASSERT_FALSE(Card_less(three_spades, three_spades, five_spades, SPADES));

    // Testing identical Cards not of trump suit
    ASSERT_FALSE(Card_less(three_spades, three_spades, five_spades, CLUBS));

    // Testing BOTH are trump suits...

    // Testing first param right bower
    ASSERT_FALSE(Card_less(jack_spades, jack_clubs, king_diamonds, SPADES));

    // Testing second param right bower
    ASSERT_TRUE(Card_less(jack_spades, jack_clubs, five_spades, CLUBS));

    // Testing first param left bower and second is lower card
    ASSERT_FALSE(Card_less(jack_clubs, five_spades, king_diamonds, SPADES));
    
    // Testing first param is lower card and second is left bower
    ASSERT_TRUE(Card_less(five_spades, jack_clubs, five_spades, SPADES));

    // Testing both are not bowers but of trump suit
    ASSERT_TRUE(Card_less(three_spades, five_spades,  king_diamonds, SPADES));
    ASSERT_FALSE(Card_less(five_spades, three_spades, king_diamonds, SPADES));

    // NOW Testing NEITHER in trump suits...

    // Both match led suit
    ASSERT_TRUE(Card_less(three_spades, five_spades, six_spades, HEARTS));
    ASSERT_FALSE(Card_less(five_spades, three_spades, six_spades, HEARTS));

    // First does not match led suit, but second does
    ASSERT_TRUE(Card_less(three_spades, king_diamonds, three_diamonds, HEARTS));

    // First does match led suit, but second doesn't
    ASSERT_FALSE(Card_less(three_spades, king_diamonds, five_spades, HEARTS));

    // Neither match led suit or trump suit
    ASSERT_TRUE(Card_less(three_spades, five_spades, king_diamonds, HEARTS));
    ASSERT_FALSE(Card_less(five_spades, three_spades, king_diamonds, HEARTS));

}

TEST_MAIN()
