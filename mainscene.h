#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "character.h"
#include "lives.h"
#include "chrono.h"
#include "zombie.h"
#include "fireball.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPushButton>
#include <QTimer>
#include <QUrl>
#include <QMediaPlayer>
#include <QPainter>
#include <QDialog>
#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QGraphicsView>
#include <QCheckBox>
#include <QLineEdit>

class MainScene : public QGraphicsScene {
    Q_OBJECT

private:
    bool stateGame; // ce booléen permet d'éviter de repasser par la fonction checkLives() lors d'une victoire car cela était source de bogues
    bool disableSoundChecked;
    bool hardcoreModeChecked;
    bool soundValue;
    bool keyFound;
    bool onCage;
    bool pseudoAlready;
    bool isHide;
    bool isClosing;
    QPixmap background;
    QPixmap backgroundMenu;
    QTimer* timer;
    Chrono* time;
    Lives* livesDisplay;
    QGraphicsPixmapItem* iconLives;
    QGraphicsTextItem* pseudoDisplay;
    QGraphicsPixmapItem* iconKey;
    QGraphicsTextItem* alertKey;
    Character* character;
    Zombie* zombie;
    QGraphicsPixmapItem* princess;
    QGraphicsPixmapItem* ground1;
    QGraphicsPixmapItem* rope;
    QGraphicsPixmapItem* spikes;
    QGraphicsPixmapItem* key;
    QGraphicsPixmapItem* ground2;
    QGraphicsPixmapItem* platform;
    QGraphicsPixmapItem* spikedBall;
    QGraphicsPixmapItem* lava;
    QGraphicsPixmapItem* lava2;
    QGraphicsPixmapItem* tomb;
    FireBall* fireball1;
    FireBall* fireball2;
    QGraphicsRectItem* panel;
    QLabel* labPseudo;
    QLabel* txtMenu;
    QLabel* labSound;
    QLabel* labHardcore;
    QLabel* labPicture;
    QLabel* labScore;
    QLabel* labBestScore;
    QLabel* labCredits;
    QLabel* control1;
    QLabel* control2;
    QLineEdit* lePseudo;
    QString Pseudo;
    QPushButton* playAgain;
    QPushButton* playAgainWithAnoterPseudo;
    QPushButton* backToGame;
    QPushButton* quit;
    QGraphicsPixmapItem* escapeKey;
    QGraphicsPixmapItem* arrowKeys;
    QCheckBox* soundDisable;
    QCheckBox* modeHardcore;
    QMediaPlayer* soundWin;
    QMediaPlayer* soundLose;
    QMediaPlayer* soundDie;
    QMediaPlayer* soundKey;
    QList<Character*> charItems;
    QList<QGraphicsView*> viewo;
    QList<QGraphicsPixmapItem*> listGroundSettings;
    QList<QGraphicsPixmapItem*> listKillSettings;

public:
    MainScene();
    virtual ~MainScene();
    void drawBackground(QPainter* painter, const QRectF& rect); // dessine l'arrière plan
    QString getPseudo(); // permet de recupérer le pseudo
    void start(); // démarre la partie
    void initSettings(); //initialise tous les items de la scène, les place et les ajoute
    void spawnCharacter(); // créer le personnage et le place au bon endroit
    void pushListSettings(); // ajoute dans les listes les éléments de la scène (objets qui tue le personnages et les sols)
    void clearScene(); //efface toutes la scène et vide les listes
    void CollisionEvent(); //détecte les collisions
    void checkLives(); //vérifie le nombre de vie
    void setEndMenu(QString txtToDisplay, QString pathPicture); // créer le menu de fin (qui apparaît en cas de défaite et de victoire)
    void createLayoutMenu(int x, int y, int w, int h, QColor backgroundColor, double opacity); //créer le layout de menu
    bool getHide(); // retourne un booléen pour cacher la mainWindow
    bool getExit(); // retourne un booléen pour fermer la mainWindow (et donc tout le jeu)
    void Pause(); // stoppe le jeu créer le menu de pauses (qui apparaît en appuyant sur la touche echap en jeu)

public slots :
    void setStartMenu(); //créer le menu de démarrage de jeu
    void updateScene(); // actualise le jeu en permanence
    void restart(); // redémarre le jeu en cas de "play Again"
    void verifForm(); // vérifie le formulaire de début de jeu (pseudo et checkbox)
    void exitGame(); // ferme la vue et affecte la valeur "true" que va récupérer la mainWindow pour se fermer à son tour
    void backToGameClear(); // supprimer l'écran de pause et reprend le jeu la où il s'était arrêté
};


#endif // MAINSCENE_H
