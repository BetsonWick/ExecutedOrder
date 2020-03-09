#include "requests.h"

ExecutionDetails decode_executed_order(const std::vector<unsigned char> & message)
{
    ExecutionDetails exec_details;
    // fill exec_details fields
    static_cast<void>(message); // to suppress a warning about unused variable
    return exec_details;
}

