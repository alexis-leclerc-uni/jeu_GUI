#ifndef CONTROLLER
#define CONTROLLER

#include "ui/menuwindow.h"
#include "threadSignal.h"
#include <QObject>
#include <QThread>
#include "../external_libs/concurrent_queue.hpp"
#include <String>
#include <iostream>
#include <windows.h>
#include <ui/gamewindow.h>
#include "lib_Jeu/Coordonnee.h"
#include "ui/menuwindow.h"

using lime62::concurrent_queue;

class Controller : public QObject
{
    Q_OBJECT
        QThread workerThread;
public:
    Controller (concurrent_queue<std::string>* q);
    ~Controller();

public slots:
    void handleResultat(const std::string);

signals:
    void operate(concurrent_queue<std::string>* q);
    void changeCoordsSignal(std::string resultat);
    void sendTailleX(int resultat);
    void sendTailleY(int resultat);
    void sendMode(std::string resultat);
    void sendStartTailleX(std::string texteTitre);
    void sendStartTailleY(std::string texteTitre);
    void sendEndTailleX();
    void sendEndTailleY();
    void sendStartGameJeu();
    void sendTailleBateau(int resultat);
    void sendPlaceBateau();
    void sendRotateBateau();
    void sendJoueur1Fini();
    void sendJoueur2Fini();
    void sendJoueur(std::string resultat);
    void sendCarte(std::string resultat);
    void sendElevation(int resultat);
    void sendElevationConfirmation();
    void sendAngle(int resultat);
    void sendAngleConfirmation();
    void sendPuissance(int resultat);
    void sendPuissanceConfirmation();


private:

    bool mode = false;
    bool tailleEnX = false;
    bool tailleEnY = false;
    bool Joueur1Bateau = false;
    bool Joueur2Bateau = false;
    bool JoueurTir = false;
    bool Carte = false;
    bool Elevation = false;
    bool Angle = false;
    bool Puissance = false;
    bool shake = false;
    bool fin = false;
};

#endif