#include "serverthree.h"
#include "configs/protos/User.pb.h"
#include "configs/Configs.h"
#include "Log/MyLog.h"

//收到消息之后发送一个user给对方
void socket_read_cb3(bufferevent* bev, void* arg)
{
    char msg[4096];
    size_t len = bufferevent_read(bev,msg,sizeof(msg));
    msg[len] = '\0';
    std::cout<<"recv : "<<msg<<" from "<<bufferevent_getfd(bev)<<std::endl;

    char sendm[1024];
    User::User user;
    user.set_name("jack");
    user.set_id(123);
    user.set_sex(true);
    user.SerializeToArray(sendm,1024);
    bufferevent_write(bev,&sendm,sizeof(sendm));

}

void socket_event_cb3(bufferevent* bev, short event, void* arg)
{
    if(event & BEV_EVENT_EOF)
    {
        std::cout<<"close connection "<<bufferevent_getfd(bev)<<std::endl;
    }
    else if(event & BEV_EVENT_ERROR)
    {
        std::cout<<"error "<<std::endl;
    }
    bufferevent_free(bev);
}

void listener_cb3(evconnlistener* listener, evutil_socket_t fd, sockaddr* sock, int len,void* arg)
{
    std::cout<<"new connection: "<<fd<<std::endl;
    event_base *base = (event_base*)arg;
    bufferevent* buffer = bufferevent_socket_new(base, fd,BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(buffer,socket_read_cb3, NULL,socket_event_cb3,nullptr);
    bufferevent_enable(buffer, EV_READ|EV_PERSIST);
}

ServerThree::ServerThree()
{
}


void ServerThree::init()
{
    m_base = event_base_new();
    if(m_base == nullptr)
    {
        return;
    }
    sockaddr_in serAddr;
    memset(&serAddr, 0,sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serAddr.sin_port = htons(static_cast<ServerConfigs*>(ServerConfigs::getInstance())->getPort());

    m_listener = evconnlistener_new_bind(m_base,listener_cb3, m_base,
                                         LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE,
                                         10,
                                         (sockaddr*)&serAddr,
                                         sizeof(sockaddr_in));
    LOG_DBG("server init finished!");
    event_base_dispatch(m_base);
}
