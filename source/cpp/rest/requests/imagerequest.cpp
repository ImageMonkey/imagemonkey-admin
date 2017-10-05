#include "imagerequest.h"
#include <QFile>
#include <QUrlQuery>
#include <QUuid>

GetAllUnverifiedPicturesRequest::GetAllUnverifiedPicturesRequest()
    : ClientAuthRequest()
{
    QUrl url(m_baseUrl + "unverified/donation");
    m_request->setUrl(url);
}

GetAllUnverifiedPicturesRequest::~GetAllUnverifiedPicturesRequest(){
}

VerifyPictureRequest::VerifyPictureRequest()
    : ClientAuthRequest()
{
    QUrl url(m_baseUrl + "unverified/donation");
    m_request->setUrl(url);
}

void VerifyPictureRequest::set(const QString& uuid, const bool isGood){
    QUrl url(m_baseUrl + "unverified/donation/" + uuid + "/" + ((isGood) ? "good" : "bad"));
    m_request->setUrl(url);
}

VerifyPictureRequest::~VerifyPictureRequest(){
}
