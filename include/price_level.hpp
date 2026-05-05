#pragma once

#include <cstddef>
#include <deque>
#include "order.hpp"

class PriceLevel
{
private:
    Price price_;
    std::deque<Order> orders_;

public:
    explicit PriceLevel(Price price);

    // Accessors
    Price GetPrice() const;
    bool Empty() const;
    std::size_t size() const;

    // Core operations
    void AddOrder(const Order &order);

    Order &Front();
    const Order &Front() const;

    void PopFront();

    // Matching Helper
    Quantity Match(Quantity quantity_to_match);

    // Printing
    Quantity TotalQuantity() const;
};
