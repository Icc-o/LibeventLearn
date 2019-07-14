#ifndef CLIENTONE_H
#define CLIENTONE_H

#include <event2/event.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
using namespace std;

#define PORT 8889
#define SERADDR "192.168.0.2"

//使用libevent写的简单的client

class ClientOne
{
public:
    ClientOne();
    bool init();
    bool Connect();
private:

    sockaddr_in m_serAddr;
    int m_fd;

    struct event_base*  m_base;
    struct event*       ev_fd;  //读取事件
    struct event*       ev_cmd; //命令行输入事件

};

#endif // CLIENTONE_H
