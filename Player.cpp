//#ifndef PLAYER_H
//#define PLAYER_H
/* Player.h
 *
 * Euchre player interface
 *
 * by Andrew DeOrio
 * awdeorio@umich.edu
 * 2014-12-21
 */


#include "Card.h"
#include "Player.h"
#include <string>
#include <vector>
#include <iostream>


//********************************************************************************
//**************************** HELPER FUNCTIONS **********************************
//********************************************************************************

// SORT HELPER FUNCTION
static void sort_hand(std::vector<Card> handCopy, std::vector<Card> newHand)
{
    // Find the min number in the vector
    Card min = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    int minLoc = 0;
    for(int i = 0; i < handCopy.size(); ++i)
    {
        if(operator<(handCopy.at(i), min))
        {
            min = handCopy.at(i);
            minLoc = i;
        }
    }
    handCopy.erase(handCopy.begin() + minLoc);
    newHand.push_back(min);
}

// RETURNS SAME COLOR SUIT
static std::string same_color_suit(Card upcard)
{
    if(upcard.get_suit() == Card::SUIT_SPADES)
    {
        return Card::SUIT_CLUBS;
    }
    if(upcard.get_suit() == Card::SUIT_HEARTS)
    {
        return Card::SUIT_DIAMONDS;
    }
    if(upcard.get_suit() == Card::SUIT_CLUBS)
    {
        return Card::SUIT_SPADES;
    }
    if(upcard.get_suit() == Card::SUIT_DIAMONDS)
    {
        return Card::SUIT_HEARTS;
    }
    return 0;
}



// CAN SIMPLE PLAYER FOLLOW SUIT?
static bool follows_suit(std::vector<Card> hand, const Card &led_card)
{
    for(int i = 0; i < hand.size(); ++i)
    {
        if(hand.at(i).get_suit() == led_card.get_suit())
        {
            return true;
        }
    }
    return false;
}


// COPY VECTORS (HAND)
static void copy_vec(std::vector<Card> handCopy, std::vector<Card> hand)
{
    for(int i = 0; i < hand.size(); ++i)
    {
        handCopy.at(i) = hand.at(i);
    }
}


// ARE TRUMP FACE CARDS
static bool is_trump_face(const Card card, const Card &upcard)
{
    std::string actualRank = card.get_rank();
    if(Card::RANK_JACK == actualRank || Card::RANK_QUEEN == actualRank || Card::RANK_KING == actualRank || Card::RANK_ACE == actualRank)
    {
        return true;
    }
    if(card.is_left_bower(upcard.get_suit()) || card.is_right_bower(upcard.get_suit()))
    {
        return true;
    }
    return false;
}




//***************************************************************************
//**************************** CLASS HUMAN **********************************
//***************************************************************************


class Human : public Player {

    // VARIABLES PART OF THE CLASS//
    
    std::string name;
    std::vector<Card> hand; //Number of cards in hand
    
public:
    Human(std::string name)
    :name(name) {}
    
//EFFECTS returns player's name
const std::string & get_name() const override
{
    return name;
}

//REQUIRES player has less than MAX_HAND_SIZE cards
//EFFECTS  adds Card c to Player's hand
void add_card(const Card &c) override
{
    if(hand.size() < 5)
    {
        hand.push_back(c);
    }
}
    
//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If Player wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If Player wishes to pass, then do
//  not modify order_up_suit and return false.
bool make_trump(const Card &upcard, bool is_dealer, int round, std::string &order_up_suit) const override
{
// *********** PRINT PLAYER'S HAND IN ASCENDING ORDER *********** //
    // Make a copy of the hand vector
    std::vector<Card> newHand;
    std::vector<Card> handCopy;
    copy_vec(handCopy, hand);
   
    //Sort the copied hand & print it using the copy
    sort_hand(handCopy, newHand);
    
    for(int i = 0; i < newHand.size(); ++i)
    {
        std::cout << "Human player " << name << "'s hand: ["<< i << "] " << newHand.at(i) << "\n";
    }
    
// *********** PROMPT USER TO PASS OR ORDER UP *********** //
    std::string decision;
    std::cout << "Human player " << name << ", please enter a suit, or \"pass\": ";
    std::cin >> decision;

    if(decision == "pass")
    {
        std::cout << name << "passes" << "\n";
        return false;
    }
    else
    {
        order_up_suit = decision;
        std::cout << name << " orders up " << decision << "\n";
        return true;
    }
}
    
    
//REQUIRES Player has at least one card
//EFFECTS  Player adds one card to hand and removes one card from hand.
void add_and_discard(const Card &upcard) override
{
    // *********** PRINT PLAYER'S HAND IN ASCENDING ORDER *********** //
    // Make a copy of the hand vector
    std::vector<Card> newHand;
    std::vector<Card> handCopy;
    copy_vec(handCopy, hand);
        
    //Sort the copied hand & print it using the copy
    sort_hand(handCopy, newHand);
    for(int i = 0; i < newHand.size(); ++i)
    {
        std::cout << "Human player " << name << "'s hand: ["<< i << "] " << newHand.at(i) << "\n";
    }
    std::cout << "Discard upcard: [-1] " << "\n";
    
    // *********** PROMPT THE DEALER TO SELECT A CARD TO DISCARD *********** //
    int decision;
    std::cout << "Human player " << name << ", please select a card to discard: ";
    std::cin >> decision;
    
    //unsort to find the position of the decision card in the unsorted hand
   // unsort_hand(handCopy, newHand, hand);
    // Actually discard the card from the hand
    if(decision != -1)
    {
        for(int act = 0; act < hand.size(); ++act)
        {
            if(newHand.at(decision) == hand.at(act))
            {
                hand.at(act) = upcard;
            }
        }
    }
}

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Leads one Card from Player's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
Card lead_card(const std::string &trump) override
{
    // *********** PRINT PLAYER'S HAND IN ASCENDING ORDER *********** //
    // Make a copy of the hand vector
    std::vector<Card> newHand;
    std::vector<Card> handCopy;
    copy_vec(handCopy, hand);
    
    //Sort the copied hand & print it using the copy
    sort_hand(handCopy, newHand);
    for(int i = 0; i < newHand.size(); ++i)
    {
        std::cout << "Human player " << name << "'s hand: ["<< i << "] " << newHand.at(i) << "\n";
    }
    // *********** PROMPT THE DEALER TO LEAD *********** //
    int decision;
    std::cout << "Human player " << name << ", please select a card: ";
    std::cin >> decision;

    // *********** PRINT THE CARD PLAYED AND DISCARD THE CARD FROM HAND *********** //
    std::cout << newHand.at(decision) << " led by " << name << "\n";
    for(int i = 0; i < hand.size(); ++i)
    {
        if(newHand.at(decision) == hand.at(i))
        {
            hand.erase(hand.begin() + i);
        }
    }
    return newHand.at(decision);
}

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Plays one Card from Player's hand according to their strategy.
//  The card is removed from the player's hand.
Card play_card(const Card &led_card, const std::string &trump) override
{
    // *********** PRINT PLAYER'S HAND IN ASCENDING ORDER *********** //
    // Make a copy of the hand vector
    std::vector<Card> newHand;
    std::vector<Card> handCopy;
    for(int i = 0; i < hand.size(); ++i)
    {
        handCopy.at(i) = hand.at(i);
    }
    
    //Sort the copied hand & print it using the copy
    sort_hand(handCopy, newHand);
    for(int i = 0; i < newHand.size(); ++i)
    {
        std::cout << "Human player " << name << "'s hand: ["<< i << "] " << newHand.at(i) << "\n";
    }
    // *********** PROMPT THE DEALER TO LEAD *********** //
    int decision;
    std::cout << "Human player " << name << ", please select a card: ";
    std::cin >> decision;
    
    // *********** PRINT THE CARD PLAYED AND DISCARD THE CARD FROM HAND *********** //
    std::cout << newHand.at(decision) << " played by " << name << "\n";
    for(int i = 0; i < hand.size(); ++i)
    {
        if(newHand.at(decision) == hand.at(i))
        {
            hand.erase(hand.begin() + i);
        }
    }
    return newHand.at(decision);
}

};




//***************************************************************************
//**************************** CLASS SIMPLE *********************************
//***************************************************************************


class Simple : public Player {
    
    // VARIABLES PART OF THE CLASS//
    
    std::string name;
    std::vector<Card> hand; //Number of cards in hand
    
public:
    Simple(std::string name)
        :name(name) {}
    
//EFFECTS returns player's name
const std::string & get_name() const override
{
    return name;
}
    
//REQUIRES player has less than MAX_HAND_SIZE cards
//EFFECTS  adds Card c to Player's hand
void add_card(const Card &c) override
{
    if(hand.size() < 5)
    {
        hand.push_back(c);
    }
}
    
//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If Player wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If Player wishes to pass, then do
//  not modify order_up_suit and return false.
bool make_trump(const Card &upcard, bool is_dealer, int round, std::string &order_up_suit) const override
{
    // *************** ROUND 1 *************** //
   if(round == 1)
   {
       int countTrump = 0;
       for(int i = 0; i < hand.size(); ++i)
       {
           if(is_trump_face(hand.at(i), upcard))
           {
               ++countTrump;
           }
       }
       if(countTrump >= 2)
       {
           order_up_suit = upcard.get_suit();
           std::cout << name << " orders up " << order_up_suit << "\n";
           return true;
       }
       else
       {
           std::cout << name << " passes " << "\n";
           return false;
       }
   }
    
    // *************** ROUND 2 *************** //
    
    if(round == 2 && is_dealer == true)         //If round 2 & player is dealer (SCREW THE DEALER)
    {
        order_up_suit = same_color_suit(upcard);
        std::cout << name << " orders up " << order_up_suit << "\n";
        return true;
    }
    return false;
    
    if(round == 2 && is_dealer == false)
    {
       int countFace = 0;
       for(int i = 0; i < hand.size(); ++i)
       {
           if(hand.at(i).get_suit() == same_color_suit(upcard) && is_trump_face(hand.at(i), upcard))
           {
               ++countFace;
           }
       }
       if(countFace >= 1)
       {
           order_up_suit = same_color_suit(upcard);
           std::cout << name << " orders up " << order_up_suit << "\n";
           return true;
       }
       else
       {
           std::cout << name << " passes " << "\n";
           return false;
       }
    }
}
    
    
    
//REQUIRES Player has at least one card
//EFFECTS  Player adds one card to hand and removes one card from hand.
void add_and_discard(const Card &upcard) override
{
    // ADD CARD (UPCARD)
    hand.push_back(upcard);
        
    // DISCARD THE MIN CARD IN HAND
    Card min = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    int minLoc = 0;
    for(int i = 0; i < hand.size(); ++i)
    {
        if(Card_less(hand.at(i), min, upcard.get_suit()))
        {
            min = hand.at(i);
            minLoc = i;
        }
    }
    if(minLoc == hand.size())
    {
        hand.pop_back();
    }
    else
    {
        hand.at(minLoc) = upcard;
    }
}
    
//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Leads one Card from Player's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
    
Card lead_card(const std::string &trump) override
{
    // IF ALL CARDS IN HAND ARE TRUMP
    int countTrump = 0;
    for(int i = 0; i < hand.size(); ++i)
    {
        if(hand.at(i).is_trump(trump))
        {
            ++countTrump;
        }
    }
    if(countTrump == hand.size())
    {
        Card max = Card();
        for(int i = 0; i < hand.size(); ++i)
        {
            if(Card_less(max, hand.at(i), trump))
            {
                max = hand.at(i);
            }
        }
        std::cout << max << " led by " << name << "\n";
        return max;
    }
    // IF NOT ALL CARDS IN HAND ARE TRUMP
    else
    {
        Card max = Card();
        for(int i = 0; i < hand.size(); ++i)
        {
            if(!Card_less(hand.at(i), max, trump) && !hand.at(i).is_trump(trump))
            {
                max = hand.at(i);
            }
        }
        std::cout << max << " led by " << name << "\n";
        return max;
    }
}
    
//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Plays one Card from Player's hand according to their strategy.
//  The card is removed from the player's hand.
    
Card play_card(const Card &led_card, const std::string &trump) override
{
    // IF FOLLOWS SUIT (OUTPUT HIGHEST HAND IN SUIT)
    if(follows_suit(hand, led_card))
    {
        Card max = Card();
        for(int i = 0; i < hand.size(); ++i)
        {
            if(Card_less(max, hand.at(i), led_card, trump))
            {
                max = hand.at(i);
            }
        }
        std::cout << max << " played by " << name << "\n";
        return max;
    }
    // IF DOES NOT FOLLOW SUIT (OUTPUT LOWEST HAND)
    else
    {
        Card min = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
        for(int i = 0; i < hand.size(); ++i)
        {
            if(Card_less(hand.at(i), min, trump))
            {
                min = hand.at(i);
            }
        }
        std::cout << min << " played by " << name << "\n";
        return min;
    }
}

};



//*******************************************************************************************
//**************************** NOT PART OF THE TWO CLASSES **********************************
//*******************************************************************************************



//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy)
{
    // We need to check the value of strategy and return the corresponding Simple player type.
    if (strategy == "Simple") {
        return new Simple(name);
    }
    
    // Repeat for each other type of Human player
    if (strategy == "Human") {
        return new Human(name);
    }
    
    // Invalid strategy if we get here
    return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p)
{
    os << p.get_name();
    return os;
}

//#endif

