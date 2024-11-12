#pragma once

#include <iostream>
#include <mqtt/async_client.h>
#include "parse_string.hpp"
#include "led_control.hpp"
class callback : public virtual mqtt::callback
{
private:
    const std::string SERVER_ADDRESS;
    const std::string CLIENT_ID;
    const std::string TOPIC;
    const int QOS = 1;
    std::string Message_Arrived;
    Parse_string m_parse_strig;
    Led_Control m_led_control;

public:
    callback(std::string SERVER_ADDRESS, std::string CLIENT_ID, std::string TOPIC, int QOS = 1);
    std::string get_Server_address(void);
    std::string get_Client_Id(void);
    std::string get_Topic(void);
    int get_QOS(void);
    std::string get_Message_Arrived(void);

    void message_arrived(mqtt::const_message_ptr msg) override;
    ~callback();
};
