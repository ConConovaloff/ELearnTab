#include <QtGui>
#include <QtSql>
#include "wordbase.h"

WordBase::WordBase(QString inBaseName,QObject *parent) :
    QObject(parent)
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName(inBaseName);
    if (!db->open()){
        QMessageBox::warning(0, QObject::tr("Database Error"), db->lastError().text());
    }
    query = new QSqlQuery;
}


void WordBase::changeBase(QString inText){
    db->setDatabaseName(inText);
    if (!db->open()){
        QMessageBox::warning(0, QObject::tr("Database Error"), db->lastError().text());
    }
    query = new QSqlQuery;
}

QString WordBase::translateFromDB(QString engInText){
    query->prepare("SELECT bother FROM words WHERE aeng = :aeng;");
    query->bindValue(":aeng", engInText);
    if(!query->exec()){ // Ошибка
        qDebug() << "ERROR: " << query->lastError();
    }else if(query->next()){ // Перевод есть
        return query->value(0).toString();
    }else{ // Перевода нет
        return "None";
    }
}

void WordBase::addWords(QString engInText, QString otherInText){
    //Проверяем на наличие повтора
    query->prepare("SELECT cdone FROM words WHERE aeng = :aeng;");
    query->bindValue(":aeng", engInText);
    if(!query->exec()){
        qDebug() << "ERROR: " << query->lastError();
    }else if(query->next()){
        if(query->value(0).toBool()){ //Повторяющееся, якобы выученое
            query->prepare("UPDATE words SET cdone = 0 WHERE aeng = :aeng");
            query->bindValue(":aeng", engInText);
            if(!query->exec()){
                qDebug() << "ERROR: " << query->lastError();
            }
        }else{ // Повторяющееся, не выученное
            //nothing
        }
    }else{ //Повторов нет
        query->prepare("INSERT INTO words (aeng, bother, cdone) VALUES (:aeng, :bother, 0)");
        query->bindValue(":aeng", engInText);
        query->bindValue(":bother", otherInText);
        if(!query->exec()){
            qDebug() << "ERROR" << query->lastError();
        }
    }
}

void WordBase::studiedWords(QString engInText){
    query->prepare("UPDATE words SET cdone = 1 WHERE aeng = :aeng");
    query->bindValue(":aeng", engInText);
    if(!query->exec()){
        qDebug() << "ERROR: "<< query->lastError();
    }
}

void WordBase::randomLine(Core *ptrCore){
    query->exec("SELECT aeng, bother FROM words WHERE cdone = 0 ORDER BY RANDOM() LIMIT 1;");
    if(query->next()){
        ptrCore->upTextTransmiter(query->value(0).toString());
        ptrCore->downTextTransmiter(query->value(1).toString());
    }else{
        ptrCore->upTextTransmiter("Not Data");
        ptrCore->downTextTransmiter("Not Data");
    }
}

void WordBase::reverseRandomLine(Core *ptrCore){
    query->exec("SELECT bother, aeng FROM words WHERE cdone = 0 ORDER BY RANDOM() LIMIT 1;");
    if(query->next()){
        ptrCore->upTextTransmiter(query->value(0).toString());
        ptrCore->downTextTransmiter(query->value(1).toString());
    }else{
        ptrCore->upTextTransmiter("Not Data");
        ptrCore->downTextTransmiter("Not Data");
    }
}

void WordBase::getWords(Core *ptrCore){
    query->exec("SELECT aeng, bother FROM words WHERE cdone = 0 ORDER BY RANDOM() LIMIT 1;");
    if(query->next()){
        ptrCore->wordToUpLabel = query->value(0).toString();
        ptrCore->wordToDownLabel = query->value(1).toString();
    }else{
        ptrCore->wordToUpLabel = "Not Data";
        ptrCore->wordToDownLabel = "Not Data";
    }
}
