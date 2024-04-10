#ifndef THREADSIGNAL
#define THREADSIGNAL

#include "ui/menuwindow.h"
#include <QObject>
#include <QThread>
#include "../external_libs/concurrent_queue.hpp"
#include <String>
#include <iostream>
#include <windows.h>

using lime62::concurrent_queue;

class Worker : public QObject
{
    Q_OBJECT

public slots:
    void doWork(concurrent_queue<std::string>* q);

signals:
    void resultat(const std::string);
};



class Controller : public QObject
{
    Q_OBJECT
        QThread workerThread;
public:
    Controller(concurrent_queue<std::string>* q);
    ~Controller();

public slots:
    void handleResultat(const std::string);

signals:
    void operate(concurrent_queue<std::string>* q);

private:
    std::string Mode;
    int numRows;
    int numCols;


    bool mode = false;
    bool tailleEnX = false;
    bool tailleEnY = false;
    bool Joueur1Bateau = false;
    bool Joueur2Bateau = false;
    bool JoueurTir = false;
    bool Elevation = false;
    bool Angle = false;
    bool Puissance = false;
    bool shake = false;
    bool fin = false;
    GameWindow* game;
};

#endif