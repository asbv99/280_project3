#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here
TEST(test_card_get_suit) {
    std::vector<Card> cards;
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_EIGHT, Card::SUIT_HEARTS);
    Card c3(Card::RANK_FOUR, Card::SUIT_CLUBS);
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);
    
    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);
    
    ASSERT_EQUAL(Card::SUIT_SPADES, cards.at(0).get_suit());
    ASSERT_EQUAL(Card::SUIT_HEARTS, cards.at(1).get_suit());
}
TEST(test_card_get_rank) {
    std::vector<Card> cards;
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_EIGHT, Card::SUIT_HEARTS);
    Card c3(Card::RANK_FOUR, Card::SUIT_CLUBS);
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);
    
    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);
    
    ASSERT_EQUAL(Card::RANK_JACK, cards.at(0).get_rank());
    ASSERT_EQUAL(Card::RANK_FOUR, cards.at(2).get_rank());
}
TEST(test_card_is_face) {
    std::vector<Card> cards;
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_EIGHT, Card::SUIT_HEARTS);
    Card c3(Card::RANK_FOUR, Card::SUIT_CLUBS);
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);
    
    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);
    
    ASSERT_EQUAL(true, cards.at(0).is_face());
    ASSERT_EQUAL(false, cards.at(2).is_face());
}
TEST(test_card_is_right_bower) {
    std::vector<Card> cards;
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_EIGHT, Card::SUIT_HEARTS);
    Card c3(Card::RANK_FOUR, Card::SUIT_CLUBS);
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);
    
    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);
    
    const std::string trump = cards.at(0).get_suit();
    
    ASSERT_EQUAL(true, cards.at(0).is_right_bower(trump));
    ASSERT_EQUAL(false, cards.at(2).is_right_bower(trump));
}
TEST(test_card_is_left_bower) {
    std::vector<Card> cards;
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_EIGHT, Card::SUIT_HEARTS);
    Card c3(Card::RANK_FOUR, Card::SUIT_CLUBS);
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);
    
    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);
    
    const std::string trump = cards.at(0).get_suit();
    
    ASSERT_EQUAL(false, cards.at(0).is_left_bower(trump));
    ASSERT_EQUAL(true, cards.at(3).is_left_bower(trump));
}
TEST(test_card_is_trump) {
    std::vector<Card> cards;
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_EIGHT, Card::SUIT_SPADES);
    Card c3(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);
    
    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);
    
    const std::string trump = cards.at(0).get_suit();
    
    ASSERT_EQUAL(true, cards.at(0).is_trump(trump));
    ASSERT_EQUAL(true, cards.at(3).is_trump(trump));
    ASSERT_EQUAL(false, cards.at(2).is_trump(trump));
}

// NON MEMBER FUNCTIONS TESTS
TEST(test_card_oper_lower) {
    std::vector<Card> cards;
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c3(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);
    
    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);
    
    ASSERT_EQUAL(false, cards.at(0) < cards.at(2));
    ASSERT_EQUAL(true, (cards.at(2) < cards.at(1)));
    ASSERT_EQUAL(false, (cards.at(3) < cards.at(0)));
}
TEST(test_card_oper_higher) {
    std::vector<Card> cards;
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c3(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);
    
    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);
    
    ASSERT_EQUAL(true, (cards.at(0) > cards.at(2)));
    ASSERT_EQUAL(false, (cards.at(2) > cards.at(1)));
    ASSERT_EQUAL(true, (cards.at(3) > cards.at(0)));
}
TEST(test_card_oper_equal) {
    std::vector<Card> cards;
    Card c1(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c2(Card::RANK_EIGHT, Card::SUIT_SPADES);
    Card c3(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);

    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);

    ASSERT_EQUAL(false, (cards.at(0) == cards.at(2)));
    ASSERT_EQUAL(false, (cards.at(2) == cards.at(1)));
    ASSERT_EQUAL(true, (cards.at(3) == cards.at(0)));
}
TEST(test_card_oper_not_equal) {
   std::vector<Card> cards;
    Card c1(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c2(Card::RANK_EIGHT, Card::SUIT_SPADES);
    Card c3(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);

    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);

    ASSERT_EQUAL(true, (cards.at(0) != cards.at(2)));
    ASSERT_EQUAL(true, (cards.at(2) != cards.at(1)));
    ASSERT_EQUAL(false, (cards.at(3) != cards.at(0)));
}
TEST(test_card_suit_next) {
    
    ASSERT_EQUAL(Card::SUIT_CLUBS, Suit_next(Card::SUIT_SPADES));
    ASSERT_EQUAL(Card::SUIT_HEARTS, Suit_next(Card::SUIT_DIAMONDS));
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, Suit_next(Card::SUIT_HEARTS));
}
TEST(test_card_Card_less_trump) {
    std::vector<Card> cards;
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);

    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);

    const std::string trump = cards.at(2).get_suit();

    ASSERT_TRUE(Card_less(cards.at(1), cards.at(0), trump));
    ASSERT_TRUE(Card_less(cards.at(0), cards.at(2), trump));
    ASSERT_FALSE(Card_less(cards.at(2), cards.at(1), trump));
}
TEST(test_card_card_less_lead) {
    std::vector<Card> cards;
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c3(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);

    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);

    const Card led_card = cards.at(2);
    const std::string trump = Card::SUIT_SPADES;

    ASSERT_TRUE(Card_less(cards.at(1), cards.at(0), led_card, trump));
    ASSERT_FALSE(Card_less(cards.at(0), cards.at(2), led_card, trump));
    ASSERT_TRUE(Card_less(cards.at(2), cards.at(1), led_card, trump));
}



























TEST_MAIN()
