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
    if (resultat == "fin") {

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
    else if (!mode) {
        Mode = resultat;
        mode = true;
        //Update en envoyant un signal
    }
    else if (!tailleEnX) {
        if (resultat == "confirm") 
            tailleEnX = true;
        else
            numCols = std::stoi(resultat);
            //Update en envoyant un signal
    }
    else if (!tailleEnY) {
        if (resultat == "confirm") {
            tailleEnY = true;

        }
        else
            numRows = std::stoi(resultat);
            //Update en envoyant un signal
    }
    else if (!Joueur1Bateau) {
        if (resultat == "Joueur1") {
            Joueur1Bateau = true;
            //Update en envoyant un signal

        }
        else if (resultat == "confirm") {
            //placer le bateau

        }
        else {
            // changement des coordonnées
            if (resultat == "N") {
                // Vers le Nord

            }
            else if (resultat == "E") {
                //Vers l'Est

            }
            else if (resultat == "S") {
                //Vers le Sud

            }
            else if (resultat == "O") {
                //Vers l'Ouest

            }
        }

        
    }
    else if (!Joueur2Bateau) {
        if (resultat == "Joueur2") {
            Joueur2Bateau = true;
            //Update en envoyant un signal

        }
        else if (resultat == "confirm") {
            //placer le bateau

        }
        else {
            // changement des coordonnées
            if (resultat == "N") {
                // Vers le Nord

            }
            else if (resultat == "E") {
                //Vers l'Est

            }
            else if (resultat == "S") {
                //Vers le Sud

            }
            else if (resultat == "O") {
                //Vers l'Ouest

            }
        }


    }
    else if (!JoueurTir) {
        //Update qui joue

        JoueurTir = true;
    }
    else if (!Elevation) {
        if (resultat == "confirmElevation") {
            Elevation = true;
            //Envoyer la confirmation

        }
        else {
            //Update en envoyant un signal

        }

    }
    else if (!Angle) {
        if (resultat == "confirmAngle") {
            Angle = true;
            //Envoyer la confirmation

        }
        else {
            //Update en envoyant un signal

        }
    }
    else if (!Puissance) {
        if (resultat == "confirmPuissance") {
            Puissance = true;
            //Envoyer la confirmation

        }
        else {
            //Update en envoyant un signal

        }
    }
    else if (!shake) {

        JoueurTir = false; //le jeu continu
        Elevation = false;
        Angle = false;
        Puissance = false;
    }
}