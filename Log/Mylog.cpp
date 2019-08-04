#include "MyLog.h"
#include "log4cpp/Category.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/OstreamAppender.hh"

Mylog* Mylog::m_log = nullptr;

Mylog::Mylog()
{}

Mylog::~Mylog()
{}

Mylog* Mylog::getInstance()
{
    if(m_log == nullptr)
    {
        m_log = new Mylog();
    }
    return m_log;
}

void Mylog::init(std::string logFileName)
{
    log4cpp::Appender *appender = new log4cpp::FileAppender("root",logFileName);

    log4cpp::PatternLayout *layout = new log4cpp::PatternLayout();
    layout->setConversionPattern("%d [%p] - %m %n");
    appender->setLayout(layout);

    //默认先设置为debug
    log4cpp::Category &root = log4cpp::Category::getRoot();
    root.setPriority(log4cpp::Priority::DEBUG);
    root.addAppender(appender);
}

void Mylog::setPriority(int p)
{
    log4cpp::Category& root = log4cpp::Category::getRoot();
    switch(p)
    {
    case EMERG: root.setPriority(log4cpp::Priority::EMERG);break;
    case FATAL: root.setPriority(log4cpp::Priority::FATAL);break;
    case ALERT: root.setPriority(log4cpp::Priority::ALERT);break;
    case ERROR: root.setPriority(log4cpp::Priority::ERROR);break;
    case WARN:  root.setPriority(log4cpp::Priority::WARN);break;
    case NOTICE:root.setPriority(log4cpp::Priority::NOTICE);break;
    case DEBUG: root.setPriority(log4cpp::Priority::DEBUG);break;
    default:break;
    }
}

void Mylog::log_debug(std::__cxx11::string msg)
{
    log4cpp::Category::getRoot().debug(msg);
}

void Mylog::log_warn(std::__cxx11::string msg)
{
    log4cpp::Category::getRoot().warn(msg);
}

void Mylog::log_fatal(std::__cxx11::string msg)
{
    log4cpp::Category::getRoot().fatal(msg);
}

void Mylog::log_emerg(std::__cxx11::string msg)
{
    log4cpp::Category::getRoot().emerg(msg);
}


