/*
@Author: Enzo MOULIN
@Website: http://www.enzomoulin.com/
@Email: enzo.moulin@isen-ouest.yncrea.fr
 */

#include "lives.h"

Lives::Lives(QGraphicsItem * parent) : QGraphicsTextItem(parent) {
    soundBool = true;
    nbLives = 3;

    setPlainText("x " + QString::number(nbLives));
    setDefaultTextColor(Qt::white);
    setFont(QFont("Helvetica", 24));
}

void Lives::decrease() {
    nbLives--;
    if(soundBool){
        soundLivesDecrease = new QMediaPlayer();
        soundLivesDecrease->setMedia(QUrl("qrc:/sound/sound/mort.wav"));
        soundLivesDecrease->setVolume(50);
        soundLivesDecrease->play();
    }
    setPlainText("x " + QString::number(nbLives));
}

void Lives::setSound(bool newSound) {
    this->soundBool = newSound;
}

int Lives::getLives() {
    return nbLives;
}

Lives::~Lives() {

}
