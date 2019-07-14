#ifndef CLIENTTWO_H
#define CLIENTTWO_H

#include <event2/event.h>
#include <event2/bufferevent.h>

//这个客户端和服务器需要使用eventbuffer来实现

class ClientTwo
{
public:
    ClientTwo();


    void init();
    void Connect();

private:
    int fd;
    event_base *m_base;
};

#endif // CLIENTTWO_H
