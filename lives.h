#ifndef LIVES_H
#define LIVES_H

#include <QGraphicsTextItem>
#include <QFont>
#include <QMediaPlayer>

class Lives : public QGraphicsTextItem {
public:
    Lives(QGraphicsItem* parent = 0);
    ~Lives();
    void decrease(); // décrémente le nombre de vie et émet un son (est appelé dans la mainscene lors de collision avec un obstable qui tue)
    int getLives(); // retourne le nombre de vie
    void setSound(bool newSound); // permet de changer la valeur d'un booléen pour activer / désactiver le son

private:
    bool soundBool;
    int nbLives;
    QMediaPlayer* soundLivesDecrease;

};


#endif // LIVES_H



