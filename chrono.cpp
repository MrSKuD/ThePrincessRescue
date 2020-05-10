/*
@Author: Enzo MOULIN
@Website: http://www.enzomoulin.com/
@Email: enzo.moulin@isen-ouest.yncrea.fr
 */

#include "chrono.h"

Chrono::Chrono(QGraphicsItem *parent) {
    this->timerChrono = new QTimer(this);
    this->timerChrono->start(10);

    setPlainText("Your timer : "+QString::number(minutes)+":"+QString::number(secondes)+":"+QString::number(msecondes)+ "\nTime to beat : " + recupBestTimer());
    setDefaultTextColor(Qt::white);
    setFont(QFont("Helvetica", 24));

    connect(timerChrono, SIGNAL(timeout()), this, SLOT(updateTimer()));
}

void Chrono::updateTimer() {
    msecondes++;
    if(msecondes == 100){
        secondes++;
        msecondes =0;
    }
    if (secondes == 60) {
        minutes++;
        secondes = 0;
    }
    totalMillisecondes++;

    setPlainText("Your timer : "+QString::number(minutes)+":"+QString::number(secondes)+":"+QString::number(msecondes)+ "\nTime to beat : " + recupBestTimer());
}

int Chrono::getMillisecondes() {
    return this->msecondes;
}

int Chrono::getSecondes() {
    return this->secondes;
}

int Chrono::getMinutes() {
    return this->minutes;
}

int Chrono::getTotalTimeInMs() {
    return totalMillisecondes*10;
}

QTimer* Chrono::getTimer() {
    return timerChrono;
}

void Chrono::compareTimer(QString pseudo) {
    QFile file("timer.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&file);
    QString score;
    QString actualScore = QString::number(getTotalTimeInMs());

    while (!flux.atEnd()) {
        score = flux.readLine();
        QStringList timer = score.split(";"); // Liste qui permet de lire le fichier en séparant le temps et le pseudo avec le délimiteur ";"
        int scoreChiffre = timer.at(0).toInt();
        if (getTotalTimeInMs() <= scoreChiffre) {
           QString d = actualScore + ";" + pseudo;
           printTimerInFile(d);
        }
    }
}

void Chrono::printTimerInFile(QString t) {
    QFile file("timer.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream flux(&file);
    flux.setCodec("UTF-8");
    flux << t;
}

QString Chrono::recupBestTimer() {
    QFile file("timer.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&file);
    QString score;
    QString actualScore = QString::number(getTotalTimeInMs());
    QString bestPseudo;
    QString def;

    while (!flux.atEnd()) {
        score = flux.readLine();
        QStringList timer = score.split(";"); // Liste qui permet de lire le fichier en séparant le temps et le pseudo avec le délimiteur ";"
        int m =0;
        int s =0;
        int ms=0;
        int scoreChiffre = timer.at(0).toInt();  // Nombre total de millisecondes dans le fichier
        bestPseudo = timer.at(1); // Pseudo de l'auteur du meilleur temps dans le fichier
        //Conversion du total de millisecondes dans le fichier en "minute : secondes : millisecondes"
        s = floor(scoreChiffre/1000); // secondes
        m = floor(s/60); // minutes
        ms = scoreChiffre-(s*1000); // millisecondes
        def = QString::number(m) + ":" + QString::number(s) + ":" + QString::number(ms/10) + " by " + bestPseudo; // temps sous la forme "minute : secondes : millisecondes"
        return def;
    }
}

Chrono::~Chrono() {

}
