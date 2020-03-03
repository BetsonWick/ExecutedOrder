![OUCH Executed Order](https://github.com/itiviti-cpp-master/ouch-executed-order/workflows/OUCH%20Executed%20Order/badge.svg?branch=master)
# Декодирование сообщения ExecutedOrder
## Новый протокол!
В примере на лекции мы познакомились с протоколом BOE, используемом преимущественно на торговых площадках, принадлежащих бирже CBOE.
В этом задании вам предлагается познакомиться с ещё одним протоколом - OUCH, используемом более широко (в разных вариациях), однако
мы сосредоточимся на его варианте, используемом на площадках Nasdaq Nordic (INET), объединяюищх скандинавские биржи.

Существенное отличие: числа кодируются в big endian формате.

## Идея
Когда какой-то заказ исполняется на бирже, то есть обнаруживается встречный заказ и биржа регистрирует сделку, участник, отправивший
заказ, получает уведомление о свершившейся сделке - исполнение заказа, order execution.
Заказ может быть исполнен полностью или частично, по указанной в нём цене или по более лучшей.

## Задание
Требуется реализовать декодер для сообщения ExecutedOrder (см. [protocol
specifications](https://github.com/itiviti-cpp-master/syllabus/wiki/files/doc/BATS_Europe_BOE2_Specification.pdf)) имеющий следующий интерфейс:
```cpp
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

ExecutionDetails decode_executed_order(const std::vector<unsigned char> & message)
{
    ExecutionDetails exec_details;
    // fill exec_details fields
    return exec_details;
}
```

Требуемые поля:
* Order Token -> cl_ord_id
* Executed Quantity -> filled_volume
* Execution Price -> price
* Match Number -> match_number
* Contra Firm -> counterpart
* Liquidity Attributes -> liquidity_indicator, internalized, self_trade
