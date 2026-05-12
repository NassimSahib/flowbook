#pragma once

#include <map>
#include <vector>

#include <cstddef>
#include "price_level.hpp"
#include "trade.hpp"

class OrderBook {
private:
    std::map<Price, PriceLevel, std::greater<>> bids_;
    std::map<Price, PriceLevel, std::less<>> asks_;

public:
    OrderBook() = default;

    std::vector<Trade> AddOrder(Order order);

    std::size_t BidLevelCount() const;
    std::size_t AskLevelCount() const;

    Quantity GetTotalBidQuantityAtPrice(Price price) const;
    Quantity GetTotalAskQuantityAtPrice(Price price) const;

    OrderId GetFrontBidOrderIdAtPrice(Price price) const;
    Quantity GetFrontBidRemainingQuantityAtPrice(Price price) const;

private:
    std::vector<Trade> Match(Order &incoming);
    void AddToBook(const Order &order);
    bool CanMatch(const Order &incoming) const;
};