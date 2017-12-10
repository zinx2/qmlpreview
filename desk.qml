import QtQuick 2.0

Rectangle {
    width: 300
    height: 300
    color: "transparent"
    Text {
        width: 300
        height: 300
        font.pointSize: 15
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: "SELECT QML FILE."
        color: "white"
    }

    MouseArea {
        id:ma
        anchors.fill: parent
        onClicked: {
//            console.log("clicked");
//            console.log(applicationData.getCurrentDateTime());
//            console.log(applicationData.log());
//            console.log(scr.log());
        }
    }
}
