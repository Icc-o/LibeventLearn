#include "servertow.h"
#include <string.h>
void socket_read_cb(bufferevent* bev, void* arg)
{
    char msg[4096];
    size_t len = bufferevent_read(bev,msg,sizeof(msg));
    msg[len] = '\0';
    cout<<"recv: "<<msg<<" from:"<<bufferevent_getfd(bev)<<endl;
    char retmsg[] = "This is a reply from server";
    bufferevent_write(bev,retmsg,strlen(msg));
}

void socket_event_cb(bufferevent* bev,short event, void* arg)
{
    if(event&BEV_EVENT_EOF)
    {
        //断开连接请求
        cout<<"connection close: "<<bufferevent_getfd(bev)<<endl;
    }
    else if(event | BEV_EVENT_ERROR)
    {
        cout<<"some other error"<<endl;
    }
    bufferevent_free(bev);
}

void listener_cb(evconnlistener* listener, evutil_socket_t fd, sockaddr *sock, int socklen, void* arg)
{
   cout<<"new connection"<<fd<<endl;
   event_base* base = (event_base*)arg;
   bufferevent* buffer = bufferevent_socket_new(base,fd,BEV_OPT_CLOSE_ON_FREE);
   bufferevent_setcb(buffer,socket_read_cb,NULL,socket_event_cb,NULL);
   bufferevent_enable(buffer,EV_READ|EV_PERSIST);
}

ServerTow::ServerTow()
{

}

void ServerTow::init()
{
    m_base = event_base_new();
    if(m_base == nullptr)
    {
        return;
    }

    sockaddr_in sin;
    memset(&sin,0,sizeof(sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8889);

    m_listener = evconnlistener_new_bind(m_base,listener_cb,m_base,LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE,10,(sockaddr*)&sin,sizeof(sockaddr_in));

    event_base_dispatch(m_base);
}
