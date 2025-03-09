#include "Player.hpp"
#include "Pack.hpp"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Game {
    public:
        Game(string pack_in, string shuffle, string points,
             string player1, string type1,
             string player2, string type2,
             string player3, string type3,
             string player4, string type4) {

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

                // Step0: start the hand
                cout << "Hand " << hand << endl;
                hand ++;

                // Step1: Shuffle if require
                if (shuffle_need) {
                    pack.shuffle();
                }

                // Step2: Deal Cards for each player

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
                Card upcard = pack.deal_one();
                cout << upcard << " turned up" << endl;

                // Step3: Making trump

                Suit order_up_suit;
                int trump_round = 0;
                int attack;

                // 3.1 round 1
                trump_round ++;
                bool any_order_up = false;
                for (int i = 1; i <= 4; ++i) {
                    bool is_dealer = ((dealer+i)%4 == dealer);
                    if(players[(dealer+i)%4]->make_trump(upcard, is_dealer, trump_round, order_up_suit)) {
                        players[dealer]->add_and_discard(upcard);
                        any_order_up = true;
                        cout << *players[(dealer+i)%4] << " orders up "  << order_up_suit << endl;
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
                        bool is_dealer = ((dealer+i)%4 == dealer);
                        if(players[(dealer+i)%4]->make_trump(upcard, is_dealer, trump_round, order_up_suit)) {
                            cout << *players[(dealer+i)%4] << " orders up "  << order_up_suit << endl;
                            attack = (dealer+i)%4;
                            break;
                        }
                        else {
                            cout << *players[(dealer+i)%4] << " passes" << endl;
                        }
                    }
                }

                cout << endl;

                // Step4: Playing five rounds trick
                int round = 1;
                int start = (dealer + 1) % 4;
                vector <int> win_counts = {0, 0, 0, 0};
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
                        play[(start+i)%4] = players[(start+i)%4]->play_card(play[start], order_up_suit);
                        cout << play[(start+i)%4] << " played by " << *players[(start+i)%4] << endl;
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

                // Step5: Find the winning team for this hand
                bool euchred = false;
                bool march = false;
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
                    if (euchred) {
                        group2 += 2;
                        cout << *players[1] << " and " << *players[3] << " win the hand" << endl;
                        cout << "euchred!" << endl;
                    }
                    else if (march) {
                        group1 += 2;
                        cout << *players[0] << " and " << *players[2] << " win the hand" << endl;
                        cout << "march!" << endl;
                    }
                    else {
                        group1 += 1;
                        cout << *players[0] << " and " << *players[2] << " win the hand" << endl;
                    }
                }
                else {
                    if (euchred) {
                        group1 += 2;
                        cout << *players[0] << " and " << *players[2] << " win the hand" << endl;
                        cout << "euchred!" << endl;
                    }
                    else if (march) {
                        group2 += 2;
                        cout << *players[1] << " and " << *players[3] << " win the hand" << endl;
                        cout << "march!" << endl;
                    }
                    else {
                        group2 += 1;
                        cout << *players[1] << " and " << *players[3] << " win the hand" << endl;
                    }
                }
                cout << *players[0] << " and " << *players[2] << " have " << group1 << " points" << endl;
                cout << *players[1] << " and " << *players[3] << " have " << group2 << " points" << endl;
                cout << endl;
            }

            // Step7: When the game is over, print the winners of the game.
            if (group1 > group2) {
                cout << *players[0] << " and " << *players[2] << " win!" << endl;
            }
            else {
                cout << *players[1] << " and " << *players[3] << " win!" << endl;
            }


            // Final Step: Delete players, end game
            for (size_t i = 0; i < players.size(); ++i) {
                delete players[i];
            }
        }

    private:
        std::vector<Player*> players;
        Pack pack;
        bool shuffle_need;
        int win_point;
        int group1;
        int group2;
        int hand;
        int dealer;

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
    // *: ./euchre.exe pack.in noshuffle 1 Adi Simple Barbara Simple Chi-Chih Simple Dabbala Simple 
    for (int i = 0; i < 12; ++i) {
        cout << argv[i] << " ";
    }

    cout << endl;

    Game euchre(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], 
                argv[7], argv[8], argv[9], argv[10], argv[11]);

    euchre.play();

    
};

