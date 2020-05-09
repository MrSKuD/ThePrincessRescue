#ifndef CHRONO_H
#define CHRONO_H

#include <QGraphicsTextItem>
#include <QFont>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include "math.h"


class Chrono : public QGraphicsTextItem {
    Q_OBJECT
private:
    int msecondes = 0;
    int secondes = 0;
    int minutes = 0;
    int totalMillisecondes = 0;
    QString stringMillisecondes;
    QString stringSecondes;
    QString stringMinutes;
    QTimer* timerChrono;

public:
    Chrono(QGraphicsItem* parent = 0);
    ~Chrono();
    int getMillisecondes(); // récupère le nombre de millisecondes du temps
    int getSecondes(); // récupère le nombre de secondes du temps
    int getMinutes(); // récupère le nombre de minutes du temps
    int getTotalTimeInMs(); // récupère le temps total en millisecondes
    void printTimerInFile(QString t); // écris le score dans le fichier
    void compareTimer(QString pseudo); // compare le timer actuel avec le meilleur timer dans le fichier et appelle la fonction print si le timer actuel est meilleur
    QString recupBestTimer(); // lis le fichier "timer.txt" et récupère le meilleur timer ainsi que le pseudo correspondant
    QTimer* getTimer();

public slots:
    void updateTimer(); // incrémente le timer, l'actualise et actualise son affichage

};


#endif // CHRONO_H
