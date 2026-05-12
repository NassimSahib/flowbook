#pragma once

#include "order.hpp"

class Trade {
private:
    OrderId buy_order_id_;
    OrderId sell_order_id_;
    Price price_;
    Quantity quantity_;
    Timestamp timestamp_;

public:
    Trade(OrderId buy_order_id,
          OrderId sell_order_id,
          Price price,
          Quantity quantity,
          Timestamp timestamp);

    
    OrderId GetBuyOrderId() const;
    OrderId GetSellOrderId() const;
    Price GetPrice() const;
    Quantity GetQuantity() const;
    Timestamp GetTimestamp() const; 

};