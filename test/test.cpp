#include "requests.h"

#include <gtest/gtest.h>
#include <string>
#include <stdio.h>

TEST(ExecutedOrderTest, decode_bofa_executed_order)
{
    std::vector<unsigned char> message;
    // '12345678912345'
    std::vector<unsigned char> orderId = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '1', '2', '3', '4', '5'};
    message.insert(message.end(), orderId.begin(), orderId.end());
    // 4831
    std::vector<unsigned char> match_number = { 0x00, 0x00, 0x12, 0xdf };
    message.insert(message.end(), match_number.begin(), match_number.end());
    // 100000
    std::vector<unsigned char> filled_volume = { 0x00, 0x01, 0x86, 0xa0 };
    message.insert(message.end(), filled_volume.begin(), filled_volume.end());
    // 14.746
    std::vector<unsigned char> fill_price = { 0x00, 0x02, 0x40, 0x04 };
    message.insert(message.end(), fill_price.begin(), fill_price.end());
    // BofA
    std::vector<unsigned char> counter_part = { 'B', 'o', 'f', 'A' };
    message.insert(message.end(), counter_part.begin(), counter_part.end());
    // Removed, Internalized, Not-Self traded
    message.push_back(0b01101000);
    ASSERT_EQ(31, message.size());

    ExecutionDetails details = decode_executed_order(message);

    ASSERT_EQ(0, strcmp("12345678912345", details.cl_ord_id));
    ASSERT_EQ(4831, details.match_number);
    ASSERT_EQ(100000, details.filled_volume);
    ASSERT_DOUBLE_EQ(14.746, details.price);
    ASSERT_EQ(0, strcmp("BofA", details.counterpart));
    ASSERT_EQ(LiquidityIndicator::Removed, details.liquidity_indicator);
    ASSERT_TRUE(details.internalized);
    ASSERT_FALSE(details.self_trade);
}

TEST(ExecutedOrderTest, decode_sgen_executed_order)
{
    std::vector<unsigned char> message;
    // '00042000000042'
    std::vector<unsigned char> orderId = { '0', '0', '0', '4', '2', '0', '0', '0', '0', '0', '0', '0', '4', '2'};
    message.insert(message.end(), orderId.begin(), orderId.end());
    // 74847
    std::vector<unsigned char> match_number = { 0x00, 0x01, 0x24, 0x5f };
    message.insert(message.end(), match_number.begin(), match_number.end());
    // 450000
    std::vector<unsigned char> filled_volume = { 0x00, 0x06, 0xdd, 0xd0 };
    message.insert(message.end(), filled_volume.begin(), filled_volume.end());
    // 1909.2754
    std::vector<unsigned char> fill_price = { 0x01, 0x23, 0x55, 0x12 };
    message.insert(message.end(), fill_price.begin(), fill_price.end());
    // SGen
    std::vector<unsigned char> counter_part = { 'S', 'G', 'e', 'n' };
    message.insert(message.end(), counter_part.begin(), counter_part.end());
    // Added, Non Internalized, Self-traded
    message.push_back(0b11000000);
    ASSERT_EQ(31, message.size());

    ExecutionDetails details = decode_executed_order(message);

    ASSERT_EQ(0, strcmp("00042000000042", details.cl_ord_id));
    ASSERT_EQ(74847, details.match_number);
    ASSERT_EQ(450000, details.filled_volume);
    ASSERT_DOUBLE_EQ(1909.2754, details.price);
    ASSERT_EQ(0, strcmp("SGen", details.counterpart));
    ASSERT_EQ(LiquidityIndicator::Added, details.liquidity_indicator);
    ASSERT_FALSE(details.internalized);
    ASSERT_TRUE(details.self_trade);
}