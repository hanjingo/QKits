#include <QCoreApplication>
#include <QThread>
#include <QDebug>

#include "Logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    libqt::logger::configure(QCoreApplication::applicationDirPath() + "/log.conf");
    libqt::logger::setHandleQtMessages(true);
    libqt::logger * log = libqt::logger::instance();
    int nMax = 100000;
    for(int n = 0; n < nMax; ++n)
    {

//        log->debug("debug");
//        log->info("info");
//        log->warn("warn");
//        log->error("error");
//        log->fatal("fatal");

//        qDebug() << "qDebug";
//        qInfo() << "qInfo";
//        qWarning() << "qWarning";
//        qCritical() << "qCritical";

        LOG_DEBUG("DEBUG");
        LOG_INFO("INFO");
        LOG_WARN("WARN");
        LOG_ERROR("ERROR");
        LOG_FATAL("FATAL");

        QThread::msleep(100);
    }

    return a.exec();
}
