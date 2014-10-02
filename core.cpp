#include "core.h"
#include "iostream"

Core::Core(QThread *parent) :
    QThread(parent)
{
    coreMod = 1;
    reverse = false;
    mayAddTranslate = false;
    translateAPI = new TranslateAPI;
}

void Core::guiConnect(MainGui *inWin){
    mainGui = inWin;
}

void Core::baseConnect(WordBase *inBase){
    readyBase = inBase;
}

void Core::upTextTransmiter(QString inText){
    mainGui->changeUpText(inText);
}

void Core::downTextTransmiter(QString inText){
    mainGui->changeDownText(inText);
}

void Core::slotReverseWord(){
    reverse=true;
}

void Core::changeBase(QString inText){
    readyBase->changeBase(inText);
}

void Core::addWordsTransmiter(QString engInText, QString otherInText){
    readyBase->addWords(engInText, otherInText);
}

void Core::studiedWordsTransmiter(QString engInText){
    readyBase->studiedWords(engInText);
}

void Core::setMayAddTranslate(bool inBool){
    mayAddTranslate = inBool;
}

bool Core::getMayAddTranslate(){
    return mayAddTranslate;
}

void Core::nextWords(){
    if(!reverse){
        readyBase->randomLine(this);
    }else{
        readyBase->reverseRandomLine(this);
    }
}

void Core::prepareWords(){
    readyBase->getWords(this);
}

void Core::changeUpWord(){
    mainGui->changeUpText(wordToUpLabel);
}

void Core::changeDownWord(){
    mainGui->changeDownText(wordToDownLabel);
}

void Core::clearWords(){
    mainGui->changeUpText(" ");
    mainGui->changeDownText(" ");
}

void Core::changeMode(short idMode, QString inText){
    // For coreMod:
    // 1 - normal
    // 2 - pause
    coreMod = idMode;
    if(coreMod == 2){
        if(!getMayAddTranslate()){
            mainGui->changeMainButton("X");
        }
    }else if(coreMod == 1){
        if(!getMayAddTranslate()){
            mainGui->changeMainButton("V");
        }
    }else if(coreMod == 3){ // TranslateAPI
        mainGui->changeMainButton("+");
        setMayAddTranslate(true); // Если выходим из наведения, то "+" остается и можно заново навести.
        mainGui->changeUpText(inText);
        QString tmpTranslateBD = readyBase->translateFromDB(inText);
        if(tmpTranslateBD != "None"){ // Если уже имеется в базе
            mainGui->changeDownText(tmpTranslateBD);
        }else{ // Иначе API
            mainGui->changeDownText(translateAPI->translate(inText));
        }
    }
}

int Core::getMode(){
    return coreMod;
}

void Core::run(){
    while(1){
        if(coreMod == 1 /* Normal */){
            if(getMayAddTranslate()){
                setMayAddTranslate(false);
                mainGui->changeMainButton("V");
            }
            clearWords();
            QThread::sleep(appSetting->value("window/timing/pause").toInt());
            prepareWords();
            if(coreMod == 1){
                changeUpWord();
            }
            QThread::sleep(appSetting->value("window/timing/uptext").toInt());
            if(coreMod == 1){
                changeDownWord();
            }
            QThread::sleep(appSetting->value("window/timing/downtext").toInt());

            //nextWords();

        }else if (coreMod == 2 /* Pause */) {
            QThread::sleep(1);
        }else if (coreMod == 3 /* TranslateAPI */){
            QThread::sleep(1);
        }
        QThread::sleep(1);
    }
}
