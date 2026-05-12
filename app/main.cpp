#include "order_book.hpp"

#include <iostream>

int main() {
    OrderBook ob;

    Order buy1(1, 1, 100, 10, Side::Buy);
    auto trades1 = ob.AddOrder(buy1);

    std::cout << "Trades after buy1: " << trades1.size() << "\n";

    Order sell1(2, 2, 100, 4, Side::Sell);
    auto trades2 = ob.AddOrder(sell1);

    std::cout << "Trades after sell1: " << trades2.size() << "\n";

    for (const auto& trade : trades2) {
        std::cout << "Trade: buy="
                  << trade.GetBuyOrderId()
                  << " sell="
                  << trade.GetSellOrderId()
                  << " price="
                  << trade.GetPrice()
                  << " qty="
                  << trade.GetQuantity()
                  << " ts="
                  << trade.GetTimestamp()
                  << "\n";
    }

    std::cout << "Remaining bid qty at 100: "
              << ob.GetTotalBidQuantityAtPrice(100)
              << "\n";

    return 0;
}