#include "threadSignal.h"

void Worker::doWork(concurrent_queue<std::string>* q) {
    std::string result;

    do {
        while (q->empty()) { //Attente du joueur pour le mode
            Sleep(50);
        };
        result = q->front();
        q->pop();
        emit resultat(result); // Envoie le mode de jeu
    } while (true);

}

Controller::Controller(concurrent_queue<std::string>* q) {
    Worker* worker = new Worker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &Controller::operate, worker, &Worker::doWork);
    connect(worker, &Worker::resultat, this, &Controller::handleResultat);
    emit operate(q);
    workerThread.start();
}

Controller::~Controller() {
    workerThread.quit();
    workerThread.wait();
}

void Controller::handleResultat(const std::string resultat) {
    if (!mode) {
        Mode = resultat;
        mode = true;
    }
    else if (!tailleEnX) {
        if (resultat == "confirm") 
            tailleEnX = true;
        else
            numCols = std::stoi(resultat);
    }
    else if (!tailleEnY) {
        if (resultat == "confirm") {
            tailleEnY = true;

        }
        else
            numRows = std::stoi(resultat);
    }
    else if (!Joueur1Bateau) {

        Joueur1Bateau = true;
    }
    else if (!Joueur2Bateau) {

        Joueur2Bateau = true;
    }
    else if (!JoueurTir) {

        JoueurTir = true;
    }
    else if (!Elevation) {

        Elevation = true;
    }
    else if (!Angle) {

        Angle = true;
    }
    else if (!Puissance) {
        Puissance = true;
    }
    else if (!shake) {

        shake = true; //Si le jeu est termnié


        JoueurTir = false; //Si le jeu continu
        Elevation = false;
        Angle = false;
        Puissance = false;
        shake = false;
    }
    else if (!fin) {

        exit(0); // Si c'est la fin

        mode = false; // Si on continue;
        tailleEnX = false;
        tailleEnX = false;
        Joueur1Bateau = false;
        Joueur2Bateau = false;
        JoueurTir = false;
        Elevation = false;
        Angle = false;
        Puissance = false;
        shake = false;
    }
}