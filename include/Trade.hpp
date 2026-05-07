#pragma once

#include "order.hpp"

class Trade {
private:
    OrderId buy_order_id_;
    OrderId sell_order_id_;
    Price price_;
    Quantity quantity;
    Timestamp timestamp_;

public:
    Trade(OrderId buy_order_id,
          OrderId sell_order_id,
          Price price,
          Quantity quantity,
          Timestamp timestamp)
        : buy_order_id_(buy_order_id),
          sell_order_id_(sell_order_id),
          price_(price),
};