//#ifndef PACK_H
//#define PACK_H
/* Pack.h
 *
 * Represents a pack of playing cards
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * 2014-12-21
 */

#include "Card.h"
#include "Pack.h"
#include <array>
#include <string>

    // EFFECTS: Initializes the Pack to be in the following standard order:
    //          the cards of the lowest suit arranged from lowest rank to
    //          highest rank, followed by the cards of the next lowest suit
    //          in order from lowest to highest rank, and so on.
    // NOTE: The standard order is the same as that in pack.in.
    // NOTE: Do NOT use pack.in in your implementation of this function
    Pack::Pack()
    {
        next = 0;
        for(int suitIndex = 0; suitIndex < NUM_SUITS; ++suitIndex)
        {
            for(int rankIndex = 7; rankIndex < NUM_RANKS; ++rankIndex)
            {
                cards[next] = Card(RANK_NAMES_BY_WEIGHT[rankIndex], SUIT_NAMES_BY_WEIGHT[suitIndex]);
                ++next;
            }
        }
        next = 0;
    }

    // REQUIRES: pack_input contains a representation of a Pack in the
    //           format required by the project specification
    // MODIFIES: pack_input
    // EFFECTS: Initializes Pack by reading from pack_input.
    Pack::Pack(std::istream& pack_input)
    {
        std::string card_rank;
        std::string card_suit;
        std::string lalalalala;
        
        next = 0;
        while(pack_input >> card_rank >> lalalalala >> card_suit)
        {
            cards[next] = Card(card_rank, card_suit);
            ++next;
        }
        next = 0;
    }

    // REQUIRES: cards remain in the Pack
    // EFFECTS: Returns the next card in the pack and increments the next index
    Card Pack::deal_one()
    {
        ++next;
        return cards[next - 1];
    }
    
    // EFFECTS: Resets next index to first card in the Pack
    void Pack::reset()
    {
        next = 0;
    }
    
    // EFFECTS: Shuffles the Pack and resets the next index. This
    //          performs an in shuffle seven times. See
    //          https://en.wikipedia.org/wiki/In_shuffle.
    void Pack::shuffle()
    {
        //CREATE AN OLD AND NEW COPY OF THE PACK
        Card oldCard[PACK_SIZE];
        Card newCard[PACK_SIZE];
    
        //SHUFFLE THROUGH 7 TIMES
        int shuffleNum = 0;
        while(shuffleNum < 7)
        {
            //INITIALIZING OLD AND NEW PACKS
            for(int c = 0; c < PACK_SIZE; ++c)
            {
                oldCard[next] = cards[c];
                newCard[next] = cards[c];
                ++next;
            }
            reset();
            
            //*******ACTUAL SHUFFLE CODE*******//
            int index1 = 0;
            int index2 = 12;
            while(index1 < 12 && index2 < 24)
            {
                cards[index1*2] = oldCard[index2];
                cards[2*index1 + 1] = newCard[index1];
                ++index1;
                ++index2;
            }
            ++shuffleNum;
        }
    }



    // EFFECTS: returns true if there are no more cards left in the pack
    bool Pack::empty() const
    {
        if(next == PACK_SIZE)
        {
            return true;
        }
        return false;
    }


