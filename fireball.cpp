/*
@Author: Enzo MOULIN
@Website: http://www.enzomoulin.com/
@Email: enzo.moulin@isen-ouest.yncrea.fr
 */

#include "fireball.h"

FireBall::FireBall(QString imageFileName) : QGraphicsPixmapItem(QPixmap(imageFileName)) {
    speed = 5;
    up = false;
    down = false;

    this->direction();
}

void FireBall::direction() {
    if(this->y() < 600) {
        down = true;
        up = false;
    }

    if(this->y() > 900) {
        up = true;
        down = false;
    }
}

void FireBall::move() {
    if (down) {
        setPixmap(QPixmap(":/img/img/settings/fireballdown.png"));
        setPos(this->x(),this->y()+speed);
    }

    if(up) {
        setPixmap(QPixmap(":/img/img/settings/fireballup.png"));
        setPos(this->x(),this->y()-speed);
    }
    direction();
}

void FireBall::setSpeed(int newSpeed) {
    this->speed = newSpeed;
}

FireBall::~FireBall() {

}
