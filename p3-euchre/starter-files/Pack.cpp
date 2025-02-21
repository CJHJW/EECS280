#include <cassert>
#include <iostream>
#include <array>
#include "Pack.hpp"

// EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on. 
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  // NOTE: The pack is initially full, with no cards dealt.
  Pack::Pack() {
    int i = 0;
    for (int s = SPADES; s <= DIAMONDS; ++s) {
        Suit suit = static_cast<Suit>(s);
        for (int j = NINE; j <= ACE; ++j) {
            Rank rank = static_cast<Rank>(j);
            cards[i++] = Card(rank, suit);
        }
      }  
    reset();    
  }

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  // NOTE: The pack is initially full, with no cards dealt.
  Pack::Pack(std::istream& pack_input) {
    for (int i = 0; i < PACK_SIZE; ++i) {
        pack_input >> cards[i];
    }
    reset();
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one() {
    return cards[next++];
  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset() {
    next = 0;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle() {
    for (int i = 0; i < 7; ++i) {
        std::array<Card, PACK_SIZE> temp = cards;
        for (int j = 0; j < PACK_SIZE; j+=2) {
            cards[j] = temp[j/2+12];
            cards[j+1] = temp[j/2];
        }
    }
    reset();
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const {
    return (next == PACK_SIZE);
  }