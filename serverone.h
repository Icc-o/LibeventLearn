#ifndef SERVERONE_H
#define SERVERONE_H
#include <event2/event.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
using namespace std;

//�򵥵�libevent server
//��������¼�


class ServerOne
{
public:
    ServerOne();

    void init();

private:
    int m_listenfd;
    struct sockaddr_in m_serAddr, m_cliAddr;

    struct event_base*  base;
    struct event*       ev_listen;

};

#endif // SERVERONE_H
