#ifndef CORE_H
#define CORE_H

#include <QThread>
#include "maingui.h"
#include "wordbase.h"
#include "translateapi.h"

class WordBase;
class MainGui;
class TranslateAPI;

class Core : public QThread
{
    Q_OBJECT
public:
    explicit Core(QThread *parent = 0);
    void baseConnect(WordBase *inBase);
    void guiConnect(MainGui *inWin);
    void upTextTransmiter(QString inText);
    void downTextTransmiter(QString inText);
    void changeMode(short idMode, QString inText = "None");
    int  getMode();
    void addWordsTransmiter(QString engInText, QString otherInText);
    void studiedWordsTransmiter(QString engInText);

    void nextWords();

    void setMayAddTranslate(bool);
    bool getMayAddTranslate();

    void prepareWords();
    void changeUpWord();
    void changeDownWord();
    void clearWords();

    QString wordToUpLabel;
    QString wordToDownLabel;
signals:

public slots:
    void slotReverseWord();
    void changeBase(QString inText);

protected:
    void run();

private:
    MainGui *mainGui;
    WordBase *readyBase;
    TranslateAPI *translateAPI;
    bool reverse;
    bool mayAddTranslate;


    short coreMod;
    // 1 - normal
    // 2 - pause

};

#endif // CORE_H
