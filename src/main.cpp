#include <iostream>
#include <iomanip>

#include "requests.h"

namespace {

template <class T>
void print_binary(const T & x)
{
    size_t i = 0;
    const auto print8 = [&x, &i] () {
        for (size_t j = 0; i < x.size() && j < 8; ++i, ++j) {
            if (j != 0) {
                std::cout << ' ';
            }
            std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(x[i]);
        }
    };
    while (i < x.size()) {
        print8();
        if (i < x.size()) {
            std::cout << "  ";
            print8();
        }
        std::cout << std::endl;
    }
}

} // anonymous namespace

int main(int argc, char** argv)
{
    std::vector<unsigned char> message;
    print_binary(message);
    const ExecutionDetails executedOrder = decode_executed_order(message);

    return 0;
}