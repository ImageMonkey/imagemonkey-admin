#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "main.h"
#include "executiontarget.h"
#include "rest/settings.h"
#include "misc/network.h"

#ifdef Q_OS_ANDROID
#include <QtAndroid>
#endif

/*
class CustomNetworkAccessManager : public QNetworkAccessManager {
        Q_OBJECT
public:
    CustomNetworkAccessManager(QObject* parent = 0)
        : QNetworkAccessManager(parent)
    {
    }
    CustomNetworkAccessManager::~CustomNetworkAccessManager(){

    }

protected:
    QNetworkReply *createRequest(Operation op, const QNetworkRequest &req, QIODevice * outgoingData=0)
    {

        QNetworkRequest newReq(req);
        newReq.setRawHeader("X-Client-Id", X_CLIENT_ID.toUtf8());
        newReq.setRawHeader("X-Client-Secret", X_CLIENT_SECRET.toUtf8());

        QNetworkReply *reply = QNetworkAccessManager::createRequest(op, newReq, outgoingData);
        return reply;
    }

//private:
//    QString __userAgent;
};

class CustomNetworkAccessManagerFactory : public QQmlNetworkAccessManagerFactory
{
public:
    virtual QNetworkAccessManager *create(QObject *parent);
};

QNetworkAccessManager* CustomNetworkAccessManagerFactory::create(QObject *parent)
{
    CustomNetworkAccessManager* manager = new CustomNetworkAccessManager(parent);

    return manager;
}*/

int main(int argc, char *argv[])
{
    const QString applicationName = "imagemonkeyadmin";
    const QString applicationVersion = "1.0.0";
    const QString g_uri = "com." + applicationName + "." + applicationName;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Material");

    if(EXECUTIONTARGET == ExcecutionTarget::LOCAL){
        ConnectionSettings::instance()->setProtocol(ConnectionSettings::HTTP);
        ConnectionSettings::instance()->setIpAddress("127.0.0.1");
        ConnectionSettings::instance()->setPort(8081);
        ConnectionSettings::instance()->setVerifySSL(false);
        ConnectionSettings::instance()->setApiVersion(1);
        ConnectionSettings::instance()->setEnforceSecureCiphers(false);
    }
    else if(EXECUTIONTARGET == ExcecutionTarget::TEST){
        ConnectionSettings::instance()->setIpAddress("change me");
        ConnectionSettings::instance()->setPort(443);
        ConnectionSettings::instance()->setVerifySSL(true);
        ConnectionSettings::instance()->setApiVersion(1);
        ConnectionSettings::instance()->setEnforceSecureCiphers(true);
    }
    else if(EXECUTIONTARGET == ExcecutionTarget::PRODUCTION){
        ConnectionSettings::instance()->setIpAddress("api.imagemonkey.io");
        ConnectionSettings::instance()->setPort(443);
        ConnectionSettings::instance()->setVerifySSL(true);
        ConnectionSettings::instance()->setApiVersion(1);
        ConnectionSettings::instance()->setEnforceSecureCiphers(true);
    }

    app.setApplicationName(applicationName);
    app.setApplicationVersion(applicationVersion);

    QString executionTarget = "";
    if(EXECUTIONTARGET == ExcecutionTarget::LOCAL){
        app.setOrganizationName(applicationName+"-local");
        executionTarget = "Local";
    }
    else if(EXECUTIONTARGET == ExcecutionTarget::TEST){
        app.setOrganizationName(applicationName+"-test");
        executionTarget = "Test";
    }
    else if(EXECUTIONTARGET == ExcecutionTarget::PRODUCTION){
        app.setOrganizationName(applicationName);
        executionTarget = "Production";
    }
    app.setOrganizationDomain(g_uri);

    QQmlApplicationEngine engine;

    qmlRegisterType<VerifyPictureRequest>(g_uri.toStdString().c_str(), 1, 0, "VerifyPictureRequest");
    qmlRegisterType<DeletePictureRequest>(g_uri.toStdString().c_str(), 1, 0, "DeletePictureRequest");

    qmlRegisterType<GetAllUnverifiedPicturesRequest>(g_uri.toStdString().c_str(), 1, 0, "GetAllUnverifiedPicturesRequest");
    qmlRegisterType<HttpsRequestWorker>(g_uri.toStdString().c_str(), 1, 0, "HttpsRequestWorker");
    qmlRegisterType<HttpsRequestWorkerThread>(g_uri.toStdString().c_str(), 1, 0, "HttpsRequestWorkerThread");

    qmlRegisterSingletonType<ConnectionSettings>(g_uri.toStdString().c_str(), 1, 0, "ConnectionSettings",
                                                                           ConnectionSettings::connectionSettingsProvider);

    engine.addImportPath(QStringLiteral("qrc:/"));
    engine.load(QUrl(QLatin1String("qrc:/source/qml/main.qml")));
    engine.setNetworkAccessManagerFactory(new CustomNetworkAccessManagerFactory());

    //the splashscreen was defined as "sticky" with the following line
    //meta-data android:name="android.app.splash_screen_sticky" android:value="true"
    //in the AndroidManifest. After the heavy lifting is done (i.e engine is loaded)
    //we can hide the splashscreen. This removes the white flickering that otherwise would
    //occur during the engine loads its data
#ifdef Q_OS_ANDROID
    QtAndroid::hideSplashScreen();
#endif

    return app.exec();
}
