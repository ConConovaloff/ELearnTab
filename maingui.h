#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include "core.h"
#include "setting.h"

class QPoint;
class QAction;
class QMenu;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class Core;
class QActionGroup;



class MainGui : public QLabel
{
    Q_OBJECT
public:
    explicit MainGui(Core *ptrCore, QWidget *parent = 0);
    void changeUpText();
    void changeUpText(QString inText);
    void changeDownText();
    void changeDownText(QString inText);
    void changeMainButton(QString inText);
signals:

public slots:

private slots:
    void clickedMainButton();
    void showSettings();

private:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent* pe);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);


    Core *mainCore;

    QLabel *upText;
    QLabel *downText;
    QPushButton *mainButton;

    bool moving; // Двигается ли окно
    QPoint offset; // Отступ, для движения окна, мышью

    QAction *rmMenuExit;
    QAction *rmReverseWords;
    QAction *rmSetting;
    QMenu *menu;
    QMenu *rmModeSubMenu;
    QMenu *rmBaseSubMenu;

    SettingWin *settingWin;
};

#endif // MAINWINDOW_H
