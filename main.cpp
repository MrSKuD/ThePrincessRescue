/*
@Author: Enzo MOULIN
@Website: http://www.enzomoulin.com/
@Email: enzo.moulin@isen-ouest.yncrea.fr
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);
    MainWindow mainWindow;

    mainWindow.show();
    return application.exec();
}
