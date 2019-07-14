#include "serverone.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

void socket_read_cb(int fd, short events, void *arg)
{
    char msg[1024];

    int ret = recv(fd,msg,sizeof(msg),0);
    if(ret<0)
    {
        cout<<"read failed!"<<errno<<endl;
        return;
    }
    cout<<"recv msg: "<<msg<<endl;
    char retMsg[1024] = "I recvd msg!";
    write(fd,retMsg,sizeof(retMsg));
}

void accept_cb(int fd, short events, void* arg)
{
    cout<<"accept callback!"<<endl;
    evutil_socket_t sockfd;
    struct sockaddr_in client;
    socklen_t len= sizeof(client);
    sockfd = accept(fd,(struct sockaddr*)&client, &len);
    evutil_make_socket_nonblocking(sockfd);
    cout<<"accepted a new connection"<<endl;

    struct event_base* base = (struct event_base* )arg;
    struct event *ev = event_new(NULL,-1,0,NULL,NULL);
    event_assign(ev,base,sockfd,EV_READ|EV_PERSIST, socket_read_cb, (void*)ev);
    event_add(ev,NULL);
}

ServerOne::ServerOne()
{

}


void ServerOne::init()
{
    base = event_base_new();

    m_listenfd = socket(AF_INET,SOCK_STREAM,NULL);
    if(m_listenfd == -1)
    {
        cout<<"create socket failed!"<<endl;
        return;
    }
    bzero(&m_serAddr,sizeof(m_serAddr));
    m_serAddr.sin_family = AF_INET;
    m_serAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_serAddr.sin_port = htons(8889);

    if(bind(m_listenfd,(struct sockaddr*)&m_serAddr,sizeof(m_serAddr))<0)
    {
        cout<<"bind error!"<<errno<<endl;
        evutil_closesocket(m_listenfd);
        return;
    }

    if(listen(m_listenfd,10)<0)
    {
        cout<<"listen error!"<<errno<<endl;
        evutil_closesocket(m_listenfd);
        return;
    }
    evutil_make_socket_nonblocking(m_listenfd);
    ev_listen = event_new(base,m_listenfd,EV_READ|EV_PERSIST,accept_cb,base);
    event_add(ev_listen,NULL);
    event_base_dispatch(base);
}
