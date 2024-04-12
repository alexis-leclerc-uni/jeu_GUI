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
