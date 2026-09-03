#pragma once

#include <vector>

#include "TradeInfo.hpp"

class Trade
{
public:
    Trade(const TradeInfo& bidTrade, const TradeInfo& askTrade)
    : bidTrade_{ bidTrade }
    , askTrade_{ askTrade }
    { }

    const TradeInfo& GetBidTradeInfo() const { return bidTrade_; }
    const TradeInfo& GetAskTradeInfo() const { return askTrade_; }

private:
    TradeInfo bidTrade_;
    TradeInfo askTrade_;
};

using Trades = std::vector<Trade>;