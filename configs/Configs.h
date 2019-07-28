#ifndef CONFIGS_H_
#define CONFIGS_H_

#include "third-party/pugixml.hpp"

//服务器配置信息、

class IConfigs
{
public:
    IConfigs();
    virtual ~IConfigs();
    /**
     * @brief getInstance  使用单例
     * @return
     */
    //virtual IConfigs* getInstance()=0;
    /**
     * @brief getMsgFromXmlNode 从xml节点获取到配置信息
     * @param node
     */
    virtual void getMsgFromXmlNode(const pugi::xml_node& node)=0;
};

class ServerConfigs:public IConfigs
{
public:
    static IConfigs* getInstance();
    virtual void getMsgFromXmlNode(const pugi::xml_node& node);
    std::string getAddress()const;
    int getPort()const;

private:
    ServerConfigs();
    ~ServerConfigs();
    std::string m_address;
    int port;
    static ServerConfigs* m_pInstance;
};

class ClientConfigs:public IConfigs
{
public:
    static IConfigs* getInstance();
    virtual void getMsgFromXmlNode(const pugi::xml_node &node);
private:
    ClientConfigs();
    ~ClientConfigs();
    std::string m_address;
    static ClientConfigs* m_pInstance;
};

#endif





