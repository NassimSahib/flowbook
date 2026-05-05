#include <stdexcept>
#include "order.hpp"

Order::Order(OrderId id, Timestamp ts, Price price, Quantity qty, Side side)
    : id_(id),
      timestamp_(ts),
      price_(price),
      quantity_(qty),
      remainingQuantity_(qty),
      side_(side) {}

// Getters

OrderId Order::GetId() const {
    return id_;
}

Price Order::GetPrice() const {
    return price_;
}

Side Order::GetSide() const {
    return side_;
}

Quantity Order::GetQuantity() const {
    return quantity_;
}

Quantity Order::GetRemainingQuantity() const {
    return remainingQuantity_;
}

// Core logic

void Order::ReduceQuantity(Quantity quantity) {
    if (quantity > remainingQuantity_) {
        throw std::logic_error("Cannot reduce more than remaining quantity.");
    }
    
    remainingQuantity_ -= quantity;
}