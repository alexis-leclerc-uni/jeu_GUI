#include "controller.h"


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
    std::cout << resultat << std::endl;
    if (resultat == "fin") {

        mode = false; // Si on continue;
        tailleEnX = false;
        tailleEnX = false;
        Joueur1Bateau = false;
        Joueur2Bateau = false;
        JoueurTir = false;
        Carte = false;
        Elevation = false;
        Angle = false;
        Puissance = false;
        shake = false;
    }
    else if (!mode) {
        mode = true;
        //Update en envoyant un signal
        emit sendMode(resultat);
        emit sendStartTailleX("Choissiser le nombre de colonne");
    }
    else if (!tailleEnX) {
        if (resultat == "confirm") {
            tailleEnX = true;
            emit sendEndTailleX();
            emit sendStartTailleY("Choissiser le nombre de ligne");
        }
        else {

            //Update en envoyant un signal
            emit sendTailleX(std::stoi(resultat));
        }
    }
    else if (!tailleEnY) {
        if (resultat == "confirm") {
            tailleEnY = true;
            //Commencer le jeu
            emit sendEndTailleY();
            emit sendStartGameJeu();
        }
        else {
            //Update en envoyant un signal
            emit sendTailleY(std::stoi(resultat));
        }
    }
    else if (!Joueur1Bateau) {
        if (resultat.substr(0, 1) == "T") {
            emit sendTailleBateau(std::stoi(resultat.substr(1, 1)));
        }
        else if (resultat == "Joueur1") {
            Joueur1Bateau = true;
            //Update en envoyant un signal
            emit sendJoueur1Fini();

        }
        else if (resultat == "confirm") {
            //placer le bateau
            emit sendPlaceBateau();

        }
        else if (resultat == "rotate") {
            //fait tourner le bateau
            emit sendRotateBateau();
        }
        else {
            emit changeCoordsSignal(resultat);
        }


    }
    else if (!Joueur2Bateau) {
        if (resultat == "Joueur2") {
            Joueur2Bateau = true;
            //Update en envoyant un signal
            emit sendJoueur2Fini();

        }
        else if (resultat == "confirm") {
            //placer le bateau
            emit sendPlaceBateau();

        }
        else {
            // changement des coordonnées
            emit changeCoordsSignal(resultat);

        }


    }
    else if (!JoueurTir) {
        //Update qui joue
        emit sendJoueur(resultat);

        JoueurTir = true;
    }
    else if (!Carte) {
        //Update la carte en l'envoyant en string (un peu sketch)
        emit sendCarte(resultat);

        Carte = true;
    }
    else if (!Elevation) {
        if (resultat == "confirmElevation") {
            Elevation = true;
            //Envoyer la confirmation
            emit sendElevationConfirmation();
        }
        else {
            //Update en envoyant un signal
            emit sendElevation(std::stoi(resultat));
        }

    }
    else if (!Angle) {
        if (resultat == "confirmAngle") {
            Angle = true;
            //Envoyer la confirmation
            emit sendAngleConfirmation();
        }
        else {
            //Update en envoyant un signal
            emit sendAngle(std::stoi(resultat));

        }
    }
    else if (!Puissance) {
        if (resultat == "confirmPuissance") {
            Puissance = true;
            //Envoyer la confirmation
            emit sendPuissanceConfirmation();
        }
        else {
            //Update en envoyant un signal
            emit sendPuissance(std::stoi(resultat));
        }
    }
    else if (!shake) {

        emit sendCarte(resultat);

        JoueurTir = false; //le jeu continu
        Elevation = false;
        Angle = false;
        Puissance = false;
        Carte = false;
    }
}