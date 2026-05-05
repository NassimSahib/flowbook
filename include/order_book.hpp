#pragma once

#include <map>
#include <cstddef>
#include "price_level.hpp"

class OrderBook
{
private:
    // Buyside (highest price first)
    std::map<Price, PriceLevel, std::greater<>> bids_;

    // Sell side (lowest price first)
    std::map<Price, PriceLevel, std::less<>> asks_;

public:
    OrderBook() = default;

    // Core API
    void AddOrder(Order order);

    // Print
    void PrintBook() const;

        // Test / Query Helpers
    std::size_t BidLevelCount() const;
    std::size_t AskLevelCount() const;

    Quantity GetTotalBidQuantityAtPrice(Price price) const;
    Quantity GetTotalAskQuantityAtPrice(Price price) const;

    OrderId GetFrontBidOrderIdAtPrice(Price price) const;
    Quantity GetFrontBidRemainingQuantityAtPrice(Price price) const;

private:
    // Matching logic
    void Match(Order &incoming);

    // Helpers
    void AddToBook(const Order &order);

    bool CanMatch(const Order &incoming) const;
};