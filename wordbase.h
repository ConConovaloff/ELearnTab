#ifndef WORDBASE_H
#define WORDBASE_H

#include <QObject>
#include "core.h"

class Core;
class QSqlDatabase;
class QSqlQuery;

class WordBase : public QObject
{
    Q_OBJECT
public:
    explicit WordBase(QString inBaseName, QObject *parent = 0);
    void randomLine(Core *ptrCore);
    void reverseRandomLine(Core *ptrCore);
    void changeBase(QString inText);
    void addWords(QString engInText, QString otherInText);
    void studiedWords(QString engInText);
    QString translateFromDB(QString engInText);
    void getWords(Core *ptrCore);
signals:


public slots:

private:
    QSqlDatabase *db;
    QSqlQuery *query;
};

#endif // WORDBASE_H
