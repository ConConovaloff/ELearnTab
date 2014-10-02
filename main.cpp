#include <QApplication>
#include <QFile>
#include <QDebug>
#include "maingui.h"
#include "core.h"
#include "wordbase.h"


int main(int argc, char** argv){
    QApplication app(argc, argv);

    QFile file("./style/default/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    app.setStyleSheet(styleSheet);

    WordBase *base = new WordBase("./Bases/general.sqlite");
    Core *appCore = new Core;
    MainGui *win = new MainGui(appCore);

    win->show();
    appCore->guiConnect(win);
    appCore->baseConnect(base);
    appCore->start();
    return app.exec();
}
