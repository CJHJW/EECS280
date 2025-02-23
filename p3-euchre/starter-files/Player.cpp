#include "Player.hpp"
#include "cassert"
#include <algorithm>
using namespace std;

class SimplePlayer : public Player {
    private:
        const string name;
        vector<Card> hand;
    public:
        SimplePlayer (const string &name) : name(name) {

        }
        //EFFECTS returns player's name
        const string & get_name() const override {
            return name;
        }
    
        //REQUIRES player has less than MAX_HAND_SIZE cards
        //EFFECTS  adds Card c to Player's hand
        void add_card(const Card &c) override {
            assert(hand.size() < MAX_HAND_SIZE);
            hand.push_back(c);
        }

        //REQUIRES round is 1 or 2
        //MODIFIES order_up_suit
        //EFFECTS If Player wishes to order up a trump suit then return true and
        //  change order_up_suit to desired suit.  If Player wishes to pass, then do
        //  not modify order_up_suit and return false.
        bool make_trump(const Card &upcard, bool is_dealer,
            int round, Suit &order_up_suit) const override {
                assert((round == 1) || (round == 2));
                if (round == 1) {
                    int count = 0;
                    Suit trump = upcard.get_suit();
                    for (int i = 0; i < hand.size(); ++i) {
                        if ((hand[i].is_trump(trump)) && (hand[i].is_face_or_ace())) {
                            count ++;
                        }
                        if (hand[i].is_left_bower(trump)) {
                            count ++;
                        }
                        if (hand[i].is_right_bower(trump)) {
                            count ++;
                        }
                    }
                    if (count >= 2) {
                        order_up_suit = trump;
                        return true;
                    }
                    else {
                        return false;
                    }
                }
                if (round == 2) {
                    int count = 0;
                    Suit trump = Suit_next(upcard.get_suit());
                    for (int i = 0; i < hand.size(); ++i) {
                        if (hand[i].is_trump(trump) && (hand[i].is_face_or_ace())) {
                            count ++;
                        }
                        if (hand[i].is_left_bower(trump)) {
                            count ++;
                        }
                        if (hand[i].is_right_bower(trump)) {
                            count ++;
                        }
                    }
                    if ((is_dealer) || (count >= 1)) {
                        order_up_suit = trump;
                        return true;
                    }
                }
                return false;
            }
    
        //REQUIRES Player has at least one card
        //EFFECTS  Player adds one card to hand and removes one card from hand.
        void add_and_discard(const Card &upcard) override {
            assert(hand.size() >= 1);
            hand.push_back(upcard);
            Suit trump = upcard.get_suit();
            int min_idx = 0;
            Card min = hand[0];
            for (int i = 1; i < hand.size(); ++i) {
                if (!Card_less(min, hand[i], trump)) {
                    min_idx = i;
                    min = hand[min_idx];
                }
            }
            hand.erase(hand.begin()+min_idx);
        }

        //REQUIRES Player has at least one card
        //EFFECTS  Leads one Card from Player's hand according to their strategy
        //  "Lead" means to play the first Card in a trick.  The card
        //  is removed the player's hand.
        Card lead_card(Suit trump) override {
            assert(hand.size() >= 1);
            int max_no_idx = 0;
            int max_yes_idx = 0;
            Card max_no;
            Card max_yes;
            int count_yes = 0;
            for (int i = 0; i < hand.size(); ++i) {
                if (hand[i].is_trump(trump)) {
                    count_yes ++;
                    if (max_yes.get_rank() == TWO) {
                        max_yes_idx = i;
                        max_yes = hand[max_yes_idx];
                    }
                    else if (Card_less(max_yes, hand[i], trump)) {
                        max_yes_idx = i;
                        max_yes = hand[max_yes_idx];
                    }

                }
                else {
                    if (max_no.get_rank() == TWO) {
                        max_no_idx = i;
                        max_no = hand[max_no_idx];
                    }
                    else if (Card_less(max_no, hand[i], trump)) {
                        max_no_idx = i;
                        max_no = hand[max_no_idx];
                    }
                }
            }
            if (count_yes == hand.size()) {
                hand.erase(hand.begin()+max_yes_idx);
                return max_yes;
            }
            else {
                hand.erase(hand.begin()+max_no_idx);
                return max_no;
            }

        }

        //REQUIRES Player has at least one card
        //EFFECTS  Plays one Card from Player's hand according to their strategy.
        //  The card is removed from the player's hand.
        Card play_card(const Card &led_card, Suit trump) override {
            assert(hand.size() >= 1);
            int max_idx = 0;
            int min_idx = 0;
            Card max_card;
            Card min_card;
            int count_led = 0;
            Suit led = led_card.get_suit(trump);
            for (int i = 0; i < hand.size(); ++i) {
                if (hand[i].get_suit(trump)==led) {
                    count_led ++;
                    if (max_card.get_rank() == TWO) {
                        max_idx = i;
                        max_card = hand[max_idx];
                    }
                    else if (Card_less(max_card, hand[i], led_card, trump)) {
                        max_idx = i;
                        max_card = hand[max_idx];
                    }

                }
                else {
                    if (min_card.get_rank() == TWO) {
                        min_idx = i;
                        min_card = hand[min_idx];
                    }
                    else if (!Card_less(min_card, hand[i], led_card, trump)) {
                        min_idx = i;
                        min_card = hand[min_idx];
                    }
                }
            }
            if (count_led != 0) {
                hand.erase(hand.begin()+max_idx);
                return max_card;
            }
            else {
                hand.erase(hand.begin()+min_idx);
                return min_card;
            }
        }
    
};

class HumanPlayer : public Player {
    private:
        const string name;
        vector<Card> hand;

        void print_hand() const {
            for (size_t i=0; i < hand.size(); ++i)
              cout << "Human player " << name << "'s hand: "
                   << "[" << i << "] " << hand[i] << "\n";
        }


    public:
        HumanPlayer (const string &name) : name(name) {

        }
        //EFFECTS returns player's name
        const string & get_name() const override {
            return name;
        }
    
        //REQUIRES player has less than MAX_HAND_SIZE cards
        //EFFECTS  adds Card c to Player's hand
        void add_card(const Card &c) override {
            assert(hand.size() < MAX_HAND_SIZE);
            hand.push_back(c);
        }


        bool make_trump(const Card &upcard, bool is_dealer,
            int round, Suit &order_up_suit) const override {
            print_hand();
            cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
            string decision;
            cin >> decision;
            if (decision != "pass") {
                Suit ordered_up = string_to_suit(decision);
                cout << name << " orders up " << ordered_up << endl;
                order_up_suit = ordered_up;
                return true;
            }
            else {
                cout << name << " passes\n";
                return false;
            }
        }
    
        //REQUIRES Player has at least one card
        //EFFECTS  Player adds one card to hand and removes one card from hand.
        void add_and_discard(const Card &upcard) override {
            assert(hand.size() >= 1);
            print_hand();
            cout << "Discard upcard: [-1]\n";
            cout << "Human player " << name << ", please select a card to discard:\n";
            int decision;
            cin >> decision; 
            if (decision != -1) {
                hand.erase(hand.begin()+decision);
                hand.push_back(upcard);
                sort(hand.begin(), hand.end());
            } 
        }

        //REQUIRES Player has at least one card
        //EFFECTS  Leads one Card from Player's hand according to their strategy
        //  "Lead" means to play the first Card in a trick.  The card
        //  is removed the player's hand.
        Card lead_card(Suit trump) override {
            assert(hand.size() >= 1);
            print_hand();
            cout << "Human player " << name << ", please select a card:\n";
            int decision;
            cin >> decision;
            Card play = hand[decision];
            cout << play << " led by " << name << endl;
            hand.erase(hand.begin()+decision);
            return play;
        }

        //REQUIRES Player has at least one card
        //EFFECTS  Plays one Card from Player's hand according to their strategy.
        //  The card is removed from the player's hand.
        Card play_card(const Card &led_card, Suit trump) override {
            assert(hand.size() >= 1);
            assert(hand.size() >= 1);
            print_hand();
            cout << "Human player " << name << ", please select a card:\n";
            int decision;
            cin >> decision;
            Card play = hand[decision];
            cout << play << " led by " << name << endl;
            hand.erase(hand.begin()+decision);
            return play;
        }
    
};

Player * Player_factory(const std::string &name, const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  // Repeat for each other type of Player
  if (strategy == "Human") {
    return new HumanPlayer(name);
  }
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}

