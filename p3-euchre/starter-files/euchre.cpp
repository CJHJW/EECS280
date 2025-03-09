#include "Player.hpp"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

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
    bool correct_shuffle_arg = (shuffle_argument == "shuffle" || shuffle_argument == "noshuffle");

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