#include "character.h"

Character::Character(QString imageFileName) : QGraphicsPixmapItem(imageFileName) {
    speed = 10;
    sound = true;
    rope = false;
    right = false;
    left = false;
    up = false;
    down = true;
    jumpReady = true;
    escape = false;
    escapeReady = true;
    iListForward = 0;
    iListBackward = 0;

    setPixmapForward();
    setPixmapBackward();
}

void Character::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left && !rope)
        left = true;
    else if (event->key() == Qt::Key_Right && !rope)
        right = true;
    else if (event->key() == Qt::Key_Up && jumpReady)
        up = true;
    else if (event->key() == Qt::Key_Escape && escapeReady)
        escape = true;
}

void Character::setPixmapForward() {
    forward.push_back(QPixmap(":/img/img/forwardanim/forward1.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim/forward2.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim/forward4.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim/forward5.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim/forward6.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim/forward7.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim/forward8.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim/forward9.png"));
    forward.push_back(QPixmap(":/img/img/forwardanim/forward10.png"));
}

void Character::setPixmapBackward() {
    backward.push_back(QPixmap(":/img/img/backwardanim/backward1.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim/backward2.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim/backward4.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim/backward5.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim/backward6.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim/backward7.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim/backward8.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim/backward9.png"));
    backward.push_back(QPixmap(":/img/img/backwardanim/backward10.png"));
}

void Character::move(QGraphicsPixmapItem* i) {
    if (left && this->x() > 0) {
        if (iListBackward == backward.size()) {
            iListBackward = 0;
        }
        setPixmap(backward.at(iListBackward));
        iListBackward++;
        setPos(this->x()-speed,this->y());
    }

    if (right && this->x() + this->boundingRect().width() < 1800) {
        if (iListForward == forward.size()) {
            iListForward = 0;
        }
        setPixmap(forward.at(iListForward));
        iListForward++;
        setPos(this->x()+speed,this->y());
    }

    if (up && this->y() > 0 && this->collidesWithItem(i, Qt::IntersectsItemBoundingRect)) {
        rope = false;
        jump();
        jumpReady = true;
    }

    if (up && rope && !right && !left)
        setPos(this->x(), this->y()-3);

    else {
        rope = false;
        fall();
    }
}

void Character::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left)
        left = false;
    else if (event->key() == Qt::Key_Right)
        right = false;
    else if (event->key() == Qt::Key_Up)
        up = false;
    else if (event->key() == Qt::Key_Escape)
        escape = false;
    else
        down = true;
}

void Character::setRope(bool rope) {
    this->rope = rope;
}

bool Character::getEscape() {
    return escape;
}

bool Character::getEscapeReady() {
    return escapeReady;
}

void Character::setEscapeReady(bool escR) {
    this->escapeReady = escR;
}

void Character::fall() {
    setPos(this->x(),this->y()+5);
}

void Character::jump() {
    jumpReady = false;
    if(sound) {
        jumpSound = new QMediaPlayer();
        jumpSound->setMedia(QUrl("qrc:/sound/sound/jump.wav"));
        jumpSound->setVolume(50);
        jumpSound->play();
    }
    setPos(this->x(),this->y()-150);
}

void Character::setSound(bool newSound) {
    this->sound = newSound;
}

Character::~Character() {

}
