#pragma once

#include <cstdint>

using OrderId = uint64_t;
using Price = uint64_t;
using Quantity = uint32_t;
using Timestamp = uint64_t;

enum class Side : uint8_t
{
    Buy,
    Sell
};

class Order
{
private:
    OrderId id_;
    Timestamp timestamp_;
    Price price_;
    Quantity quantity_;
    Quantity remainingQuantity_;
    Side side_;
public:
    Order(OrderId id, Timestamp ts, Price price, Quantity qty, Side side);
    
    OrderId GetId() const;
    Price GetPrice() const;
    Timestamp GetTimestamp() const;
    Side GetSide() const;
    Quantity GetQuantity() const;
    Quantity GetRemainingQuantity() const;
    

    void ReduceQuantity(Quantity quantity);
};

// static_assert(sizeof(Order) <= 64);