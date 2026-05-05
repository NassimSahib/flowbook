#include <stdexcept>
#include "order.hpp"
#include "price_level.hpp"



PriceLevel::PriceLevel(Price price)
    : price_(price) {}

void PriceLevel::AddOrder(const Order &order) {
    if (order.GetPrice() != price_) {
        throw std::logic_error("Price mismatch");
    }
    orders_.push_back(order);
}

Order& PriceLevel::Front() {
    return orders_.front();
}

const Order& PriceLevel::Front() const {
    return orders_.front();
}

void PriceLevel::PopFront() {
    orders_.pop_front();
}

std::size_t PriceLevel::size() const {
    return orders_.size();
}

Quantity PriceLevel::Match(Quantity quantity_to_match) {
    Quantity remaining = quantity_to_match;

    while (remaining > 0 && !orders_.empty()) {
        Order& front = Front();
        Quantity available = front.GetRemainingQuantity();

        if (available <= remaining) {
            front.ReduceQuantity(available);
            remaining -= available;
            PopFront();
        } else {
            front.ReduceQuantity(remaining);
            remaining = 0;
        }
    }

    return quantity_to_match - remaining;
}

bool PriceLevel::Empty() const {
    return orders_.empty();
}

Quantity PriceLevel::TotalQuantity() const {
    Quantity total = 0;
    for (const auto& order : orders_) {
        total += order.GetRemainingQuantity();
    }
    return total;
}

