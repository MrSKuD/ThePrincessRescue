/*
@Author: Enzo MOULIN
@Website: http://www.enzomoulin.com/
@Email: enzo.moulin@isen-ouest.yncrea.fr
 */

#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QList>

class Zombie: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
private:
    int speed;
    bool right;
    bool left;
    QList<QPixmap> forward;
    QList<QPixmap> backward;
    QList<QPixmap> jumpRight;
    QList<QPixmap> die;
    int iListForward = 0;
    int iListBackward = 0;

public:
    Zombie(QString imageFileName);
    ~Zombie();
    void direction(); // change la direction du zombie selon sa position
    void setPixmapForward(); // met dans la liste les images d'animations du zombie qui avance
    void setPixmapBackward(); // idem mais dans le sens inverse
    void move(); // fait aller à droite/gauche le zombie et change son image selon sa direction pour l'animer
    void setSpeed(int newSpeed); // permet de changer la valeur de la vitesse
};


#endif // ZOMBIE_H
