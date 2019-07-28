#ifndef CLIENTTHREE_H
#define CLIENTTHREE_H
#include "configs/protos/User.pb.h"
#include "event2/event.h"
#include "event2/listener.h"
#include "event2/bufferevent.h"

class ClientThree
{
public:
    ClientThree();
    ~ClientThree();
    void Connect();

private:
    int m_fd;
    bufferevent* m_bev;
    event_base* m_base;
};

#endif // CLIENTTHREE_H
