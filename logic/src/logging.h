#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <list>

#include <string>
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdio.h>

inline std::string NowTime();

class handler
{
public:
    explicit handler();
    explicit handler(std::string fn);
    virtual ~handler();
    void setStream(std::string fn);
    virtual void write(std::string msg);

protected:
    std::ofstream ofs;
};

class logging
{
public:
    logging();
    logging(handler *h);
    ~logging();
    void setHandler(handler *newHandler);
    void info(std::string message);
private:
    handler* myHandler;
};

struct rootLogger
{
    static void setHandler(handler *newHandler);
    static void info(std::string message);
private:
    static logging log;
};

#ifndef INFO
#define INFO(message) rootLogger::info(message);
#endif

#ifndef SET_LOGGING_HANDLER
#define SET_LOGGING_HANDLER(newHandler) rootLogger::setHandler(newHandler);
#endif

#endif // LOGGING_H
