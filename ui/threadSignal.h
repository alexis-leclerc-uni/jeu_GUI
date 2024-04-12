#ifndef THREADSIGNAL
#define THREADSIGNAL

#include "controller.h"
#include "../external_libs/concurrent_queue.hpp"
using lime62::concurrent_queue;

class Worker : public QObject
{
    Q_OBJECT

public slots:
    void doWork(concurrent_queue<std::string>* q);

signals:
    void resultat(const std::string);
};


#endif