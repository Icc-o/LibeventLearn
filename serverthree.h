#ifndef SERVERTHREE_H
#define SERVERTHREE_H
#include "configs/protos/User.pb.h"
#include "event2/event.h"
#include "event2/listener.h"
#include "event2/bufferevent.h"


class ServerThree
{
public:
    ServerThree();
    ~ServerThree(){}
    void init();

private:
    event_base* m_base;
    evconnlistener* m_listener;
    bufferevent* m_buffer;

    User::User m_user;
};

#endif // SERVERTHREE_H
