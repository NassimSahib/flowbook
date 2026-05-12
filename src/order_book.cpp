#include "order_book.hpp"
#include "order.hpp"
#include "price_level.hpp"
#include "trade.hpp"

#include <algorithm>
#include <stdexcept>
#include <vector>

bool OrderBook::CanMatch(const Order& incoming) const {
    if (incoming.GetSide() == Side::Buy) {
        return !asks_.empty() && incoming.GetPrice() >= asks_.begin()->first;
    }

    return !bids_.empty() && incoming.GetPrice() <= bids_.begin()->first;
}

std::vector<Trade> OrderBook::Match(Order& incoming) {
    std::vector<Trade> trades;

    while (incoming.GetRemainingQuantity() > 0 && CanMatch(incoming)) {
        if (incoming.GetSide() == Side::Buy) {
            auto best_level = asks_.begin();

            Order& resting = best_level->second.Front();

            Quantity matched = std::min(
                incoming.GetRemainingQuantity(),
                resting.GetRemainingQuantity()
            );

            Trade trade(
                incoming.GetId(),          // buy order id
                resting.GetId(),           // sell order id
                best_level->first,         // execution price
                matched,
                incoming.GetTimestamp()    // timestamp of incoming order
            );

            trades.push_back(trade);

            incoming.ReduceQuantity(matched);
            resting.ReduceQuantity(matched);

            if (resting.GetRemainingQuantity() == 0) {
                best_level->second.PopFront();
            }

            if (best_level->second.Empty()) {
                asks_.erase(best_level);
            }
        } else {
            auto best_level = bids_.begin();

            Order& resting = best_level->second.Front();

            Quantity matched = std::min(
                incoming.GetRemainingQuantity(),
                resting.GetRemainingQuantity()
            );

            Trade trade(
                resting.GetId(),           // buy order id
                incoming.GetId(),          // sell order id
                best_level->first,         // execution price
                matched,
                incoming.GetTimestamp()    // timestamp of incoming order
            );

            trades.push_back(trade);

            incoming.ReduceQuantity(matched);
            resting.ReduceQuantity(matched);

            if (resting.GetRemainingQuantity() == 0) {
                best_level->second.PopFront();
            }

            if (best_level->second.Empty()) {
                bids_.erase(best_level);
            }
        }
    }

    return trades;
}

std::vector<Trade> OrderBook::AddOrder(Order order) {
    std::vector<Trade> trades = Match(order);

    if (order.GetRemainingQuantity() > 0) {
        AddToBook(order);
    }

    return trades;
}

void OrderBook::AddToBook(const Order& order) {
    if (order.GetSide() == Side::Buy) {
        auto it = bids_.find(order.GetPrice());

        if (it == bids_.end()) {
            PriceLevel level(order.GetPrice());
            level.AddOrder(order);
            bids_.emplace(order.GetPrice(), std::move(level));
        } else {
            it->second.AddOrder(order);
        }
    } else {
        auto it = asks_.find(order.GetPrice());

        if (it == asks_.end()) {
            PriceLevel level(order.GetPrice());
            level.AddOrder(order);
            asks_.emplace(order.GetPrice(), std::move(level));
        } else {
            it->second.AddOrder(order);
        }
    }
}

std::size_t OrderBook::BidLevelCount() const {
    return bids_.size();
}

std::size_t OrderBook::AskLevelCount() const {
    return asks_.size();
}

Quantity OrderBook::GetTotalBidQuantityAtPrice(Price price) const {
    auto it = bids_.find(price);

    if (it == bids_.end()) {
        return 0;
    }

    return it->second.TotalQuantity();
}

Quantity OrderBook::GetTotalAskQuantityAtPrice(Price price) const {
    auto it = asks_.find(price);

    if (it == asks_.end()) {
        return 0;
    }

    return it->second.TotalQuantity();
}

OrderId OrderBook::GetFrontBidOrderIdAtPrice(Price price) const {
    auto it = bids_.find(price);

    if (it == bids_.end()) {
        throw std::logic_error("Bid price level not found");
    }

    return it->second.Front().GetId();
}

Quantity OrderBook::GetFrontBidRemainingQuantityAtPrice(Price price) const {
    auto it = bids_.find(price);

    if (it == bids_.end()) {
        throw std::logic_error("Bid price level not found");
    }

    return it->second.Front().GetRemainingQuantity();
}