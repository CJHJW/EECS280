#include "Player.hpp"
#include "Pack.hpp"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Game {
    public:
        Game(vector<string> arg_value) {

                // argv[1], argv[2]...
                // Pointer, size 
                // for 
                // vector/array: argv[1] - argv[11]
                
                string pack_in = arg_value[0];
                string shuffle = arg_value[1];
                string points = arg_value[2];
                string player1 = arg_value[3];
                string type1 = arg_value[4];
                string player2 = arg_value[5];
                string type2 = arg_value[6];
                string player3 = arg_value[7];
                string type3 = arg_value[8];
                string player4 = arg_value[9];
                string type4 = arg_value[10];



                // Step1: Set the pack
                ifstream pack_input(pack_in);
                pack = Pack(pack_input);
                
                // Step2: Whether shuffle
                if (shuffle == "shuffle") {
                    shuffle_need = true;
                }
                else {
                    shuffle_need = false;
                }

                // Step3: Points to win:
                win_point = stoi(points);

                // Step4: Create players
                players.push_back(Player_factory(player1, type1));
                players.push_back(Player_factory(player2, type2));
                players.push_back(Player_factory(player3, type3));
                players.push_back(Player_factory(player4, type4));

                // Step5: Initialize each group's point to 0
                group1 = 0;
                group2 = 0;

                // Step6: Initialize hand(# of rounds) and dealer index
                hand = 0;
                dealer = 0;

            }
        void play() {

            // Continue the game until one group reaches the win_point
            while ((group1 < win_point) && (group2 < win_point)) {

                // For each hand:
                pack.reset();

                // Step0: start the hand
                cout << "Hand " << hand << endl;
                hand ++;

                // Step1: Shuffle if require
                if (shuffle_need) {
                    pack.shuffle();
                }

                // Step2: Deal Cards for each player
                deal_cards();

                // Step3: Making trump
                making_trump();
                
                // Step4: Playing five rounds trick
                play_round();

                // Step5: Find the winning team for this hand
                find_win();
            }

            // Step6: When the game is over, print the winners of the game.
            print_winner();


            // Final Step: Delete players, end game
            for (size_t i = 0; i < players.size(); ++i) {
                delete players[i];
            }
        }

    private:
        std::vector<Player*> players;
        Pack pack;
        Card upcard;
        Suit order_up_suit;
        vector <int> win_counts;
        bool euchred;
        bool march;
        bool shuffle_need;
        int win_point;
        int group1;
        int group2;
        int hand;
        int dealer;
        int attack;

        // Step2: Dealing cards
        void deal_cards() {
            
            // 2.1 Locate the Dealer index
            dealer = (hand - 1) % 4;
            cout << *players[dealer] << " deals" << endl;

            // 2.2 Deal by 3-2-3-2
             for (int i = 1; i <= 4; ++i) {
                if (i % 2 == 1) {
                    for (int j = 0; j < 3; ++j) {
                        players[(dealer+i)%4]->add_card(pack.deal_one());
                    }
                }
                else {
                    for (int j = 0; j < 2; ++j) {
                        players[(dealer+i)%4]->add_card(pack.deal_one());
                    }
                }
            }

            // 2.3 Deal by 2-3-2-3
            for (int i = 1; i <= 4; ++i) {
                if (i % 2 == 1) {
                    for (int j = 0; j < 2; ++j) {
                        players[(dealer+i)%4]->add_card(pack.deal_one());
                    }
                }
                else {
                    for (int j = 0; j < 3; ++j) {
                        players[(dealer+i)%4]->add_card(pack.deal_one());
                    }
                }
            }

            // 2.4 Get the upcard
            upcard = pack.deal_one();
            cout << upcard << " turned up" << endl;
        }

        // Step3: Making trump
        void making_trump() {
            
            int trump_round = 0;

            // 3.1 round 1
            trump_round ++;
            bool any_order_up = false;
            for (int i = 1; i <= 4; ++i) {
                bool is_dealer = ((dealer+i)%4 == dealer);
                int t = (dealer+i)%4;
                bool made_trump = 
                players[t]->make_trump(upcard, is_dealer, trump_round, order_up_suit);
                if (made_trump) {
                    any_order_up = true;
                    cout << *players[t] << " orders up "  << order_up_suit << endl;
                    players[dealer]->add_and_discard(upcard);
                    attack = (dealer+i)%4;
                    break;
                }
                else {
                    cout << *players[(dealer+i)%4] << " passes" << endl;
                }
            }

            // 3.2 round 2
            if (!any_order_up) {
                trump_round ++;
                for (int i = 1; i <= 4; ++i) {
                    bool is_dlr = ((dealer+i)%4 == dealer);
                    int t = (dealer+i)%4;
                    bool made_trump = 
                    players[t]->make_trump(upcard, is_dlr, trump_round, order_up_suit);
                    if(made_trump) {
                        cout << *players[(dealer+i)%4] 
                            << " orders up "  << order_up_suit << endl;
                        attack = (dealer+i)%4;
                        break;
                    }
                    else {
                        cout << *players[(dealer+i)%4] << " passes" << endl;
                    }
                    }
                }

                cout << endl;
        }
        
        // Step4: Playing 5 rounds
        void play_round() {
            int round = 1;
            int start = (dealer + 1) % 4;
            win_counts = {0, 0, 0, 0};
            vector<Card> play(4);
            while (round <= 5) {
             /* 
                4.1: 
                Player to the dealer's left leads a card in the first round
                Player who won the previous trick leads a card in other round
            */
            play[start] = players[start]->lead_card(order_up_suit);
            cout << play[start] << " led by " << *players[start] << endl;
            // 4.2: Three players play cards
            for (int i = 1; i <= 3; ++i) {
                play[(start+i)%4] = 
                    players[(start+i)%4]->play_card(play[start], order_up_suit);
                
                cout << play[(start+i)%4] << " played by " 
                     << *players[(start+i)%4] << endl;
            }
            // 4.3: Find the player take this trick
                Card max_card = play[0];
                int max_index = 0;
                for (int i = 1; i < 4; ++i) {
                    if (Card_less(max_card, play[i], play[start], order_up_suit)) {
                        max_index = i;
                        max_card = play[i];
                    }
                }
                cout << *players[max_index] << " takes the trick" << endl << endl;
                // 4.4: Winner gets one win
                win_counts[max_index] += 1;
                start = max_index;
                round ++;
            }
        }

        // Step5: Find win
        void find_win() {
            euchred = false;
            march = false;
            int attack_win = win_counts[attack] + win_counts[(attack+2)%4];
            if (attack_win >= 3) {
                if (attack_win == 5) {
                    march = true;
                }
            }
            else {
                euchred = true;
            }
            if (attack % 2 == 0) {
                attack_from_group1();
            }
            else {
                attack_from_group2();
            }
            cout << *players[0] << " and " << *players[2] 
                 << " have " << group1 << " points" << endl;
            cout << *players[1] << " and " << *players[3] 
                 << " have " << group2 << " points" << endl;
            cout << endl;
        }

        void attack_from_group1() {
            if (euchred) {
                group2 += 2;
                cout << *players[1] << " and " 
                     << *players[3] << " win the hand" << endl;
                
                cout << "euchred!" << endl;
            }
            else if (march) {
                group1 += 2;
                cout << *players[0] << " and " 
                     << *players[2] << " win the hand" << endl;
                cout << "march!" << endl;
            }
            else {
                group1 += 1;
                cout << *players[0] << " and " 
                     << *players[2] << " win the hand" << endl;
            }
        }

        void attack_from_group2() {
            if (euchred) {
                group1 += 2;
                cout << *players[0] << " and " 
                     << *players[2] << " win the hand" << endl;
                cout << "euchred!" << endl;
            }
            else if (march) {
                group2 += 2;
                cout << *players[1] << " and " 
                     << *players[3] << " win the hand" << endl;
                cout << "march!" << endl;
            }
            else {
                group2 += 1;
                cout << *players[1] << " and " 
                     << *players[3] << " win the hand" << endl;
            }
        }

        // Step6: Print winner of game
        void print_winner() {
            if (group1 > group2) {
                cout << *players[0] << " and " 
                     << *players[2] << " win!" << endl;
            }
            else {
                cout << *players[1] << " and " 
                     << *players[3] << " win!" << endl;
            }
        }
};

int main(int argc, char *argv[]) {

    // Should be true if argc is 12
    bool correct_arg_count = (argc == 12);


    if(!correct_arg_count){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;

        return 1;
    };

    // If correct arg count is here, let's perform the other checks

    // Checks if points to win is between 1 and 100 inclusive
    int points_to_win = stoi(argv[3]);
    bool correct_points_to_win = (1 <= points_to_win && points_to_win <= 100);

    // Checks if the shuffle argument passed is valid
    string shuffle_argument = argv[2];
    bool correct_shuffle_arg = (shuffle_argument == "shuffle" || 
                                shuffle_argument == "noshuffle");

    // Checks if the types of player 0, 1, 2, 3 are valid (Simple or Human)
    // [5 & 7 & 9 & 11] 
    string player_type_arg;
    bool correct_player_type_arg = true;

    for (int i = 5; i <= 11; i += 2)
    {
        player_type_arg = argv[i];

        if (player_type_arg != "Simple" && player_type_arg != "Human")
        {
            correct_player_type_arg = false;
        }
    }

    if (!correct_points_to_win || !correct_shuffle_arg || !correct_player_type_arg)
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;

        return 1;

    }

    // Check if the input file could be opened 

    // ifstream inFile = ifstream(argv[1]);
    ifstream inFile(argv[1]);
    if (!inFile.is_open())
    {
        cout << "Error opening " << argv[1] << endl;

        return 1;
    }

    // Print the executable and all arguments on the first line
    for (int i = 0; i < 12; ++i) {
        cout << argv[i] << " ";
    }

    cout << endl;

    vector <string> arg_value;
    for (int i = 1; i < 12; ++i) {
        arg_value.push_back(argv[i]);
    }

    // Game euchre(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], 
    //             argv[7], argv[8], argv[9], argv[10], argv[11]);

    Game euchre(arg_value);
    euchre.play();
};


