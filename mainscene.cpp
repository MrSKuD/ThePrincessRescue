#include "mainscene.h"

MainScene::MainScene() {
    this->setSceneRect(0, 0, 1800, 1000);
    isClosing = false;
    isHide = false;

    this->background.load(":/img/img/settings/background.png");
    this->setStartMenu();

    viewo.push_back(new QGraphicsView(this));
    viewo.at(0)->setWindowState(Qt::WindowFullScreen);
    viewo.at(0)->setWindowTitle("TPR");
    viewo.at(0)->resize(1500,1000);
    viewo.at(0)->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    viewo.at(0)->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
}

void MainScene::verifForm() {
    if(soundDisable->isChecked())
        disableSoundChecked = true;
    if(modeHardcore->isChecked())
        hardcoreModeChecked = true;

    if (lePseudo->text().isEmpty())
        lePseudo->setStyleSheet("border: 2px solid;"
                                "border-color: red;"
                                "font-family: times;"
                                "font-size: 16px;");
     else
        start();
}

void MainScene::start() {
    stateGame = false;
    keyFound = false;
    onCage = false;

    if(!pseudoAlready)
       Pseudo = lePseudo->text();
    else
       Pseudo = getPseudo();
    isHide = true;

    viewo.at(0)->show();
    this->clear();
    this->timer = new QTimer(this);
    this->timer->start(30);
    initSettings();
    pushListSettings();

    if(hardcoreModeChecked) {
        zombie->setSpeed(20);
        fireball1->setSpeed(25);
        fireball2->setSpeed(25);
    }

    if(disableSoundChecked) {
        character->setSound(false);
        livesDisplay->setSound(false);
        soundValue = false;
    }

    connect(timer, SIGNAL(timeout()), this, SLOT(updateScene()));
}

void MainScene::restart() {
    clearScene();
    pseudoAlready = true;
    start();
}

void MainScene::initSettings() {
    ground1 = new QGraphicsPixmapItem(QPixmap(":/img/img/settings/ground.png"));
    ground1->setPos(0, 860);

    spikes = new QGraphicsPixmapItem(QPixmap(":/img/img/settings/spikes.png"));
    spikes->setPos(474,0);

    rope = new QGraphicsPixmapItem(QPixmap(":/img/img/settings/rope.png"));
    rope->setPos(500, 0);

    key = new QGraphicsPixmapItem(QPixmap(":/img/img/settings/key.png"));
    key->setPos(490, 60);

    zombie = new Zombie(":/img/img/forwardanim_zombie/forward1.png");
    zombie->setPos(340,785);

    fireball1 = new FireBall(":/img/img/settings/fireballup.png");
    fireball1->setPos(1065, 600);

    fireball2 = new FireBall(":/img/img/settings/fireballup.png");
    fireball2->setPos(1340, 660);

    lava = new QGraphicsPixmapItem(QPixmap(":/img/img/settings/lava.png"));
    lava->setPos(1000, 860);

    platform = new QGraphicsPixmapItem(QPixmap(":/img/img/settings/platform.png"));
    platform->setPos(1143, 860);

    lava2 = new QGraphicsPixmapItem(QPixmap(":/img/img/settings/lava.png"));
    lava2->setPos(1275, 860);

    ground2 = new QGraphicsPixmapItem(QPixmap(":/img/img/settings/ground.png"));
    ground2->setPos(1418, 860);

    princess = new QGraphicsPixmapItem(QPixmap(":/img/img/princess.png"));
    princess->setPos(1650,ground1->pos().y()-(ground2->boundingRect().height())+10);

    spikedBall = new QGraphicsPixmapItem(QPixmap(":/img/img/settings/spikedball.png"));
    spikedBall->setPos(280, ground1->pos().y()-(ground1->boundingRect().height()/2)+26);

    tomb = new QGraphicsPixmapItem(QPixmap(":/img/img/settings/tomb.png"));

    this->spawnCharacter();

    pseudoDisplay = new QGraphicsTextItem();
    pseudoDisplay->setPlainText("Player : " + getPseudo());
    pseudoDisplay->setPos(750, 0);
    pseudoDisplay->setDefaultTextColor(Qt::white);
    pseudoDisplay->setFont(QFont("Helvetica", 24));

    time = new Chrono();
    time->setPos(750, pseudoDisplay->boundingRect().height());

    iconLives = new QGraphicsPixmapItem(QPixmap(":/img/img/iconLives.png"));
    iconLives->setPos(755, time->boundingRect().height()+pseudoDisplay->boundingRect().height());

    livesDisplay = new Lives();
    livesDisplay->setPos(805, time->boundingRect().height()+pseudoDisplay->boundingRect().height());

    iconKey = new QGraphicsPixmapItem(QPixmap(":/img/img/iconKey.png"));
    iconKey->setPos(870, time->boundingRect().height()+pseudoDisplay->boundingRect().height());

    alertKey = new QGraphicsTextItem();
    alertKey->setPlainText("FIND THE KEY !");
    alertKey->setDefaultTextColor(Qt::white);
    alertKey->setFont(QFont("times", 52));
    alertKey->setPos(900, 500);

    this->addItem(time);
    this->addItem(pseudoDisplay);
    this->addItem(ground1);
    this->addItem(rope);
    this->addItem(key);
    this->addItem(spikes);
    this->addItem(fireball1);
    this->addItem(lava);
    this->addItem(fireball2);
    this->addItem(lava2);
    this->addItem(zombie);
    this->addItem(platform);
    this->addItem(ground2);
    this->addItem(princess);
    this->addItem(spikedBall);
    this->addItem(iconLives);
    this->addItem(livesDisplay);
}

void MainScene::spawnCharacter() {
    character = new Character(":/img/img/forwardanim/forward1.png");
    character->setPos(20, ground1->y());
    character->setFlag(QGraphicsItem::ItemIsFocusable);
    character->setFocus();
    this->addItem(character);
}

void MainScene::pushListSettings() {
    listGroundSettings.push_back(ground1);
    listGroundSettings.push_back(platform);
    listGroundSettings.push_back(ground2);

    listKillSettings.push_back(spikes);
    listKillSettings.push_back(spikedBall);
    listKillSettings.push_back(zombie);
    listKillSettings.push_back(lava);
    listKillSettings.push_back(lava2);
    listKillSettings.push_back(fireball1);
    listKillSettings.push_back(fireball2);
}

void MainScene::updateScene() {
    if (character->x() >= 750 && character->x() <= 1015) { // Condition qui permet d'afficher les informations de la partie correctement selon la position du personnage
        pseudoDisplay->setPos(character->x(), 0);
        time->setPos(character->x(), pseudoDisplay->boundingRect().height());
        livesDisplay->setPos(character->x()+50, time->boundingRect().height()+pseudoDisplay->boundingRect().height());
        iconLives->setPos(character->x()+5, time->boundingRect().height()+pseudoDisplay->boundingRect().height());
        iconKey->setPos(character->x()+115, time->boundingRect().height()+pseudoDisplay->boundingRect().height());
    }

    viewo.at(0)->centerOn(character);
    character->setFlag(QGraphicsItem::ItemIsFocusable);
    character->setFocus();

    zombie->move();
    fireball1->move();
    fireball2->move();

    for (int i = 0; i < listGroundSettings.size() ; i++)
        character->move(listGroundSettings.at(i));

    if(character->getEscape()) {
        character->setEscapeReady(false);
        this->Pause();
    }

    this->CollisionEvent();
    this->checkLives();
}

void MainScene::checkLives() {
    if (livesDisplay->getLives() == 0 && !stateGame) {
        if(soundValue) {
            soundLose = new QMediaPlayer();
            soundLose->setMedia(QUrl("qrc:/sound/sound/gameover.wav"));
            soundLose->setVolume(50);
            soundLose->play();
        }

        clearScene();
        setEndMenu("<h1>YOU LOST...</h1>" ,":/img/img/jacquette/jacquette_lose.png");
    }
}

void MainScene::CollisionEvent() {
    for (int i = 0; i < listGroundSettings.size() ; i++) {

        if (character->collidesWithItem(listGroundSettings.at(i), Qt::IntersectsItemBoundingRect))
            character->setPos(character->x(), listGroundSettings.at(i)->y()-(listGroundSettings.at(i)->boundingRect().height()/2));
    }

    for (int i = 0; i < listKillSettings.size() ; i++) {

        if (character->collidesWithItem(listKillSettings.at(i))){
            if (listKillSettings.at(i) == spikes)
                tomb->setPos(character->x(), rope->y());

            if (listKillSettings.at(i) == zombie || listKillSettings.at(i) == spikedBall)
                tomb->setPos(character->x(), spikedBall->y()+10);

            if (listKillSettings.at(i) == lava || listKillSettings.at(i) == lava2 || listKillSettings.at(i) == fireball1 || listKillSettings.at(i) == fireball2)
                tomb->setPos(character->x(), character->y()+50);

            this->addItem(tomb);
            this->livesDisplay->decrease();
            character->setPos(20, ground1->pos().y());
            pseudoDisplay->setPos(750, 0);
            time->setPos(750, pseudoDisplay->boundingRect().height());
            iconLives->setPos(755, time->boundingRect().height()+pseudoDisplay->boundingRect().height());
            livesDisplay->setPos(805, time->boundingRect().height()+pseudoDisplay->boundingRect().height());
            iconKey->setPos(870, time->boundingRect().height()+pseudoDisplay->boundingRect().height());
        }
    }

    if(character->collidesWithItem(rope))
        character->setRope(true);

    if(character->collidesWithItem(key, Qt::IntersectsItemBoundingRect)) {
        keyFound = true;
        if(soundValue) {
            soundKey = new QMediaPlayer();
            soundKey->setMedia(QUrl("qrc:/sound/sound/key.wav"));
            soundKey->setVolume(50);
            soundKey->play();
        }
        this->addItem(iconKey);
        this->removeItem(key);
    }

    if(character->collidesWithItem(princess, Qt::IntersectsItemBoundingRect) && !keyFound) {
        this->addItem(alertKey);
        onCage = true;
    }

    if(character->x() < princess->x() && onCage) {
        this->removeItem(alertKey);
        onCage = false;
    }

    if(character->collidesWithItem(princess, Qt::IntersectsItemBoundingRect) && keyFound) {
        time->compareTimer(getPseudo());
        if(soundValue) {
            soundWin = new QMediaPlayer();
            soundWin->setMedia(QUrl("qrc:/sound/sound/win.wav"));
            soundWin->setVolume(50);
            soundWin->play();
        }
        stateGame = true;
        setEndMenu("<h1>YOU WIN !</h1>", ":/img/img/jacquette/jacquette_win.png");
    }
}

void MainScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}

void MainScene::createLayoutMenu(int x, int y, int w, int h, QColor backgroundColor, double opacity) {
    panel = new QGraphicsRectItem(x,y,w,h);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(backgroundColor);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    this->addItem(panel);
}

void MainScene::clearScene() {
    int nbGround = listGroundSettings.size();
    int nbKillSettings = listKillSettings.size();

    for (int i = 0; i < nbGround ; i++)
        listGroundSettings.erase(listGroundSettings.begin());
    for (int i = 0; i < nbKillSettings ; i++)
        listKillSettings.erase(listKillSettings.begin());

    this->clear();
}

void MainScene::setStartMenu() {
    Pseudo = nullptr;
    pseudoAlready = false;
    disableSoundChecked = false;
    hardcoreModeChecked = false;
    soundValue = true;

    clearScene();

    this->createLayoutMenu(0,0,1800,1000,Qt::black,0.65);
    createLayoutMenu(450,150,900,700,Qt::white,1);

    labPicture = new QLabel();
    labPicture->setPixmap(QPixmap(":/img/img/jacquette/jaquette_start.png"));
    labPicture->move(660,180);
    labPicture->setAttribute(Qt::WA_NoSystemBackground);

    txtMenu = new QLabel();
    txtMenu->setText("<h1>THE PRINCESS RESCUE</h1>");
    txtMenu->move(770, 630);
    txtMenu->setAttribute(Qt::WA_NoSystemBackground);
    txtMenu->setStyleSheet("color: red;"
                            "font-family: Monospace;"
                            );

    labPseudo = new QLabel();
    labPseudo->setText("PSEUDO");
    labPseudo->setAttribute(Qt::WA_NoSystemBackground);
    labPseudo->move(750, 677);

    lePseudo = new QLineEdit();
    lePseudo->setPlaceholderText("Enter your pseudo here");
    lePseudo->move(900, 680);
    lePseudo->setStyleSheet("font-family: times;"
                            "font-size: 16px");

    labHardcore = new QLabel();
    labHardcore->setText("Hardcore Mode");
    labHardcore->move(620,720);
    labHardcore->setAttribute(Qt::WA_NoSystemBackground);

    modeHardcore = new QCheckBox();
    modeHardcore->move(830, 727);

    labSound = new QLabel();
    labSound->setText("Disable sound");
    labSound->move(930,720);
    labSound->setAttribute(Qt::WA_NoSystemBackground);

    soundDisable = new QCheckBox;
    soundDisable->move(1135, 727);

    playAgain = new QPushButton();
    playAgain->setText("PLAY");
    playAgain->move(700,760);

    quit = new QPushButton();
    quit->setText("QUIT");
    quit->move(1010,760);

    labCredits = new QLabel();
    labCredits->setText("Game Design and PC Program Enzo MOULIN 2020");
    labCredits->setAttribute(Qt::WA_NoSystemBackground);
    labCredits->move(600, 820);

    setFont(QFont("Helvetica", 16));

    this->addWidget(labHardcore);
    this->addWidget(modeHardcore);
    this->addWidget(labSound);
    this->addWidget(soundDisable);
    this->addWidget(labPicture);
    this->addWidget(txtMenu);
    this->addWidget(labPseudo);
    this->addWidget(lePseudo);
    this->addWidget(playAgain);
    this->addWidget(quit);
    this->addWidget(labCredits);

    connect(playAgain,SIGNAL(clicked()),this,SLOT(verifForm()), Qt::QueuedConnection);
    connect(quit,SIGNAL(clicked()),this,SLOT(exitGame()));
}

void MainScene::setEndMenu(QString txtToDisplay, QString pathPicture) {
    this->timer->stop();
    clearScene();

    this->createLayoutMenu(0,0,1800,1000,Qt::black,0.65);

    labPicture = new QLabel();
    labPicture->setPixmap(QPixmap(pathPicture));
    labPicture->setAttribute(Qt::WA_NoSystemBackground);

    txtMenu = new QLabel();
    txtMenu->setText(txtToDisplay);
    txtMenu->setAttribute(Qt::WA_NoSystemBackground);

    labScore = new QLabel();
    labScore->setText("YOUR TIMER : "+QString::number(time->getMinutes())+":"+QString::number(time->getSecondes())+":"+QString::number(time->getMillisecondes()));
    labScore->setAttribute(Qt::WA_NoSystemBackground);

    labBestScore = new QLabel();
    labBestScore->setText("BEST SCORE TO BEAT : " + time->recupBestTimer());
    labBestScore->setAttribute(Qt::WA_NoSystemBackground);

    playAgain = new QPushButton();
    playAgain->setText("PLAY AGAIN");

    playAgainWithAnoterPseudo = new QPushButton();
    playAgainWithAnoterPseudo->setText("PLAY AGAIN WITH \n ANOTER PSEUDO");

    quit = new QPushButton();
    quit->setText("QUIT");

    if(txtToDisplay == "<h1>YOU WIN !</h1>") {
        createLayoutMenu(600,150,900,700,Qt::white,1);
        labPicture->move(880,180);
        txtMenu->move(960, 530);
        labScore->move(850, 600);
        labBestScore->move(850, 650);
        playAgain->move(769,750);
        playAgainWithAnoterPseudo->move(969 ,750);
        quit->move(1260,750);
        this->addWidget(labScore);
        this->addWidget(labBestScore);
    } else {
        createLayoutMenu(450,150,900,700,Qt::white,1);
        labPicture->move(700,180);
        txtMenu->move(780, 530);
        labScore->move(700, 600);
        labBestScore->move(700, 650);
        playAgain->move(600,750);
        playAgainWithAnoterPseudo->move(815 ,750);
        quit->move(1110,750);
    }

    setFont(QFont("Helvetica", 16));

    this->addWidget(labPicture);
    this->addWidget(txtMenu);
    this->addWidget(playAgain);
    this->addWidget(playAgainWithAnoterPseudo);
    this->addWidget(quit);

    connect(playAgain,SIGNAL(clicked()),this,SLOT(restart()), Qt::QueuedConnection);
    connect(playAgainWithAnoterPseudo,SIGNAL(clicked()),this,SLOT(setStartMenu()), Qt::QueuedConnection);
    connect(quit,SIGNAL(clicked()),this,SLOT(exitGame()));
}

void MainScene::Pause() {
        this->timer->stop();
        time->getTimer()->stop();

        this->createLayoutMenu(0,0,1800,1000,Qt::black,0.65);

        txtMenu = new QLabel();
        txtMenu->setText("CONTROLS");
        txtMenu->setStyleSheet("font-size : 35px;"
                               "color : white;");
        txtMenu->setAttribute(Qt::WA_NoSystemBackground);

        arrowKeys = new QGraphicsPixmapItem();
        arrowKeys->setPixmap(QPixmap(":/img/img/arrowkeys.png"));
        escapeKey = new QGraphicsPixmapItem();
        escapeKey->setPixmap(QPixmap(":/img/img/escape.png"));

        control1 = new QLabel();
        control1->setText("MOVING");
        control1->setStyleSheet("font-size : 25px;"
                                "color : white;");
        control1->setAttribute(Qt::WA_NoSystemBackground);

        control2 = new QLabel();
        control2->setText("PAUSE");
        control2->setStyleSheet("font-size : 25px;"
                                "color : white;");
        control2->setAttribute(Qt::WA_NoSystemBackground);

        backToGame = new QPushButton();
        backToGame->setText("BACK \n TO GAME");

        playAgain = new QPushButton();
        playAgain->setText("RESTART");

        playAgainWithAnoterPseudo = new QPushButton();
        playAgainWithAnoterPseudo->setText("CHANGE PSEUDO \n AND RESTART");

        quit = new QPushButton();
        quit->setText("QUIT");

        setFont(QFont("Helvetica", 12));

        if(character->x()< 750) {    // Condition 1 qui permet de centrer le menu de pause selon la position du personnage
            txtMenu->move(730, 170);
            arrowKeys->setPos(540,320);
            escapeKey->setPos(970,420);
            control1->move(620, 570);
            control2->move(960, 570);
            backToGame->move(470,730);
            playAgain->move(620,730);
            playAgainWithAnoterPseudo->move(770,730);
            quit->move(990,730);
        }

        if (character->x() >= 750 && character->x() <= 1015) {  // Condition 2 ""
            txtMenu->move(character->x()-25, 170);
            arrowKeys->setPos(character->x()-202,320);
            escapeKey->setPos(character->x()+216,420);
            control1->move(character->x()-82, 570);
            control2->move(character->x()+221, 570);
            backToGame->move(character->x()-255,730);
            playAgain->move(character->x()-121,730);
            playAgainWithAnoterPseudo->move(character->x()+29,730);
            quit->move(character->x()+251,730);
        }

        if(character->x() > 1015) {  // Condition 3 ""
            txtMenu->move(1095, 170);
            arrowKeys->setPos(905,320);
            escapeKey->setPos(1335,420);
            control1->move(985, 570);
            control2->move(1325, 570);
            backToGame->move(835,730);
            playAgain->move(985,730);
            playAgainWithAnoterPseudo->move(1135,730);
            quit->move(1355,730);
        }

        this->addWidget(txtMenu);
        this->addItem(arrowKeys);
        this->addItem(escapeKey);
        this->addWidget(control1);
        this->addWidget(control2);
        this->addWidget(backToGame);
        this->addWidget(playAgain);
        this->addWidget(playAgainWithAnoterPseudo);
        this->addWidget(quit);

        connect(backToGame,SIGNAL(clicked()),this,SLOT(backToGameClear()));
        connect(playAgain,SIGNAL(clicked()),this,SLOT(restart()), Qt::QueuedConnection);
        connect(playAgainWithAnoterPseudo,SIGNAL(clicked()),this,SLOT(setStartMenu()), Qt::QueuedConnection);
        connect(quit,SIGNAL(clicked()),this,SLOT(exitGame()));
}

void MainScene::backToGameClear() {
    delete txtMenu;
    delete arrowKeys;
    delete escapeKey;
    delete control1;
    delete control2;
    delete panel;
    delete backToGame;
    delete quit;
    delete playAgain;
    delete playAgainWithAnoterPseudo;

    character->setEscapeReady(true);
    this->timer->start(30);
    time->getTimer()->start(10);
}

void MainScene::exitGame() {
    viewo.at(0)->close();
    isClosing = true;
}

QString MainScene::getPseudo() {
    return Pseudo;
}

bool MainScene::getExit() {
    return isClosing;
}

bool MainScene::getHide() {
    return isHide;
}

MainScene::~MainScene() {

}
