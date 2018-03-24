#ifndef _IMAGEREQUEST_H_
#define _IMAGEREQUEST_H_

#include "sslrequest.h"
#include "basicrequest.h"
#include "clientauthrequest.h"

class GetAllUnverifiedPicturesRequest : public ClientAuthRequest{
    Q_OBJECT
public:
    GetAllUnverifiedPicturesRequest();
    Q_INVOKABLE void setFilter(const QString& imageProvider);
    ~GetAllUnverifiedPicturesRequest();
};

class VerifyPictureRequest : public ClientAuthRequest{
    Q_OBJECT
public:
    VerifyPictureRequest();
    Q_INVOKABLE void set(const QString& uuid, const bool isGood);
    ~VerifyPictureRequest();
};

class DeletePictureRequest : public ClientAuthRequest{
    Q_OBJECT
public:
    DeletePictureRequest();
    Q_INVOKABLE void set(const QString& uuid);
    ~DeletePictureRequest();
};

#endif /*_IMAGEREQUEST_H_*/
