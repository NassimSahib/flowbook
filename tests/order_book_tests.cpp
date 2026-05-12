#include "order_book.hpp"
#include "order.hpp"
#include "trade.hpp"

#include <gtest/gtest.h>

TEST(OrderBookTest, AddBuyAndSellWithoutMatch) {
    OrderBook ob;

    auto trades1 = ob.AddOrder(Order(1, 1, 100, 10, Side::Buy));
    auto trades2 = ob.AddOrder(Order(2, 2, 101, 5, Side::Sell));

    EXPECT_EQ(trades1.size(), 0);
    EXPECT_EQ(trades2.size(), 0);

    EXPECT_EQ(ob.BidLevelCount(), 1);
    EXPECT_EQ(ob.AskLevelCount(), 1);

    EXPECT_EQ(ob.GetTotalBidQuantityAtPrice(100), 10);
    EXPECT_EQ(ob.GetTotalAskQuantityAtPrice(101), 5);
}

TEST(OrderBookTest, BuyCrossesMultipleAskLevelsAndGeneratesTrades) {
    OrderBook ob;

    auto trades1 = ob.AddOrder(Order(1, 1, 100, 5, Side::Sell));
    auto trades2 = ob.AddOrder(Order(2, 2, 101, 5, Side::Sell));
    auto trades3 = ob.AddOrder(Order(3, 3, 102, 8, Side::Buy));

    EXPECT_EQ(trades1.size(), 0);
    EXPECT_EQ(trades2.size(), 0);
    ASSERT_EQ(trades3.size(), 2);

    EXPECT_EQ(trades3[0].GetBuyOrderId(), 3);
    EXPECT_EQ(trades3[0].GetSellOrderId(), 1);
    EXPECT_EQ(trades3[0].GetPrice(), 100);
    EXPECT_EQ(trades3[0].GetQuantity(), 5);
    EXPECT_EQ(trades3[0].GetTimestamp(), 3);

    EXPECT_EQ(trades3[1].GetBuyOrderId(), 3);
    EXPECT_EQ(trades3[1].GetSellOrderId(), 2);
    EXPECT_EQ(trades3[1].GetPrice(), 101);
    EXPECT_EQ(trades3[1].GetQuantity(), 3);
    EXPECT_EQ(trades3[1].GetTimestamp(), 3);

    EXPECT_EQ(ob.BidLevelCount(), 0);
    EXPECT_EQ(ob.AskLevelCount(), 1);

    EXPECT_EQ(ob.GetTotalAskQuantityAtPrice(100), 0);
    EXPECT_EQ(ob.GetTotalAskQuantityAtPrice(101), 2);
}

TEST(OrderBookTest, SellCrossesMultipleBidLevelsAndGeneratesTrades) {
    OrderBook ob;

    auto trades1 = ob.AddOrder(Order(1, 1, 101, 5, Side::Buy));
    auto trades2 = ob.AddOrder(Order(2, 2, 100, 5, Side::Buy));
    auto trades3 = ob.AddOrder(Order(3, 3, 99, 8, Side::Sell));

    EXPECT_EQ(trades1.size(), 0);
    EXPECT_EQ(trades2.size(), 0);
    ASSERT_EQ(trades3.size(), 2);

    EXPECT_EQ(trades3[0].GetBuyOrderId(), 1);
    EXPECT_EQ(trades3[0].GetSellOrderId(), 3);
    EXPECT_EQ(trades3[0].GetPrice(), 101);
    EXPECT_EQ(trades3[0].GetQuantity(), 5);
    EXPECT_EQ(trades3[0].GetTimestamp(), 3);

    EXPECT_EQ(trades3[1].GetBuyOrderId(), 2);
    EXPECT_EQ(trades3[1].GetSellOrderId(), 3);
    EXPECT_EQ(trades3[1].GetPrice(), 100);
    EXPECT_EQ(trades3[1].GetQuantity(), 3);
    EXPECT_EQ(trades3[1].GetTimestamp(), 3);

    EXPECT_EQ(ob.BidLevelCount(), 1);
    EXPECT_EQ(ob.AskLevelCount(), 0);

    EXPECT_EQ(ob.GetTotalBidQuantityAtPrice(101), 0);
    EXPECT_EQ(ob.GetTotalBidQuantityAtPrice(100), 2);
}

TEST(OrderBookTest, FifoAtSamePriceLeavesSecondOrderPartiallyFilledAndGeneratesTrades) {
    OrderBook ob;

    auto trades1 = ob.AddOrder(Order(1, 1, 100, 5, Side::Buy));
    auto trades2 = ob.AddOrder(Order(2, 2, 100, 5, Side::Buy));
    auto trades3 = ob.AddOrder(Order(3, 3, 100, 7, Side::Sell));

    EXPECT_EQ(trades1.size(), 0);
    EXPECT_EQ(trades2.size(), 0);
    ASSERT_EQ(trades3.size(), 2);

    EXPECT_EQ(trades3[0].GetBuyOrderId(), 1);
    EXPECT_EQ(trades3[0].GetSellOrderId(), 3);
    EXPECT_EQ(trades3[0].GetPrice(), 100);
    EXPECT_EQ(trades3[0].GetQuantity(), 5);
    EXPECT_EQ(trades3[0].GetTimestamp(), 3);

    EXPECT_EQ(trades3[1].GetBuyOrderId(), 2);
    EXPECT_EQ(trades3[1].GetSellOrderId(), 3);
    EXPECT_EQ(trades3[1].GetPrice(), 100);
    EXPECT_EQ(trades3[1].GetQuantity(), 2);
    EXPECT_EQ(trades3[1].GetTimestamp(), 3);

    EXPECT_EQ(ob.BidLevelCount(), 1);
    EXPECT_EQ(ob.AskLevelCount(), 0);

    EXPECT_EQ(ob.GetTotalBidQuantityAtPrice(100), 3);

    EXPECT_EQ(ob.GetFrontBidOrderIdAtPrice(100), 2);
    EXPECT_EQ(ob.GetFrontBidRemainingQuantityAtPrice(100), 3);
}