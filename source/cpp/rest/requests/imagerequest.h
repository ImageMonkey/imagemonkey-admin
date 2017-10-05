#ifndef _IMAGEREQUEST_H_
#define _IMAGEREQUEST_H_

#include "sslrequest.h"
#include "basicrequest.h"
#include "clientauthrequest.h"

class GetAllUnverifiedPicturesRequest : public ClientAuthRequest{
    Q_OBJECT
public:
    GetAllUnverifiedPicturesRequest();
    ~GetAllUnverifiedPicturesRequest();
};

class VerifyPictureRequest : public ClientAuthRequest{
    Q_OBJECT
public:
    VerifyPictureRequest();
    Q_INVOKABLE void set(const QString& uuid, const bool isGood);
    ~VerifyPictureRequest();
};


#endif /*_IMAGEREQUEST_H_*/
