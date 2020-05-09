#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->timermain = new QTimer();
    this->timermain->start(30);

    this->mainScene = new MainScene();
    mainView = new QGraphicsView();
    mainView->setScene(mainScene);

    this->setCentralWidget(mainView);
    this->setWindowState(Qt::WindowFullScreen);
    mainView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    mainView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    this->setWindowTitle("TPR");
    this->setFixedSize(1800,1000);

    connect(timermain, SIGNAL(timeout()), this, SLOT(quitApp()));
}

void MainWindow::quitApp() {
    if(mainScene->getExit())
        this->close();
    if(mainScene->getHide())
        this->hide();
}
