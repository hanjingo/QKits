#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <mutex>

#include <QCoreApplication>
#include <QStandardPaths>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QDir>

#include "log4qt/logger.h"
#include "log4qt/logmanager.h"
#include "log4qt/propertyconfigurator.h"

namespace libqt
{

class logger
{
public:
    logger() = delete;
    logger(const logger&) = delete;
    logger& operator=(const logger&) = delete;

    logger(Log4Qt::Logger* base) : base_{base} {}

    ~logger()
    {
    }

    static logger* instance()
    {
        static std::once_flag logOnce;
        static logger* pLogInst_;
        std::call_once(logOnce, [&](){
            pLogInst_ = new logger(Log4Qt::Logger::rootLogger());
        });

        return pLogInst_;
    }

    static bool configure(const QString &fpath)
    {
        if (fpath.isEmpty() || !QFile::exists(fpath))
        {
            return false;
        }

        return Log4Qt::PropertyConfigurator::configure(fpath);
    }

    static void setHandleQtMessages(bool isHandle)
    {
        Log4Qt::LogManager::setHandleQtMessages(isHandle);
    }

public:
    template<typename... Args>
    inline void trace(const char* fmt, Args&& ... args)
    {
        base_->trace(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void debug(const char* fmt, Args&& ... args)
    {
        base_->debug(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void info(const char* fmt, Args&& ... args)
    {
        base_->info(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void warn(const char* fmt, Args&& ... args)
    {
        base_->warn(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void error(const char* fmt, Args&& ... args)
    {
        base_->error(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void fatal(const char* fmt, Args&& ... args)
    {
        base_->fatal(fmt, std::forward<Args>(args)...);
    }

private:
    Log4Qt::Logger *base_;
};

}

#define LOG_DEBUG(...) \
    libqt::logger::instance()->debug(__VA_ARGS__)

#define LOG_INFO(...) \
    libqt::logger::instance()->info(__VA_ARGS__)

#define LOG_WARN(...) \
    libqt::logger::instance()->warn(__VA_ARGS__)

#define LOG_ERROR(...) \
    libqt::logger::instance()->error(__VA_ARGS__)

#define LOG_FATAL(...) \
    libqt::logger::instance()->fatal(__VA_ARGS__)

#endif
