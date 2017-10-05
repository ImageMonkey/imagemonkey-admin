#include "clientauthrequest.h"
#include "../../misc/secrets.h"

ClientAuthRequest::ClientAuthRequest()
    : BasicRequest()
{
    m_request->setRawHeader("X-Client-Id", X_CLIENT_ID.toUtf8());
    m_request->setRawHeader("X-Client-Secret", X_CLIENT_SECRET.toUtf8());
}

ClientAuthRequest::~ClientAuthRequest(){
}
