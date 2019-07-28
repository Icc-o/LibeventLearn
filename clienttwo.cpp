#include "clienttwo.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>

using namespace std;

void recv_sock_cb(int fd, short events, void* arg)
{

}

void buffer_read_cb(bufferevent* bev, void*arg)
{
    char recvMsg[4096];
    size_t len = bufferevent_read(bev,recvMsg,sizeof(recvMsg));
    recvMsg[len] = '\0';   //½áÊø·û

}

void cmd_read_cb(int fd,short events,void* arg)
{
    char cmdMsg[1024];
    size_t len = read(fd,cmdMsg,sizeof(cmdMsg));
    if(len<0)
    {
        cout<<"get input failed!"<<endl;
        return;
    }
    int sockfd = *((int *)arg);
    write(sockfd,cmdMsg,strlen(cmdMsg));

}

ClientTwo::ClientTwo()
{

}


void ClientTwo::init()
{
    fd = socket(PF_INET,SOCK_STREAM,NULL);
    m_base = event_base_new();
}

void ClientTwo::Connect()
{
    sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(8889);
    if(inet_aton("192.168.0.2",&serAddr.sin_addr)==0)
    {
        cout<<"IP error!"<<endl;
        return;
    }

    if(connect(fd,(struct sockaddr*)&serAddr,sizeof(serAddr)) == -1)
    {
        cout<<"connect failed!"<<endl;
        return;
    }

    evutil_make_socket_nonblocking(fd);

    bufferevent *buffer = bufferevent_socket_new(m_base,fd,BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(buffer,buffer_read_cb,NULL,NULL,NULL);
    bufferevent_enable(buffer,EV_READ|EV_PERSIST);

    char msg[] = "This message is from client!";
    bufferevent_write(buffer,msg,strlen(msg));


    event *ev_cmd = event_new(m_base,STDIN_FILENO,EV_READ|EV_PERSIST,cmd_read_cb,&fd);
    event_add(ev_cmd,NULL);

    event_base_dispatch(m_base);
}
