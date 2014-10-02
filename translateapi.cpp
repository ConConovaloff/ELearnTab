#include "translateapi.h"
#include <iostream>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QObject>
#include <QDebug>
#include <QRegExp>

TranslateAPI::TranslateAPI()
{
    manager = new QNetworkAccessManager();
    eventLoop = new QEventLoop();
    rx = new QRegExp("\"trans\":\"(.*)\"");
    rx->setMinimal(1); // lazy regexp
}

QString TranslateAPI::translate(QString engInText){
    QString url = "http://translate.google.ru/translate_a/t?client=x&text=" + engInText + "&hl=en&sl=en&tl=ru";
    http = manager->get(QNetworkRequest(url));
    QObject::connect(http,SIGNAL(finished()),eventLoop, SLOT(quit()));
    eventLoop->exec();
    // Получен ответ
    QString answer = QString::fromUtf8(http->readAll());
    int pos = rx->indexIn(answer);
    if(pos > -1){
        return rx->cap(1);
    }else{
        return "Not Data";
    }
}
