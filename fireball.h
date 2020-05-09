#ifndef FIREBALL_H
#define FIREBALL_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class FireBall: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
private:
    int speed;
    bool up;
    bool down;

public:
    FireBall(QString imageFileName);
    ~FireBall();
    void direction(); // change la direction de la boule de feu selon sa position
    void move(); // fait monter/descendre la boule de feu et change son image selon sa direction
    void setSpeed(int newSpeed); // permet de changer la valeur de la vitesse

};

#endif // FIREBALL_H
