#include "Configs.h"
#include <iostream>
//静态成员需要申明
ServerConfigs* ServerConfigs::m_pInstance = nullptr;
ClientConfigs* ClientConfigs::m_pInstance = nullptr;

IConfigs::IConfigs()
{}

IConfigs::~IConfigs()
{}

ServerConfigs::ServerConfigs()
{
    m_pInstance = nullptr;
}

ServerConfigs::~ServerConfigs()
{}

IConfigs* ServerConfigs::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new ServerConfigs();
    }
    return m_pInstance;
}

void ServerConfigs::getMsgFromXmlNode(const pugi::xml_node &node)
{
    m_address = node.child("ip").text().as_string();
    port = node.child("port").text().as_int();
    std::cout<<"ip: "<<m_address<<" port:"<<port<<std::endl;
}

std::string ServerConfigs::getAddress()const
{
    return m_address;
}

int ServerConfigs::getPort()const
{
    return port;
}



ClientConfigs::ClientConfigs()
{}

ClientConfigs::~ClientConfigs()
{}

IConfigs* ClientConfigs::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new ClientConfigs();
    }
    return m_pInstance;
}

void ClientConfigs::getMsgFromXmlNode(const pugi::xml_node &node)
{
    m_address = node.child("ip").text().as_string();
}
