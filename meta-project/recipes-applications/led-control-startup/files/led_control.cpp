#include "led_control.hpp"

void Led_Control::Led_Change_Value(LED_NUMBER led_number, LED_VALUE led_value)
{

    switch (led_number)
    {
    case LED_NUMBER::LED2:
    {
        m_fd.open(Led1_path, std::ios::out | std::ios::binary);
        break;
    }
    case LED_NUMBER::LED3:
    {
        m_fd.open(Led2_path, std::ios::out | std::ios::binary);
        break;
    }
    case LED_NUMBER::LED4:
    {
        m_fd.open(Led3_path, std::ios::out | std::ios::binary);
        break;
    }
    case LED_NUMBER::LED17:
    {
        m_fd.open(Led4_path, std::ios::out | std::ios::binary);
        break;
    }
    case LED_NUMBER::LED27:
    {
        m_fd.open(Led5_path, std::ios::out | std::ios::binary);
        break;
    }
    default:
        break;
    }

    if (led_value == LED_VALUE::LED_OFF)
    {
        m_fd.write("0\n", 2);
    }
    else if (led_value == LED_VALUE::LED_ON)
    {
        m_fd.write("1\n",2);
    }
    m_fd.close();
}
