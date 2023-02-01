//#ifndef PLAYER_H
//#define PLAYER_H
/* Euchre
 *
 * Euchre player interface
 *
 * by Anna San Bartolome
 * annasbv@umich.edu
 * 2-18-2018
 */


#include "Card.h"
#include "Player.h"
#include "Pack.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


//********************************************************************************
//**************************** HELPER FUNCTIONS **********************************
//********************************************************************************

bool check_strategy(char* argv[])
{
    std::string first = argv[5];
    std::string second = argv[7];
    std::string third = argv[9];
    std::string fourth = argv[11];
    
    if(first != "Human" && first != "Simple")
    {
        return false;
    }
    if(second != "Human" && second != "Simple")
    {
        return false;
    }
    if(third != "Human" && third != "Simple")
    {
        return false;
    }
    if(fourth != "Human" && fourth != "Simple")
    {
        return false;
    }
    return true;
}




//********************************************************************************
//******************************* GAME CLASS *************************************
//********************************************************************************


class Game
{
    private:
        // IMPORTANT variables from main
        std::vector<Player *> players;
        Pack pack_of_cards;
        std::string shuffle_noshuffle;
        int maxPoints;
    
        // Cards
        Card upcard;
        std::string order_up_suit;
        Card ledCard;
    
        //Different player vectors
        std::vector<Player *> players_w_dealer;
        std::vector<Player *> players_for_tricks;
    
        //Score taking
        int highestScore;
        int points;
        int pointsA;
        int pointsB;
        int indexWin;

        int hand_num;
        int tricks_num;
    
        int numtricksA;
        int numtricksB;

        int dealerIndex;
        int ordered_up_player;
    
    
    public:
    
//Initialize member variables : players, and a pack of cards
    Game(std::istream& packfile, std::string argument2, int argument3, std::string name0, std::string strategy0, std::string name1, std::string strategy1, std::string name2, std::string strategy2, std::string name3, std::string strategy3)
{
    // Initialize the players with player factory
    Player * player0 = Player_factory(name0, strategy0);
    Player * player1 = Player_factory(name1, strategy1);
    Player * player2 = Player_factory(name2, strategy2);
    Player * player3 = Player_factory(name3, strategy3);
    
    std::vector<Player *> players;
    players.push_back(player0);
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);
    
    // Initialize the pack of cards
    pack_of_cards = Pack(packfile);
    
    // Initialize whether in the argument there was shuffle or noshuffle
    std::string shuffle_noshuffle = argument2;
    
    // Initialize the number of points starting with
    maxPoints = argument3;
    
    // Initialize the amount of point for teamA and teamB
    highestScore = 0;
    points = 0;
    pointsA = 0;
    pointsB = 0;
    indexWin = 3;

    hand_num = 0;
    tricks_num = 0;
    
    numtricksA = 0;
    numtricksB = 0;
    
    dealerIndex = 0;
    ordered_up_player = 0;
}

    
// FUNCTION 1
// Shuffles pack
void pack_shuffle()
{
    if(shuffle_noshuffle == "Shuffle")
    {
        pack_of_cards.shuffle();
    }
}

    
// FUNCTION 2
void add_hand()
{
    hand_num = hand_num + 1;
}
    
// FUNCTION 3
// Sorts the first player vector and considers the dealer. The dealer will now be placed in the last index of the
// vector to allow the make_trump function to read the players in order.
void sort_player_vector()
{
    if(dealerIndex == 0)
    {
        players_w_dealer.at(0) = players.at(1);
        players_w_dealer.at(1) = players.at(2);
        players_w_dealer.at(2) = players.at(3);
        players_w_dealer.at(3) = players.at(0);
    }
    if(dealerIndex == 1)
    {
        players_w_dealer.at(0) = players.at(2);
        players_w_dealer.at(1) = players.at(3);
        players_w_dealer.at(2) = players.at(0);
        players_w_dealer.at(3) = players.at(1);
    }
    if(dealerIndex == 2)
    {
        players_w_dealer.at(0) = players.at(3);
        players_w_dealer.at(1) = players.at(0);
        players_w_dealer.at(2) = players.at(1);
        players_w_dealer.at(3) = players.at(2);
    }
    if(dealerIndex == 3)
    {
        players_w_dealer.at(0) = players.at(0);
        players_w_dealer.at(1) = players.at(1);
        players_w_dealer.at(2) = players.at(2);
        players_w_dealer.at(3) = players.at(3);
    }
}

// FUNCTION 4
// Sorts the second player vector (players_w_dealer) and considers the player that ordered up. The player that ordered up will now be placed in the last index of the vector to allow the make_play function to read the players in order in a much easier way.
void sort_player_vector_tricks()
{
    if(ordered_up_player == 0)
    {
        players_for_tricks.at(0) = players_w_dealer.at(1);
        players_for_tricks.at(1) = players_w_dealer.at(2);
        players_for_tricks.at(2) = players_w_dealer.at(3);
        players_for_tricks.at(3) = players_w_dealer.at(0);
    }
    if(ordered_up_player == 1)
    {
        players_for_tricks.at(0) = players_w_dealer.at(2);
        players_for_tricks.at(1) = players_w_dealer.at(3);
        players_for_tricks.at(2) = players_w_dealer.at(0);
        players_for_tricks.at(3) = players_w_dealer.at(1);
    }
    if(ordered_up_player == 2)
    {
        players_for_tricks.at(0) = players_w_dealer.at(3);
        players_for_tricks.at(1) = players_w_dealer.at(0);
        players_for_tricks.at(2) = players_w_dealer.at(1);
        players_for_tricks.at(3) = players_w_dealer.at(2);
    }
    if(ordered_up_player == 3)
    {
        players_for_tricks.at(0) = players_w_dealer.at(0);
        players_for_tricks.at(1) = players_w_dealer.at(1);
        players_for_tricks.at(2) = players_w_dealer.at(2);
        players_for_tricks.at(3) = players_w_dealer.at(3);
    }
}

    
    
// FUNCTION 5
// Dealer is always considered to be player0
void distribute_cards() //std::vector<Player *> players, Pack pack_of_cards
{
    int deck = 0;
    while(deck < 24)
    {
        //DISTRIBUTING FOR A FIRST TIME
        for(int times = 0; times < 3; ++times)
        {
            players.at(1)->add_card(pack_of_cards.deal_one());
            ++deck;
        }
        for(int times = 0; times < 2; ++times)
        {
            players.at(2)->add_card(pack_of_cards.deal_one());
            ++deck;
        }
        for(int times = 0; times < 3; ++times)
        {
            players.at(3)->add_card(pack_of_cards.deal_one());
            ++deck;
        }
        for(int times = 0; times < 2; ++times)
        {
            players.at(0)->add_card(pack_of_cards.deal_one());
            ++deck;
        }
        
        //DISTRIBUTING FOR A SECOND TIME
        for(int times = 0; times < 2; ++times)
        {
            players.at(1)->add_card(pack_of_cards.deal_one());
            ++deck;
        }
        for(int times = 0; times < 3; ++times)
        {
            players.at(2)->add_card(pack_of_cards.deal_one());
            ++deck;
        }
        for(int times = 0; times < 2; ++times)
        {
            players.at(3)->add_card(pack_of_cards.deal_one());
            ++deck;
        }
        for(int times = 0; times < 3; ++times)
        {
            players.at(0)->add_card(pack_of_cards.deal_one());
            ++deck;
        }
    }
}
    
    
// FUNCTION 6
// Returns the upcard and outputs it to the terminal
void upcard_is() //std::vector<Player *> players, int hand_num, Pack pack_of_cards
{
    std::cout << "Hand " <<  hand_num << "\n";
    
    if(hand_num % 4 == 0)
    {
        std::cout << players.at(0)->get_name() << " deals" << "\n";
        upcard = pack_of_cards.deal_one();
        std::cout << upcard << " turned up" << "\n";
    }
    else if(hand_num % 4 == 1)
    {
        std::cout << players.at(1)->get_name() << " deals" << "\n";
        upcard = pack_of_cards.deal_one();
        std::cout << upcard << " turned up" << "\n";
    }
    else if(hand_num % 4 == 2)
    {
        std::cout << players.at(2)->get_name() << " deals" << "\n";
        upcard = pack_of_cards.deal_one();
        std::cout << upcard << " turned up" << "\n";
    }
    else //(hand_num % 4 == 3)
    {
        std::cout << players.at(3)->get_name() << " deals" << "\n";
        upcard = pack_of_cards.deal_one();
        std::cout << upcard << " turned up" << "\n";
    }
    
}
    
// FUNCTION 7
// Return the index of the dealer from "players" vector
void find_dealer_index()//std::vector<Player *> players, int hand_num, Pack pack_of_cards, std::vector<Player *> players_w_dealer, int dealerIndex
{
    if(hand_num % 4 == 0)
    {
        dealerIndex = 0;
        sort_player_vector();
    }
    else if(hand_num % 4 == 1)
    {
        dealerIndex = 1;
        sort_player_vector();
    }
    else if(hand_num % 4 == 2)
    {
        dealerIndex = 2;
        sort_player_vector();
    }
    else //(hand_num % 4 == 3)
    {
        dealerIndex = 3;
        sort_player_vector();
    }
}
    
    
    
// FUNCTION 8 (MAKE TRUMP)
// player that ordered up in the vector "players_w_dealer"
void all_make_trump() //Card &upcard, int dealerIndex, std::vector<Player *> players_w_dealer, std::string &order_up_suit
{
    bool control;
    for(int round = 0; round < 2; ++round)
    {
        for(int player = 0; player < players_w_dealer.size(); ++player)
        {
            //IF PLAYER IS DEALER
            if(player == players_w_dealer.size() - 1)
            {
                control = players_w_dealer.at(player)->make_trump(upcard, true, round, order_up_suit);
                if(control == true && round == 0)
                {
                    players_w_dealer.at(3)->add_and_discard(upcard);
                    ordered_up_player = player;
                }
            }
        
            //IF PLAYER IS NOT DEALER
            else
            {
                control = players_w_dealer.at(player)->make_trump(upcard, true, round, order_up_suit);
                if(control == true && round == 0)
                {
                    players_w_dealer.at(3)->add_and_discard(upcard);
                    ordered_up_player = player;
                }
            }
        }
    }
}
    
    
// FUNCTION 9
void lead_card_trick()
{
   ledCard = players_for_tricks.at(3)->lead_card(order_up_suit);
}

// FUNCTION 10 (output winner)
void who_won_trick()
{
    sort_player_vector_tricks();
    Card played_card;
    //int indexWin = 3; // the position of the winner of the trick
    for(int trick = 0; trick < 5; ++trick)
    {
        lead_card_trick();
        for(int playerPos = 0; playerPos < 3; ++playerPos)
        {
            played_card = players_for_tricks.at(playerPos)->play_card(ledCard, order_up_suit);
            if(played_card > ledCard)
            {
                ledCard = played_card;
                indexWin = playerPos;
            }
        }
        // Winner of the trick  ******POSSIBLE ERRORS HERE PLEASE CHECK HERE**********
        std::cout << players_for_tricks.at(indexWin)->get_name() << " takes the trick" << "\n";
        // ******************** KEEP TRACK OF POINTS ******************** //
        if(players_for_tricks.at(indexWin)->get_name() == players.at(0)->get_name() || players_for_tricks.at(indexWin)->get_name() == players.at(2)->get_name())
        {
            ++numtricksA;
        }
        if(players_for_tricks.at(indexWin)->get_name() == players.at(1)->get_name() || players_for_tricks.at(indexWin)->get_name() == players.at(3)->get_name())
        {
            ++numtricksB;
        }
        dealerIndex = indexWin;
        sort_player_vector_tricks();
    }
}
    
    
// FUNCTION 11
void highest_amount_of_tricks()
{
    if(numtricksA > numtricksB)
    {
        std::cout << players.at(0)->get_name() << " and " << players.at(2)->get_name() << " win the hand " << "\n";
        highestScore = numtricksA;
    }
    else
    {
        std::cout << players.at(1)->get_name() << " and " << players.at(3)->get_name() << " win the hand " << "\n";
        highestScore = numtricksB;
    }
}
   
    
// FUNCTION 12
void points_tracker()
{
    highest_amount_of_tricks();
    
    // ***** UPDATE POINTS FOR EACH TEAM MEMBER ***** //
    update_points();
    if(players_for_tricks.at(indexWin)->get_name() == players.at(0)->get_name() || players_for_tricks.at(indexWin)->get_name() == players.at(2)->get_name())
    {
        pointsA = points;
    }
    if(players_for_tricks.at(indexWin)->get_name() == players.at(1)->get_name() || players_for_tricks.at(indexWin)->get_name() == players.at(3)->get_name())
    {
        pointsB = points;
    }
    
    //Output the points for each team
    std::cout << players.at(0)->get_name() << " and " << players.at(2)->get_name() << " have " << pointsA << " points " << "\n";
    std::cout << players.at(1)->get_name() << " and " << players.at(3)->get_name() << " have " << pointsB << " points " << "\n";
}

// FUNCTION 13
void update_points()
{
    // IF TRICK WINNERS ORDERED UP
    if(players_for_tricks.at(indexWin)->get_name() == players_for_tricks.at(3)->get_name())
    {
        if(highestScore == 3 || highestScore == 4)
        {
            points = points + 1;
        }
        if(highestScore == 5)
        {
            points = points + 2;
            std::cout << "march!" << "\n";
        }
    }
   
    // IF TRICK WINNERS DID NOT ORDER UP
    if(players_for_tricks.at(indexWin)->get_name() != players_for_tricks.at(3)->get_name())
    {
        if(highestScore == 3 || highestScore == 4 || highestScore == 5)
        {
            points = points + 2;
            std::cout << "euchred!" << "\n";
        }
    }
}
    
    
// FUNCTION 14
int substitute_pointsA()
{
    return pointsA;
}
    
int substitute_pointsB()
{
    return pointsB;
}


// FUNCTION 15
void finally(int pointsA_TEAM, int pointsB_TEAM)
{
    if(pointsA_TEAM == maxPoints)
    {
        std::cout << players.at(0)->get_name() << " and " << players.at(2)->get_name() << " win! " << "\n";
    }
    if(pointsB_TEAM == maxPoints)
    {
        std::cout << players.at(1)->get_name() << " and " << players.at(3)->get_name() << " win! " << "\n";
    }
}
    
// FUNCTION 16
void reset_pack()
{
    pack_of_cards.reset();
}

    
// FUNCTION 17
void erase_vectors()
{
    for(int i = 0; i < players.size(); ++i)
    {
        players_w_dealer.pop_back();
        players_for_tricks.pop_back();
    }
}
    
// FUNCTION 18
void delete_players()
{
    for (int i = 0; i < (int)players.size(); ++i) {
        delete players[i];
    }
    for (int i = 0; i < (int)players_w_dealer.size(); ++i) {
        delete players_w_dealer[i];
    }
    for (int i = 0; i < (int)players_for_tricks.size(); ++i) {
        delete players_for_tricks[i];
    }
}
};
//INT MAIN FUNCTION

int main(int argc, char* argv[])
{
    //****************** VARIABLES **********************//
        std::string argument2 = argv[2];
        int argument3 = atoi(argv[3]);

        std::string name0 = argv[4];
        std::string strategy0 = argv[5];
        std::string name1 = argv[6];
        std::string strategy1 = argv[7];
        std::string name2 = argv[8];
        std::string strategy2 = argv[9];
        std::string name3 = argv[10];
        std::string strategy3 = argv[11];

        int pointsA_TEAM = 0;
        int pointsB_TEAM = 0;
    //**************************************************//
    
    //Check for any argument errors
    if(argc != 12 || argument3 < 1 || argument3 > 100 || (argument2 != "shuffle" && argument2 != "noshuffle") || check_strategy(argv) == false)
    {
        std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << std::endl;
        return -1;
    }
    
    // Check to see that the pack file opens
    std::ifstream infile(argv[1]);
    if(!infile.is_open())
    {
        std::cout << "Error opening " << argv[1] << std::endl;
        return -1;
    }
    
    //INITIALIZE GAME
    Game euchre = Game(infile, argument2, argument3, name0, strategy0, name1, strategy1, name2, strategy2, name3, strategy3);
    
    //*** BEGIN GAME ***//
    while(pointsA_TEAM <= argument3 || pointsB_TEAM <= argument3)
    {
        // Initialize the pack of cards
        euchre.pack_shuffle();
        
        //Distribute cards to each player
        euchre.distribute_cards();
        
        //Find the dealer index in the vector and set new vector considering the dealer (makes things easier)
        euchre.find_dealer_index();
        
        //Find the dealer and output their name along with the upcard
        euchre.upcard_is();
        
        // MAKE TRUMP (HAVE TWO ROUNDS TO MAKE TRUMP)
        euchre.all_make_trump();
        
        //Return the vector of player such that the one who ordered up is last index and so on...
        //euchre.sort_player_vector_tricks();
        
        //Play 5 tricks (each player puts down a card and then highest card wins the trick)
        euchre.who_won_trick();
        
        //Update points for each team
        pointsA_TEAM = euchre.substitute_pointsA();
        pointsB_TEAM = euchre.substitute_pointsB();
        
        //After 5 tricks, the hand number increases
        euchre.add_hand();
        euchre.reset_pack();
        euchre.erase_vectors();
    }
    euchre.finally(pointsA_TEAM, pointsB_TEAM);
    euchre.delete_players();

    infile.close();
    return 0;
}
