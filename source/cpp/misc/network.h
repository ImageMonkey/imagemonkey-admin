#ifndef NETWORK_H
#define NETWORK_H

#include <QQmlNetworkAccessManagerFactory>
#include <QNetworkReply>
#include "secrets.h"

class CustomNetworkAccessManager : public QNetworkAccessManager {
    Q_OBJECT
public:
    CustomNetworkAccessManager(QObject* parent = 0);
protected:
    QNetworkReply *createRequest(Operation op, const QNetworkRequest &req, QIODevice * outgoingData=0);
};

class CustomNetworkAccessManagerFactory : public QQmlNetworkAccessManagerFactory
{
public:
    virtual QNetworkAccessManager *create(QObject *parent);
};



#endif // NETWORK_H
