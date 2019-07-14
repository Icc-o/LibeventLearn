#ifndef SERVERTOW_H
#define SERVERTOW_H
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <iostream>
using namespace std;

//使用eventbuffer的服务器



class ServerTow
{
public:
    ServerTow();

    void init();

private:
    event_base* m_base;
    evconnlistener* m_listener;

    bufferevent* buffer;
};

#endif // SERVERTOW_H
