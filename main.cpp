#include "ui/menuwindow.h"
#include <QApplication>
#include <windows.h>

// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "lib_jeu/jeu.h"
#include "manette/manette.h"
#include "external_libs/concurrent_queue.hpp"
#include <fstream>
#include <thread> 

using lime62::concurrent_queue;

int lejeu(concurrent_queue<std::string>* queueManette, concurrent_queue<std::string>* queueAppli);
int manetteFn(concurrent_queue<std::string>* q);
int Appli(concurrent_queue<std::string>* q);

int main(int argc, char* argv[])
{

    concurrent_queue<std::string> qManetteJeu;
    concurrent_queue<std::string> qAppliJeu;
    
    //il y aurait dequoi à patenter si on veut que les deux puisse print du serial, je le fais pas car c'est pas le but final du jeu
    

    std::thread t1(lejeu, &qManetteJeu, &qAppliJeu);
    std::thread t2(manetteFn, &qManetteJeu);
    Appli(&qAppliJeu);

    t1.join();
    t2.join();

    return 0;
}

int Appli(concurrent_queue<std::string>* q) {

    while (true)
    {
        
        Sleep(100);
    }

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
    jeu.afficherStartUp(std::cout);
    while ((reponse = jeu.menuStartUp(std::cout, std::cin)) == INCORRECT) {}
    if (reponse == QUITTER)
        exit(0);
    //Le joueur commence
    do {
        //jeu.menuReglage(std::cout, myFile);
        jeu.menuReglage(std::cout, std::cin);
        jeu.ajouterJoueur();
        jeu.ajouterJoueur();
        //jeu.menuInitJoueur(std::cout, myFile, jeu.getJoueur(0)); // Joueur 1 place ses bateaux
        jeu.menuInitJoueur(std::cout, std::cin, jeu.getJoueur(0)); // Joueur 1 place ses bateaux
        //jeu.menuInitJoueur(std::cout, myFile, jeu.getJoueur(1)); // Joueur 2 place ses bateaux
        jeu.menuInitJoueur(std::cout, std::cin, jeu.getJoueur(1)); // Joueur 2 place ses bateaux
        switch (jeu.getMode()) {
        case MODE_NORMAL:
            jeu.menuJeuNormal(std::cout, std::cin);
            break;
        case MODE_RAFALE:
            jeu.menuJeuRafale(std::cout, std::cin);
            break;
        case MODE_STRATEGIE:
            jeu.menuJeuStrategique(std::cout, std::cin);
            break;
        }
        jeu.afficherFin(std::cout);
        while ((reponse = jeu.menuFin(std::cout, std::cin)) == INCORRECT) {}
        if (reponse == QUITTER)
            exit(0);
    } while (true);

    exit(0);
    return 0;
}