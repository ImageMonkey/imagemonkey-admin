#include "network.h"

QNetworkAccessManager* CustomNetworkAccessManagerFactory::create(QObject *parent)
{
    CustomNetworkAccessManager* manager = new CustomNetworkAccessManager(parent);

    return manager;
}

CustomNetworkAccessManager::CustomNetworkAccessManager(QObject *parent)
    : QNetworkAccessManager(parent)
{
}


QNetworkReply* CustomNetworkAccessManager::createRequest(Operation op, const QNetworkRequest &req, QIODevice * outgoingData)
{

    QNetworkRequest newReq(req);
    newReq.setRawHeader("X-Client-Id", X_CLIENT_ID.toUtf8());
    newReq.setRawHeader("X-Client-Secret", X_CLIENT_SECRET.toUtf8());

    QNetworkReply *reply = QNetworkAccessManager::createRequest(op, newReq, outgoingData);
    return reply;
}
