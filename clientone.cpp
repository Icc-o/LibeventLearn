#include "clientone.h"
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

void socket_read_cb1(int fd, short events, void* arg);
void cmd_msg_cb(int fd, short events, void* arg);

ClientOne::ClientOne()
{

}

bool ClientOne::init()
{
    m_base = event_base_new();

    m_fd = socket(AF_INET,SOCK_STREAM,NULL);
    if(m_fd == -1)
    {
        cout<<"create socket error!"<<endl;
        return -1;
    }

    m_serAddr.sin_family = AF_INET;
    m_serAddr.sin_port = PORT;
    if(inet_aton(SERADDR,&m_serAddr.sin_addr) == 0)
    {
        cout<<"error IP"<<endl;
        return -1;
    }
    return 0;
}

bool ClientOne::Connect()
{
    ev_fd = event_new(m_base, m_fd,EV_READ|EV_PERSIST,
                      socket_read_cb1, NULL);
    event_add(ev_fd,NULL);
    if(connect(m_fd,(struct sockaddr*)&m_serAddr, sizeof(m_serAddr)) == -1)
    {
        cout<<"connect failed! "<<errno<<endl;
        return -1;
    }
    evutil_make_socket_nonblocking(m_fd);

    ev_cmd = event_new(m_base, STDIN_FILENO,EV_READ|EV_PERSIST,
                       cmd_msg_cb,(void*)&m_fd);
    event_add(ev_cmd,NULL);

    event_base_dispatch(m_base);

    return 0;
}

void socket_read_cb1(int fd, short events, void *arg)
{
    char msg[1024];
    int len = read(fd, msg, sizeof(msg)-1);
    if(len<0)
    {
        cout<<"read error!"<<endl;
        return ;
    }
    cout<<"recv msg: "<<msg<<endl;
}

void cmd_msg_cb(int fd, short events, void *arg)
{
    char msg[1024];
    int ret = read(fd,msg,sizeof(msg));
    if(ret<0)
    {
        cout<<"read cmd failed"<<endl;
        return;
    }
    int sockfd = *((int*)arg);
    write(sockfd,msg,ret);
}
