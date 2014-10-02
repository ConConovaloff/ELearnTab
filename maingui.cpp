#include "maingui.h"
#include <QtGui>
#include <QtCore>
#include <QPalette>

MainGui::MainGui(Core *ptrCore, QWidget *parent) :
    QLabel(parent)
{
    mainCore = ptrCore;
    settingWin = 0; //object for setting window
    QPixmap pix("./style/default/mainPixMap.png");
    setWindowTitle("ELearnTab");
    setWindowIcon(QIcon("./style/default/programmIcon.gif"));
    setAcceptDrops(true);

    //Action Create
    rmMenuExit = new QAction(tr("&Exit"), this);
    rmMenuExit->setStatusTip(tr("Exit from programm"));
    connect(rmMenuExit, SIGNAL(triggered()),
                  qApp, SLOT(quit()));

    rmReverseWords = new QAction(tr("&Reverse"), this);
    rmReverseWords->setStatusTip(tr("Russian-UP, English-Down"));
    rmReverseWords->setCheckable(true);
    connect(rmReverseWords, SIGNAL(triggered()),
                  mainCore, SLOT(slotReverseWord()));

    rmSetting = new QAction(tr("&Settings"), this);
    rmSetting->setStatusTip(tr("Settings programm"));
    connect(rmSetting, SIGNAL(triggered()),
                 this, SLOT(showSettings()));
    //// End Action Create

    moving = false;
    setPixmap(pix);
    setMask(pix.mask());
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    upText = new QLabel("No Data");
    downText = new QLabel("No Data");
    mainButton = new QPushButton("V");
    connect(mainButton, SIGNAL(clicked()),
                  this, SLOT(clickedMainButton()));

    int idFont = QFontDatabase::addApplicationFont("./style/default/font.ttf");
    QFont* guiFont = new QFont(QFontDatabase::applicationFontFamilies(idFont).first());

#ifdef Q_WS_WIN
    guiFont.setBold(true);
    guiFont->setPointSize(12);
#endif

    upText->setFont(*guiFont);
    upText->setGeometry(11, 11, 164, 47);
    upText->setParent(this);
    downText->setFont(*guiFont);
    downText->setGeometry(11, 64, 164, 47);
    downText->setParent(this);

    mainButton->setFont(*guiFont);
    mainButton->setGeometry(195,0, 55, 122);
    mainButton->setParent(this);
    mainButton->setFocusPolicy(Qt::NoFocus);
    mainButton->setObjectName("mainButton"); // for qss
}


// Интерфейсы
void MainGui::changeUpText(QString inText){
    upText->setText(inText);
}

void MainGui::changeDownText(QString inText){
    downText->setText(inText);
}

void MainGui::changeMainButton(QString inText){
    mainButton->setText(inText);
    mainButton->style()->unpolish(mainButton); // обновление вида кнопки(qss)
}
// END

void MainGui::clickedMainButton(){
    if(mainButton->text() == "+"){
        changeMainButton("V");
        mainCore->setMayAddTranslate(false);
        mainCore->addWordsTransmiter(upText->text(), downText->text());
    }else if(mainButton->text() == "X"){
        mainCore->studiedWordsTransmiter(upText->text());
        mainCore->nextWords();
    }
}

// Меню по правой кнопке
void MainGui::contextMenuEvent(QContextMenuEvent *pe){
    menu = new QMenu(this);
    menu->addAction(rmSetting);
//    rmModeSubMenu = new QMenu(tr("&Modes"), this);  // Перенести в настройки + проверить, правильность
//    rmModeSubMenu->addAction(rmReverseWords);
//    menu->addMenu(rmModeSubMenu);

    // right mouse menu -> bases list
    rmBaseSubMenu = new QMenu(tr("&Bases"), this);
    QDir baseDir("./Bases");
    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(QString)),
                mainCore, SLOT(changeBase(QString)));

    QAction *tmpAction;
    foreach(QString inFiles, baseDir.entryList(QStringList("*.sqlite"), QDir::Files)){
        tmpAction = new QAction(QFileInfo(baseDir, inFiles).baseName(), this);
        signalMapper->setMapping(tmpAction, QFileInfo(baseDir, inFiles).absoluteFilePath());
        connect(tmpAction, SIGNAL(triggered()),
             signalMapper, SLOT(map()));
        rmBaseSubMenu->addAction(tmpAction);
    }
    // END
    menu->addMenu(rmBaseSubMenu);
    menu->addAction(rmMenuExit);
    menu->exec(QCursor::pos());
}



// Движение окна с использованием клика мыши
void MainGui::mouseMoveEvent(QMouseEvent *event){
    if(this->moving){
        this->move(event->globalPos() - this->offset);
    }
}


void MainGui::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        this->moving = true;
        this->offset = event->pos();
    }
}


void MainGui::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        this->moving = false;
    }
}
// END


// Drag & Drop
void MainGui::dragEnterEvent(QDragEnterEvent *event){
    if(event->mimeData()->hasFormat("text/plain")){
        event->acceptProposedAction();
    }
}

void MainGui::dropEvent(QDropEvent *event){
    QString DropText = event->mimeData()->text();
    mainCore->changeMode(3, DropText);
}
// END

void MainGui::enterEvent(QEvent *event){
    if(1 == mainCore->getMode()){
        mainCore->changeMode(2);
    }
}

void MainGui::leaveEvent(QEvent *event){
    mainCore->changeMode(1);
}

void MainGui::showSettings(){
    if(!settingWin){
        settingWin = new SettingWin();
    }
    settingWin->show();
}
