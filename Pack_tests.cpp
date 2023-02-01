#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
}

// Add more tests here
TEST(test_pack_deal_one) {
    Pack pack;
    Card first = pack.deal_one();
    Card second = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_TEN, second.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, second.get_suit());
}
TEST(test_pack_reset) {
    Pack pack;
    pack.deal_one();
    Card sec = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_TEN, sec.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, sec.get_suit());
    
    pack.reset();
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
}
TEST(test_pack_shuffle) {
    Pack pack;
    pack.shuffle();
    Card idk = pack.deal_one();
    Card idk2 = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_JACK, idk2.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, idk2.get_suit());
}
TEST(test_pack_empty_one) {
    Pack pack;
    for(int i = 0; i < 24; ++i)
    {
        pack.deal_one();
    }
    ASSERT_EQUAL(true, pack.empty());
}
TEST(test_pack_empty_two) {
    Pack pack;
    for(int i = 0; i < 20; ++i)
    {
        pack.deal_one();
    }
    ASSERT_EQUAL(false, pack.empty());
}

TEST_MAIN()
