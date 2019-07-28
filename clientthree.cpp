#include "clientthree.h"
#include <iostream>
#include "configs/Configs.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

void client_three_read_cb(bufferevent* bev, void*arg)
{
    char msg[4096];
    size_t len = bufferevent_read(bev,msg,sizeof(msg));
    if(len<=0)
        std::cout<<"read size < 0"<<std::endl;
    User::User user;
    user.ParseFromArray(msg,1024);
    std::cout<<"msg: "<<msg<<std::endl;
    std::cout<<"recv msg :"<<user.name()<<" "<<user.id()<<" "<<user.sex()<<std::endl;
}

void client_three_input_cb(int fd, short events, void* arg)
{
    char sendMsg[1024];
    size_t len = read(fd,sendMsg,sizeof(sendMsg));
    if(len<0)
    {
        std::cout<<"get input failed!"<<std::endl;
        return;
    }
    int sockfd = *(int*)arg;
    write(sockfd,sendMsg,strlen(sendMsg));
}

ClientThree::ClientThree()
{

}

void ClientThree::Connect()
{
    m_base = event_base_new();
    if(m_base == nullptr)
    {
        std::cout<<"event base new failed!"<<std::endl;
        return;
    }

    std::string ip = static_cast<ServerConfigs*>(ServerConfigs::getInstance())->getAddress();
    sockaddr_in serAddr;
    bzero(&serAddr,sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(static_cast<ServerConfigs*>(ServerConfigs::getInstance())->getPort());
    if(inet_aton(ip.c_str(),&serAddr.sin_addr) == 0)
    {
        std::cout<<"invalid server address!"<<std::endl;
        return;
    }

    m_fd = socket(AF_INET,SOCK_STREAM,NULL);
    if(connect(m_fd,(sockaddr*)&serAddr,sizeof(serAddr)) == -1)
    {
        std::cout<<"connect failed"<<std::endl;
        return;
    }
    evutil_make_socket_nonblocking(m_fd);

    m_bev = bufferevent_socket_new(m_base,m_fd,BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(m_bev,client_three_read_cb,NULL,NULL,NULL);
    bufferevent_enable(m_bev,EV_READ|EV_PERSIST);

    event* ev_cmd = event_new(m_base,STDIN_FILENO,EV_READ|EV_PERSIST,client_three_input_cb,&m_fd);
    event_add(ev_cmd,nullptr);

    event_base_dispatch(m_base);
}
