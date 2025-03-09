#include "Player.hpp"
#include "Pack.hpp"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Game {
    public:
        // Set up the game: set pack, create players
        Game(string pack_in, string shuffle, string points,
             string player1, string type1,
             string player2, string type2,
             string player3, string type3,
             string player4, string type4);
             
        // Play the game
        void play();

    private:
        std::vector<Player*> players;
        Pack pack;
        bool shuffle;
        int win_point;
        int group1;
        int group2;
        int hand;
        int dealer;
        // ...
        
        void shuffle();
        void deal(/* ... */);
        void make_trump(/* ... */);
        void play_hand(/* ... */);
        // ...

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

    
}

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
                    shuffle = true;
                }
                else {
                    shuffle = false;
                }

                // Step3: Points to win:
                win_point = stoi(points);

                // Step4: Create players
                players[0] = Player_factory(player1, type1);
                players[1] = Player_factory(player2, type2);
                players[2] = Player_factory(player3, type3);
                players[3] = Player_factory(player4, type4);

                // Step5: Initialize each group's point to 0
                group1 = 0;
                group2 = 0;

                //Step6: Initialize hand(# of rounds) and dealer index
                hand = 0;
                dealer = 0;

            }
        void play() {

            // Continue the game until one group reaches the win_point
            while ((group1 < win_point) && (group2 < win_point)) {

                // For each hand:

                // Step0: start the hand
                hand ++;

                // Step1: Shuffle if require
                if (shuffle) {
                    pack.shuffle();
                }

                // Step2: Deal Cards for each player

                // 2.1 Locate the Dealer index
                dealer = (hand - 1) % 4;

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

                // 2.4 Get the upcard‘s suit
                Suit upcard = pack.deal_one().get_suit();


            }


            // Final Step: Delete players, end game
            for (size_t i = 0; i < players.size(); ++i) {
                delete players[i];
            }
        }

    private:
        std::vector<Player*> players;
        Pack pack;
        bool shuffle;
        int win_point;
        int group1;
        int group2;
        int hand;
        int dealer;
        // ...
        
        void shuffle();
        void deal(/* ... */);
        void make_trump(/* ... */);
        void play_hand(/* ... */);
        // ...

};