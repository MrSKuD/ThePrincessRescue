#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainscene.h"

#include <QtWidgets/QtWidgets>
#include <QMainWindow>
#include <QGraphicsView>

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    MainScene* mainScene;
    QGraphicsView* mainView;
    QGraphicsView* titleScreenView;
    QGraphicsView* viewFocus;
    QTimer* timermain;

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() {};

public slots :
    void quitApp();  // vérifie en permanence la valeur de 2 booléens. Selon leur valeur, la fenêtre va se cacher ou se fermer.
};


#endif // MAINWINDOW_H
