#include "ui/menuwindow.h"
#include <QApplication>
#include <windows.h>
#include "ui/threadSignal.h"

// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "lib_jeu/jeu_App.h"
#include "manette/manette.h"
#include "external_libs/concurrent_queue.hpp"
#include <fstream>
#include <thread> 

using lime62::concurrent_queue;

int lejeu(concurrent_queue<std::string>* queueManette, concurrent_queue<std::string>* queueAppli);
int manetteFn(concurrent_queue<std::string>* q);

concurrent_queue<std::string> qManetteJeu;
concurrent_queue<std::string> qAppliJeu;



int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    //il y aurait dequoi à patenter si on veut que les deux puisse print du serial, je le fais pas car c'est pas le but final du jeu
    Controller Appli = Controller(&qAppliJeu);
    std::thread t1(lejeu, &qManetteJeu, &qAppliJeu);
    std::thread t2(manetteFn, &qManetteJeu);
    MenuWindow w;
    GameWindow g;


    QObject::connect(&Appli, &Controller::sendMode, &w, &MenuWindow::receiveMode);
    QObject::connect(&Appli, &Controller::sendTailleX, &w, &MenuWindow::receiveTailleX);
    QObject::connect(&Appli, &Controller::sendTailleY, &w, &MenuWindow::receiveTailleY);
    QObject::connect(&Appli, &Controller::sendStartGameJeu, &w, &MenuWindow::receiveStartGameJeu);
    QObject::connect(&Appli, &Controller::changeCoordsSignal, &g, &GameWindow::ChangeCoordsSlot);
    QObject::connect(&Appli, &Controller::sendTailleBateau, &g, &GameWindow::receiveTailleBateau);
    QObject::connect(&Appli, &Controller::sendPlaceBateau, &g, &GameWindow::receivePlaceBateau);
    QObject::connect(&Appli, &Controller::sendRotateBateau, &g, &GameWindow::receiveRotateBateau);
    QObject::connect(&Appli, &Controller::sendJoueur1Fini, &g, &GameWindow::receiveJoueur1Fini);
    QObject::connect(&Appli, &Controller::sendJoueur2Fini, &g, &GameWindow::receiveJoueur2Fini);
    QObject::connect(&Appli, &Controller::sendJoueur, &g, &GameWindow::receiveJoueur);
    QObject::connect(&Appli, &Controller::sendCarte, &g, &GameWindow::receiveCarte);
    QObject::connect(&Appli, &Controller::sendElevation, &g, &GameWindow::receiveElevation);
    QObject::connect(&Appli, &Controller::sendElevationConfirmation, &g, &GameWindow::receiveElevationConfirmation);
    QObject::connect(&Appli, &Controller::sendAngle, &g, &GameWindow::receiveAngle);
    QObject::connect(&Appli, &Controller::sendAngleConfirmation, &g, &GameWindow::receiveAngleConfirmation);
    QObject::connect(&Appli, &Controller::sendPuissance, &g, &GameWindow::receivePuissance);
    QObject::connect(&Appli, &Controller::sendPuissanceConfirmation, &g, &GameWindow::receivePuissanceConfirmation);
    QObject::connect(&w, &MenuWindow::sendStartGame, &g, &GameWindow::receiveStartGame);
    

    a.exec();
    t1.join();
    t2.join();

    return 0; 
}


int manetteFn(concurrent_queue<std::string>* q) {
    const std::string& port = "COM3";
    Manette* manette = new Manette(port, ref(q));
    return 0;
}


int lejeu(concurrent_queue<std::string>* queueManette, concurrent_queue<std::string>* queueAppli)
{
    //std::cout<<sizeof(q);
    Jeu jeu(queueManette, queueAppli);
    int reponse;
    /*
    jeu.afficherStartUp(std::cout);
    while ((reponse = jeu.menuStartUp(std::cout, std::cin)) == INCORRECT) {}
    if (reponse == QUITTER)
        exit(0);
    */
    //Le joueur commence
    do {
        //jeu.menuReglage(std::cout, myFile);
        jeu.menuReglage(std::cout, std::cin);
        jeu.ajouterJoueur();
        jeu.ajouterJoueur();
        
        //jeu.menuInitJoueur(std::cout, myFile, jeu.getJoueur(0)); // Joueur 1 place ses bateaux
        jeu.menuInitJoueur(std::cout, std::cin, jeu.getJoueur(0)); // Joueur 1 place ses bateaux
        queueAppli->push("Joueur1");
        
        //jeu.menuInitJoueur(std::cout, myFile, jeu.getJoueur(1)); // Joueur 2 place ses bateaux
        jeu.menuInitJoueur(std::cout, std::cin, jeu.getJoueur(1)); // Joueur 2 place ses bateaux
        queueAppli->push("Joueur2");
        
        switch (jeu.getMode()) {
        case MODE_NORMAL:
            //queueAppli->push("normal");
            jeu.menuJeuNormal(std::cout, std::cin);
            break;
        case MODE_RAFALE:
            //queueAppli->push("rafale");
            jeu.menuJeuRafale(std::cout, std::cin);
            break;
        case MODE_STRATEGIE:
            //queueAppli->push("strategique");
            jeu.menuJeuStrategique(std::cout, std::cin);
            break;
        }
        jeu.afficherFin(std::cout);
        queueAppli->push("fin");
        while ((reponse = jeu.menuFin(std::cout, std::cin)) == INCORRECT) {}
        if (reponse == QUITTER)
            exit(0);
    } while (true);

    exit(0);
    return 0;
}