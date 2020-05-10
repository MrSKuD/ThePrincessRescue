/*
@Author: Enzo MOULIN
@Website: http://www.enzomoulin.com/
@Email: enzo.moulin@isen-ouest.yncrea.fr
 */

#ifndef PROJETQT_CHARACTER_H
#define PROJETQT_CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QList>
#include <QMediaPlayer>


class Character:public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
private:
    int speed;
    bool sound;
    bool rope;
    bool right;
    bool left;
    bool up;
    bool down;
    bool jumpReady;
    bool rightAnimReady;
    bool leftAnimReady;
    bool escape;
    bool escapeReady;
    QPixmap mainAnim;
    QPixmap rightAnim;
    QPixmap leftAnim;
    QMediaPlayer* jumpSound;
    QList<QPixmap> forward;
    QList<QPixmap> backward;
    int iListForward;
    int iListBackward;

public:
    Character(QString imageFileName);
    ~Character();
    void move(QGraphicsPixmapItem* i); // fais bouger le personnage en fonction des touches préssées et anime le personnage
    void fall(); // fait tomber le personnage sur le sol
    void jump(); // fait sauter le personnage en émmettant un son
    bool getEscape(); // récupère la valeur de escape
    bool getEscapeReady(); // récupère la valeur de escapeReady (qui permet de savoir si le jeu est déjà en pause ou non)
    void setEscapeReady(bool ecsR); // permet de changer la valeur de escapeReady ( = false quand le jeu est en pause)
    void setRope(bool rope); // permet de changer la valeur de rope ( = true si le personnage grimpe sur la corde)
    void setPixmapForward(); // met dans la liste les images d'animations du personnnage qui avance
    void setPixmapBackward(); // idem mais dans le sens inverse
    void setSound(bool newSound); // permet de changer la valeur d'un booléen pour activer / désactiver le son

protected:
    void keyPressEvent(QKeyEvent* event); // detecte quand l'utilisateur appuie sur une touche
    void keyReleaseEvent(QKeyEvent* event); // detecte quand l'utilisateur relâche une touche

};


#endif // CHARACTER_H
