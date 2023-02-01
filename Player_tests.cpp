#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here
TEST(test_player_get_name1) {
    Player * anna = Player_factory("Anna", "Human");
    ASSERT_EQUAL("Anna", anna->get_name());

    delete anna;
}
TEST(test_player_add_card) {
    Player * alice = Player_factory("Alice", "Simple");
    
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
    
    alice->add_card(c1);
    
    ASSERT_EQUAL(c1 , alice->play_card(led_card, trump));
    delete alice;
}
TEST(test_player_add_card1) {
    Player * alice = Player_factory("Alice", "Simple");
    
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
    
    alice->add_card(c1);
    alice->add_card(c2);
    
    ASSERT_EQUAL(c2 , alice->play_card(led_card, trump));
    delete alice;
}
TEST(test_player_make_trump) {
    Player * alice = Player_factory("Alice", "Simple");
    
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
    const Card up(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    const Card upcard = up;
    std::string order_up_suit;
    
    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);

    ASSERT_TRUE(alice->make_trump(upcard, true, 1, order_up_suit));
    delete alice;
}
TEST(test_player_add_and_discard) {
    Player * alice = Player_factory("Alice", "Simple");

    std::vector<Card> cards;
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c3(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c4(Card::RANK_KING, Card::SUIT_SPADES);
    Card c5(Card::RANK_QUEEN, Card::SUIT_SPADES);
    
    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);
    cards.push_back(c5);
    
    Card led(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    const Card led_card = led;
    
    const std::string trump = Card::SUIT_SPADES;
    const Card up(Card::RANK_NINE, Card::SUIT_CLUBS);
    const Card upcard = up;
    std::string order_up_suit;

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    alice->add_and_discard(upcard);

    ASSERT_EQUAL(upcard, alice->play_card(led_card, trump));
    delete alice;
}
TEST(test_player_add_and_discard_two) {
    Player * alice = Player_factory("Alice", "Simple");
    
    std::vector<Card> cards;
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_NINE, Card::SUIT_SPADES);
    Card c3(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c4(Card::RANK_KING, Card::SUIT_SPADES);
    Card c5(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    
    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);
    cards.push_back(c5);
    
    Card led(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    const Card led_card = led;
    
    const std::string trump = Card::SUIT_SPADES;
    const Card up(Card::RANK_KING, Card::SUIT_HEARTS);
    const Card upcard = up;
    std::string order_up_suit;
    
    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);
    
    alice->add_and_discard(upcard);
    
    ASSERT_EQUAL(c1, alice->play_card(led_card, trump));
    delete alice;
}
TEST(test_player_lead_card) {
    Player * alice = Player_factory("Alice", "Simple");
    
    std::vector<Card> cards;
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_NINE, Card::SUIT_SPADES);
    Card c3(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c4(Card::RANK_KING, Card::SUIT_SPADES);
    Card c5(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    
    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);
    cards.push_back(c5);
    
    Card led(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    const Card led_card = led;
    
    const std::string trump = Card::SUIT_SPADES;
    
    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);
    
    ASSERT_EQUAL(c5, alice->lead_card(trump));
    delete alice;
}
TEST(test_player_lead_card_one) {
    Player * alice = Player_factory("Alice", "Simple");
    
    std::vector<Card> cards;
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_NINE, Card::SUIT_SPADES);
    Card c3(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c4(Card::RANK_KING, Card::SUIT_SPADES);
    Card c5(Card::RANK_QUEEN, Card::SUIT_SPADES);
    
    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);
    cards.push_back(c5);
    
    Card led(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    const Card led_card = led;
    
    const std::string trump = Card::SUIT_SPADES;
    
    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);
    
    ASSERT_EQUAL(c1, alice->lead_card(trump));
    delete alice;
}
//TEST(test_player_play_card) {
//    Player * alice = Player_factory("Alice", "Simple");
//    ASSERT_EQUAL("Alice", alice->get_name());
//
//    delete alice;
//}

TEST_MAIN()
