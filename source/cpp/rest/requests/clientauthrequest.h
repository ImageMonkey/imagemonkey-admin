#ifndef CLIENTAUTH_REQUEST_H
#define CLIENTAUTH_REQUEST_H

#include "basicrequest.h"

class ClientAuthRequest : public BasicRequest{
    Q_OBJECT
public:
    ClientAuthRequest();
    ~ClientAuthRequest();

};

#endif /*CLIENTAUTH_REQUEST_H*/
