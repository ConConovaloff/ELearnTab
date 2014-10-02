#ifndef TRANSLATEAPI_H
#define TRANSLATEAPI_H

#include <QString>

class QNetworkAccessManager;
class QNetworkReply;
class QEventLoop;

class TranslateAPI
{
public:
    TranslateAPI();
    QString translate(QString inText);

private:
    QNetworkAccessManager *manager;
    QNetworkReply *http;
    QEventLoop *eventLoop;
    QRegExp *rx;
};

#endif // TRANSLATEAPI_H
