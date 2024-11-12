#pragma once
#include <iostream>
#include <fstream>
enum class LED_NUMBER : unsigned char
{
    LED2 = 0,
    LED3,
    LED4,
    LED17,
    LED27
};
enum class LED_VALUE : unsigned char
{
    LED_OFF = 0,
    LED_ON

};
class Led_Control
{
private:
    std::fstream m_fd;
    std::string Led1_path{"/dev/led0"};
    std::string Led2_path{"/dev/led1"};
    std::string Led3_path{"/dev/led2"};
    std::string Led4_path{"/dev/led3"};
    std::string Led5_path{"/dev/led4"};

public:
    Led_Control() = default;
    void Led_Change_Value(LED_NUMBER led_number, LED_VALUE led_value);
    ~Led_Control() = default;
};
