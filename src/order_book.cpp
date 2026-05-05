#include "order.hpp"
#include "price_level.hpp"
#include "order_book.hpp"

#include <iostream>
#include <stdexcept>

bool OrderBook::CanMatch(const Order &incoming) const {
    if (incoming.GetSide() == Side::Buy) {
        return !asks_.empty() && incoming.GetPrice() >= asks_.begin()->first;
    }
    return !bids_.empty() && incoming.GetPrice() <= bids_.begin()->first;
}

void OrderBook::Match(Order &incoming) {
    while (incoming.GetRemainingQuantity() && CanMatch(incoming)) {
        if (incoming.GetSide() == Side::Buy) {
            if (asks_.empty()) break;

            auto best_level = asks_.begin();

            Quantity matched = best_level->second.Match(incoming.GetRemainingQuantity());
                incoming.ReduceQuantity(matched);

                if (best_level->second.Empty()) {
                    asks_.erase(best_level);
                }
            } else {
                if (bids_.empty()) break;

                auto best_level = bids_.begin();

                Quantity matched = best_level->second.Match(incoming.GetRemainingQuantity());
                incoming.ReduceQuantity(matched);

                if (best_level->second.Empty()) {
                    bids_.erase(best_level);
                }
                
            }
        }
    }

void OrderBook::AddOrder(Order order) {
    Match(order);
    if (order.GetRemainingQuantity() > 0) 
        AddToBook(order);
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