#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    mainwindow mainWindow;
    mainWindow.setWindowTitle("To-Do List By Cloud Hub");
    mainWindow.resize(400, 300);
    mainWindow.show();

    return app.exec();
}
