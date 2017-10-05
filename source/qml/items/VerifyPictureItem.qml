import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import com.imagemonkeyadmin.imagemonkeyadmin 1.0
import "../basiccomponents"

Item{
    id: verifyPictureItem

    signal isActive()

    onIsActive: {
        if(!internal.initialized){
            internal.initialized = true;
            internal.pendingRequests = {}
            internal.unverifiedDonations = []
            internal.currentUnverifiedDonationIdx = 0;
            restAPI.getAllUnverifiedPictures();
        }
    }

    QtObject{
        id: internal
        property var pendingRequests;
        property bool initialized: false;
        property var unverifiedDonations;
        property int currentUnverifiedDonationIdx : 0;
    }

    HttpsRequestWorkerThread{
        id: restAPI
        signal getAllUnverifiedPictures();
        signal getUnverifiedPicture(string uuid);
        signal verifyPicture(bool valid);

        onVerifyPicture: {
            progressLoadingBar.visible = true;
            var verifyPictureRequest = Qt.createQmlObject('import com.imagemonkeyadmin.imagemonkeyadmin 1.0; VerifyPictureRequest{}',
                                                   restAPI);
            verifyPictureRequest.set(internal.unverifiedDonations[(internal.currentUnverifiedDonationIdx - 1)]["uuid"], valid);
            internal.pendingRequests[verifyPictureRequest.getUniqueRequestId()] = "verify";
            restAPI.post(verifyPictureRequest);
        }

        onGetAllUnverifiedPictures: {
            progressLoadingBar.visible = true;
            var getAllUnverifiedPicturesRequest = Qt.createQmlObject('import com.imagemonkeyadmin.imagemonkeyadmin 1.0; GetAllUnverifiedPicturesRequest{}',
                                                   restAPI);
            internal.pendingRequests[getAllUnverifiedPicturesRequest.getUniqueRequestId()] = "allUnverified";
            restAPI.get(getAllUnverifiedPicturesRequest);
        }

    }

    function getNextUnverifiedPicture(){
        if(internal.unverifiedDonations !== null){
            if(internal.currentUnverifiedDonationIdx < internal.unverifiedDonations.length){
                img.source = ConnectionSettings.getBaseUrl() + "unverified/donation/" + internal.unverifiedDonations[internal.currentUnverifiedDonationIdx]["uuid"];
                label.text = internal.unverifiedDonations[internal.currentUnverifiedDonationIdx]["label"];
                internal.currentUnverifiedDonationIdx += 1;
                yesButton.visible = true;
                noButton.visible = true;
                label.visible = true;
            }
            else {
                yesButton.visible = false;
                noButton.visible = false;
                label.visible = false;
                img.visible = false;
            }
        }
    }

    Connections {
        target: restAPI
        onResultReady: {
            if(errorCode === 0){
                if(uniqueRequestId in internal.pendingRequests){
                    var reqType = internal.pendingRequests[uniqueRequestId];
                    if(reqType === "allUnverified"){
                        internal.unverifiedDonations = JSON.parse(result);
                        progressLoadingBar.visible = false;

                        getNextUnverifiedPicture();
                    }
                    else if(reqType === "verify"){
                        progressLoadingBar.visible = false;
                        getNextUnverifiedPicture();
                    }

                    delete internal.pendingRequests[uniqueRequestId];
                }
            }
            else{
                if(uniqueRequestId in internal.pendingRequests){
                    delete internal.pendingRequests[uniqueRequestId];
                }
            }
        }
    }

    Text{
        id: header
        anchors.top: parent.top
        anchors.topMargin: 5 * settings.pixelDensity
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 13 * settings.pixelDensity
        font.bold: true
        text: qsTr("ImageMonkey - Admin")
    }

    Text{
        id: label
        anchors.bottom: yesButton.top
        anchors.bottomMargin: 5 * settings.pixelDensity
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 10 * settings.pixelDensity
        font.bold: true
    }

    Image{
        id: img
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: label.top
        anchors.bottomMargin: 5 * settings.pixelDensity
        anchors.topMargin: 5 * settings.pixelDensity
        fillMode: Image.PreserveAspectFit
        asynchronous: true
    }

    Button{
        id: yesButton
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 10 * settings.pixelDensity
        anchors.horizontalCenterOffset: + ((yesButton.width/2) + (10 * settings.pixelDensity))
        Material.foreground: "white"
        Material.background: "green"
        height: 17 * settings.pixelDensity
        width: 50 * settings.pixelDensity
        text: qsTr("YES")
        visible: false
        onClicked: {
            restAPI.verifyPicture(true);
        }
    }

    Button{
        id: noButton
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 10 * settings.pixelDensity
        anchors.horizontalCenterOffset: - ((noButton.width/2) + (10 * settings.pixelDensity))
        Material.foreground: "white"
        Material.background: "red"
        height: 17 * settings.pixelDensity
        width: 50 * settings.pixelDensity
        text: qsTr("NO")
        visible: false
        onClicked: {
            //currently we do nothing but get the next picture
            getNextUnverifiedPicture();
        }
    }

    Text{
        id: error
        anchors.centerIn: parent
        width: parent.width - (10 * settings.pixelDensity)
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 6 * settings.pixelDensity
        text: qsTr("Nothing found")
        font.bold: true
        visible: false
    }

    LoadingIndicator{
        id: progressLoadingBar
        anchors.centerIn: parent
        visible: true
    }

}
