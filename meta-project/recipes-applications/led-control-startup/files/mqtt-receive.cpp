#include "mqtt-receive.hpp"

callback::callback(std::string SERVER_ADDRESS, std::string CLIENT_ID, std::string TOPIC, int QOS) : SERVER_ADDRESS(SERVER_ADDRESS),
                                                                                                    CLIENT_ID(CLIENT_ID),
                                                                                                    TOPIC(TOPIC),
                                                                                                    QOS(QOS)
{
}
void callback::message_arrived(mqtt::const_message_ptr msg)
{
    std::cout << "Received message: " << msg->get_payload_str() << std::endl;
    this->Message_Arrived = msg->get_payload_str();

    std::array<int, 5> array;
    array = m_parse_strig.parseStringToArray(msg->get_payload_str());
    for (int i = 0; i < 5; i++)
    {
        m_led_control.Led_Change_Value(static_cast<LED_NUMBER>(i), static_cast<LED_VALUE>(array[i]));
        std::cout << "index : " << i << " is : " << array[i] << std::endl;
    }
}
std::string callback::get_Server_address(void)
{
    return this->SERVER_ADDRESS;
}
std::string callback::get_Client_Id(void)
{
    return this->CLIENT_ID;
}
std::string callback::get_Topic(void)
{
    return this->TOPIC;
}
int callback::get_QOS(void)
{
    return this->QOS;
}
std::string callback::get_Message_Arrived(void)
{
    return this->Message_Arrived;
}

callback::~callback()
{
}
