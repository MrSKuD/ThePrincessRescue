/*
@Author: Enzo MOULIN
@Website: http://www.enzomoulin.com/
@Email: enzo.moulin@isen-ouest.yncrea.fr
 */

#include "zombie.h"

Zombie::Zombie(QString imageFileName) : QGraphicsPixmapItem(QPixmap(imageFileName)) {
    speed = 5;
    right = false;
    left = false;
    iListForward = 0;
    iListBackward = 0;

    this->direction();
    this->setPixmapForward();
    this->setPixmapBackward();
}

void Zombie::setPixmapForward() {
    forward.push_back(QPixmap(":/img/img/forwardanim_zombie/forward1.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim_zombie/forward2.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim_zombie/forward3.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim_zombie/forward4.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim_zombie/forward5.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim_zombie/forward6.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim_zombie/forward7.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim_zombie/forward8.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim_zombie/forward9.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim_zombie/forward10.png"));

}

void Zombie::setPixmapBackward() {
    backward.push_back(QPixmap(":/img/img/backwardanim_zombie/backward1.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim_zombie/backward2.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim_zombie/backward3.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim_zombie/backward4.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim_zombie/backward5.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim_zombie/backward6.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim_zombie/backward7.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim_zombie/backward8.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim_zombie/backward9.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim_zombie/backward10.png"));
}

void Zombie::direction() {
    if(this->x() < 340) {
        left = false;
        right = true;
    }
    if(this->x() > 900) {
        right = false;
        left = true;
    }
}

void Zombie::move() {
    if (right) {
        if (iListForward == forward.size()) {
            iListForward = 0;
        }
        setPixmap(forward.at(iListForward));
        iListForward++;
        setPos(this->x()+speed,this->y());
    }
    if(left) {
        if (iListBackward == backward.size()) {
            iListBackward = 0;
        }
        setPixmap(backward.at(iListBackward));
        iListBackward++;
        setPos(this->x()-speed,this->y());
    }
    direction();
}

void Zombie::setSpeed(int newSpeed) {
    this->speed = newSpeed;
}

Zombie::~Zombie() {

}
