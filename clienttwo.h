#ifndef CLIENTTWO_H
#define CLIENTTWO_H

#include <event2/event.h>
#include <event2/bufferevent.h>

//����ͻ��˺ͷ�������Ҫʹ��eventbuffer��ʵ��

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
