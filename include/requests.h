#pragma once

#include <vector>

enum class LiquidityIndicator {
    Added,
    Removed
};

struct ExecutionDetails
{
    char cl_ord_id[15];
    unsigned match_number;
    unsigned filled_volume;
    double price;
    char counterpart[5];
    LiquidityIndicator liquidity_indicator;
    bool internalized;
    bool self_trade;
};

ExecutionDetails decode_executed_order(const std::vector<unsigned char> & message);