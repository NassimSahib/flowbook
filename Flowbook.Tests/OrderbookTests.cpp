#include <gtest/gtest.h>
#include "Orderbook.hpp"

TEST(OrderBookTests, NewOrderbookIsEmpty) {
	Orderbook orderbook;

	EXPECT_EQ(orderbook.Size(), 0);
}