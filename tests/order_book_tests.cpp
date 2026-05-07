#include "order_book.hpp"
#include "order.hpp"

#include <gtest/gtest.h>

TEST(OrderBookTest, AddBuyAndSellWithoutMatch) {
    OrderBook ob;

    ob.AddOrder(Order(1, 1, 100, 10, Side::Buy));
    ob.AddOrder(Order(2, 2, 101, 5, Side::Sell));

    EXPECT_EQ(ob.BidLevelCount(), 1);
    EXPECT_EQ(ob.AskLevelCount(), 1);

    EXPECT_EQ(ob.GetTotalBidQuantityAtPrice(100), 10);
    EXPECT_EQ(ob.GetTotalAskQuantityAtPrice(101), 5);
}

TEST(OrderBookTest, BuyCrossesMultipleAskLevels) {
    OrderBook ob;

    ob.AddOrder(Order(1, 1, 100, 5, Side::Sell));
    ob.AddOrder(Order(2, 2, 101, 5, Side::Sell));
    ob.AddOrder(Order(3, 3, 102, 8, Side::Buy));

    EXPECT_EQ(ob.BidLevelCount(), 0);
    EXPECT_EQ(ob.AskLevelCount(), 1);

    EXPECT_EQ(ob.GetTotalAskQuantityAtPrice(100), 0);
    EXPECT_EQ(ob.GetTotalAskQuantityAtPrice(101), 2);
}

TEST(OrderBookTest, SellCrossesMultipleBidLevels) {
    OrderBook ob;

    ob.AddOrder(Order(1, 1, 101, 5, Side::Buy));
    ob.AddOrder(Order(2, 2, 100, 5, Side::Buy));
    ob.AddOrder(Order(3, 3, 99, 8, Side::Sell));

    EXPECT_EQ(ob.BidLevelCount(), 1);
    EXPECT_EQ(ob.AskLevelCount(), 0);

    EXPECT_EQ(ob.GetTotalBidQuantityAtPrice(101), 0);
    EXPECT_EQ(ob.GetTotalBidQuantityAtPrice(100), 2);
}

TEST(OrderBookTest, FifoAtSamePriceLeavesSecondOrderPartiallyFilled) {
    OrderBook ob;

    ob.AddOrder(Order(1, 1, 100, 5, Side::Buy));
    ob.AddOrder(Order(2, 2, 100, 5, Side::Buy));
    ob.AddOrder(Order(3, 3, 100, 7, Side::Sell));

    EXPECT_EQ(ob.BidLevelCount(), 1);
    EXPECT_EQ(ob.AskLevelCount(), 0);

    EXPECT_EQ(ob.GetTotalBidQuantityAtPrice(100), 3);

    // Seulement si tu as ajouté ces deux fonctions aussi :
    EXPECT_EQ(ob.GetFrontBidOrderIdAtPrice(100), 2);
    EXPECT_EQ(ob.GetFrontBidRemainingQuantityAtPrice(100), 3);
}