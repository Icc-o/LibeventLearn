//封装一个log4cpp的类，用来写日志

#ifndef _MYLOG_H_
#define _MYLOG_H_

#include <string>
#define LOG_DBG(msg) Mylog::getInstance()->log_debug(msg+std::string(__FILE__)+std::string(__LINE__));
#define LOG_WARN(msg) Mylog::getInstance()->log_warn(msg+std::string(__FILE__)+std::string(__LINE__));
#define LOG_FATAL(msg) Mylog::getInstance()->log_fatal(msg+std::string(__FILE__)+std::string(__LINE__));
#define LOG_EMERG(msg) Mylog::getInstance()->log_emerg(msg+std::string(__FILE__)+std::string(__LINE__));
class Mylog
{
public:
    //几个日志的优先级
    enum{EMERG,
         FATAL,
         ALERT,
         ERROR,
         WARN,
         NOTICE,
         DEBUG
        }LogPrio;

    Mylog();
    ~Mylog();

    static Mylog* getInstance();

    //初始化
    void init(std::string logFileName);

    //设置输出等级
    void setPriority(int p);

    //一些消息输出函数
    void log_debug(std::string msg);
    void log_warn(std::string msg);
    void log_fatal(std::string msg);
    void log_emerg(std::string msg);
private:
    static Mylog* m_log;
};

#endif
