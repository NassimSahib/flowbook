#include "trade.hpp"

Trade::Trade(OrderId buy_order_id,
             OrderId sell_order_id,
             Price price,
             Quantity quantity,
             Timestamp timestamp)
    : buy_order_id_(buy_order_id),
      sell_order_id_(sell_order_id),
      price_(price),
      quantity_(quantity),
      timestamp_(timestamp) {}

OrderId Trade::GetBuyOrderId() const {
    return buy_order_id_;
}

OrderId Trade::GetSellOrderId() const {
    return sell_order_id_;
}

Price Trade::GetPrice() const {
    return price_;
}

Quantity Trade::GetQuantity() const {
    return quantity_;
}

Timestamp Trade::GetTimestamp() const {
    return timestamp_;
}