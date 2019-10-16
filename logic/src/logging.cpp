#include "logging.h"

logging rootLogger::log = logging(new handler("root.log"));

logging::logging()
{
    myHandler = new handler("log.log");
    std::cout << "init" << std::endl;
}

logging::logging(handler *h)
{
    myHandler = h;
    std::cout << "init" << std::endl;
}

logging::~logging()
{
    delete myHandler;
}

void logging::info(std::string message)
{
    myHandler->write("[" + NowTime() + "] [INFO] " + message + '\n');
//    myHandler->write(message + '\n');
}

void logging::setHandler(handler *newHandler)
{
    delete myHandler;
    myHandler = newHandler;
}

handler::handler()
{
//    ofs = stdout;
}

handler::handler(std::string fn)
{
    setStream(fn);
}

handler::~handler()
{
    std::cout << "close" << std::endl;
    ofs.close();
}

void handler::setStream(std::string fn)
{
    ofs.open(fn);
}

void handler::write(std::string msg)
{
    ofs << msg;
}

void rootLogger::setHandler(handler *newHandler)
{
    log.setHandler(newHandler);
}

void rootLogger::info(std::string message)
{
    log.info(message);
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

#include <windows.h>

inline std::string NowTime()
{
    const int MAX_LEN = 200;
    char buffer[MAX_LEN];
    if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0,
            "HH':'mm':'ss", buffer, MAX_LEN) == 0)
        return "Error in NowTime()";

    char result[100] = {0};
    static DWORD first = GetTickCount();
    std::sprintf(result, "%s.%03ld", buffer, (long)(GetTickCount() - first) % 1000);
    return result;
}

#else

#include <sys/time.h>

inline std::string NowTime()
{
    char buffer[11];
    time_t t;
    time(&t);
    tm r = {};
    strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    char result[100] = {0};
    std::sprintf(result, "%s.%03ld", buffer, static_cast<long>(tv.tv_usec) / 1000);
    return result;
}

#endif //WIN32
