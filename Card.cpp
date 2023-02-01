//#ifndef CARD_H
//#define CARD_H

#include <iostream>
#include <string>
#include "Card.h"


//EFFECTS Initializes Card to the Two of Spades
Card::Card()
    :rank(RANK_TWO), suit(SUIT_SPADES) {}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string &rank_in, const std::string &suit_in)
    :rank(rank_in), suit(suit_in) {}

//EFFECTS Returns the rank
std::string Card::get_rank() const
{
    return rank;
}
//EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const
{
    return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const
{
    std::string actualSuit = get_suit();
    if(is_trump(trump) == true)
    {
        return trump;
    }
    if(is_trump(trump) == false)
    {
        return actualSuit;
    }
    return 0;
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const
{
    std::string actualRank = get_rank();
    if(RANK_JACK == actualRank || RANK_QUEEN == actualRank || RANK_KING == actualRank || RANK_ACE == actualRank)
    {
        return true;
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const
{
    std::string actualSuit = get_suit();
    std::string actualRank = get_rank();
    
    if(actualSuit == trump && actualRank == Card::RANK_JACK)
    {
        return true;
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const
{
    std::string actualSuit = get_suit();
    std::string actualRank = get_rank();
    
    if(actualRank == Card::RANK_JACK)
    {
        if(Card::SUIT_SPADES == trump && Card::SUIT_CLUBS == actualSuit)
        {
            return true;
        }
        if(Card::SUIT_HEARTS == trump && Card::SUIT_DIAMONDS == actualSuit)
        {
            return true;
        }
        if(Card::SUIT_CLUBS == trump && Card::SUIT_SPADES == actualSuit)
        {
            return true;
        }
        if(Card::SUIT_DIAMONDS == trump && Card::SUIT_HEARTS == actualSuit)
        {
            return true;
        }
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const
{
    std::string actualSuit = get_suit();
    if(actualSuit == trump)
    {
        return true;
    }
    if(is_left_bower(trump) == true)
    {
        return true;
    }
    return false;
}




//***************************************************************************
//************************ NON-CLASS FUNCTIONS ******************************
//***************************************************************************


//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs)
{
    int LS, RS, RR, LR;
    
//RANK COMPARISONS
    for(int r = 0; r < NUM_RANKS; ++r)
    {
        if(RANK_NAMES_BY_WEIGHT[r] == lhs.get_rank())
        {
            LR = r;
        }
        if(RANK_NAMES_BY_WEIGHT[r] == rhs.get_rank())
        {
            RR = r;
        }
    }

//SUIT COMPARISONS
    for(int s = 0; s < NUM_SUITS; ++s)
    {
        if(SUIT_NAMES_BY_WEIGHT[s] == lhs.get_suit())
        {
            LS = s;
        }
        if(SUIT_NAMES_BY_WEIGHT[s] == rhs.get_suit())
        {
            RS = s;
        }
    }

    
//RESULT
    if(LR < RR)
    {
        return true;
    }
    else if(LR == RR && LS < RS)
    {
        return true;
    }
    else
    {
        return false;
    }
}



//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs)
{
    int LS, RS, RR, LR;
    
    //SUIT COMPARISONS
    for(int s = 0; s < NUM_SUITS; ++s)
    {
        if(SUIT_NAMES_BY_WEIGHT[s] == lhs.get_suit())
        {
            LS = s;
        }
        if(SUIT_NAMES_BY_WEIGHT[s] == rhs.get_suit())
        {
            RS = s;
        }
    }
    
    //RANK COMPARISONS
    for(int r = 0; r < NUM_RANKS; ++r)
    {
        if(RANK_NAMES_BY_WEIGHT[r] == lhs.get_rank())
        {
            LR = r;
        }
        if(RANK_NAMES_BY_WEIGHT[r] == rhs.get_rank())
        {
            RR = r;
        }
    }
    
    //RESULT
    if(LR > RR)
    {
        return true;
    }
    else if(LR == RR && LS > RS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs)
{
    if(lhs.get_suit() == rhs.get_suit() && lhs.get_rank() == rhs.get_rank())
    {
        return true;
    }
    return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs)
{
    if(lhs.get_suit() != rhs.get_suit() && lhs.get_rank() != rhs.get_rank())
    {
        return true;
    }
    return false;
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit)
{
    if(suit == Card::SUIT_SPADES)
    {
        return Card::SUIT_CLUBS;
    }
    if(suit == Card::SUIT_HEARTS)
    {
        return Card::SUIT_DIAMONDS;
    }
    if(suit == Card::SUIT_CLUBS)
    {
        return Card::SUIT_SPADES;
    }
    if(suit == Card::SUIT_DIAMONDS)
    {
        return Card::SUIT_HEARTS;
    }
    return 0;
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card)
{
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}


//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b. Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump)
{
    //a and b are both trump cards
    int aR, bR;
    if(a.is_trump(trump) && b.is_trump(trump))
    {
        if(a.is_right_bower(trump) == true)
        {
            return false;
        }
        for(int r = 0; r < NUM_RANKS; ++r)
        {
            if(RANK_NAMES_BY_WEIGHT[r] == a.get_suit())
            {
                aR = r;
            }
            if(RANK_NAMES_BY_WEIGHT[r] == b.get_suit())
            {
                bR = r;
            }
        }
        if(aR < bR)
        {
            return true;
        }
    }
    
    //a and b are both NOT trump cards
    if(!a.is_trump(trump) && !b.is_trump(trump))
    {
        if(operator<(a,b) == true)
        {
            return true;
        }
    }
    
    //a is a trump card but b is NOT
    if(a.is_trump(trump) && !b.is_trump(trump))
    {
        if(a.is_right_bower(trump) != true && b.is_left_bower(trump) == true)
        {
            return true;
        }
        return false;
    }
    
    //a is NOT a trump card but b is
    if(!a.is_trump(trump) && b.is_trump(trump))
    {
        if(a.is_left_bower(trump) == true && b.is_right_bower(trump) != true)
        {
            return false;
        }
        return true;
    }
    return false;
}

// REQUIRES trump is a valid suit
// EFFECTS Returns true if a is lower value than b. Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card, const std::string &trump)
{
    //*******LED CARD IS A THE TRUMP SUIT*********
    if(led_card.is_trump(trump))
    {
        //if a and b are trump suits
        if(a.is_trump(trump) && b.is_trump(trump))
        {
            if(Card_less(a, b, trump) == true)
            {
                return true;
            }
        }
    
        //if a and b are NOT trump suits
        if(!a.is_trump(trump) && !b.is_trump(trump))
        {
            if(operator<(a, b))
            {
                return true;
            }
        }

        //if a is trump suit and b is NOT
        if(a.is_trump(trump) && !b.is_trump(trump))
        {
            if(!a.is_right_bower(trump) && b.is_left_bower(trump))
            {
                return true;
            }
            return false;
        }
        
        //if a is NOT trump suit and b is
        if(!a.is_trump(trump) && b.is_trump(trump))
        {
            if(a.is_left_bower(trump) && !b.is_right_bower(trump))
            {
                return false;
            }
            return true;
        }
    }
    
    //*******LED CARD IS NOT THE TRUMP SUIT********
    if(!led_card.is_trump(trump))
    {
        //if a and b are trump suits
        if(a.is_trump(trump) && b.is_trump(trump))
        {
            if(Card_less(a, b, trump) == true)
            {
                return true;
            }
        }
            
        //if a and b are NOT trump suits
        if(!a.is_trump(trump) && !b.is_trump(trump))
        {
            if(led_card.get_suit() == a.get_suit() && led_card.get_suit() != b.get_suit())
            {
                return false;
            }
            if(led_card.get_suit() != a.get_suit() && led_card.get_suit() == b.get_suit())
            {
                return true;
            }
            if(led_card.get_suit() != a.get_suit() && led_card.get_suit() != b.get_suit())
            {
                if(operator<(a, b))
                {
                    return true;
                }
            }
        }
                
        //if a is trump suit and b is NOT
        if(a.is_trump(trump) && !b.is_trump(trump))
        {
            if(!a.is_right_bower(trump) && b.is_left_bower(trump))
            {
                return true;
            }
            return false;
        }
                    
        //if a is NOT trump suit and b is
        if(!a.is_trump(trump) && b.is_trump(trump))
        {
            if(a.is_left_bower(trump) && !b.is_right_bower(trump))
            {
                return false;
            }
            return true;
        }
                        
    }
    return false;
}













