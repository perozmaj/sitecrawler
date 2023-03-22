import QtQuick 2.5
import QtQuick.Controls 2.3
ApplicationWindow {
    //title of the application
    id: root
    title: qsTr("Crawler Demo")
    width: 800
    height: 600
    visible: true
    color: "white"
    Rectangle
    {
        id: txtInputObj
        anchors.top: parent.top
        width:  400
        height: 50
        color: "black"
        TextInput
        {
            id: buttonTextInput
            anchors.fill: parent
            anchors.centerIn: parent
            color: "white"
            font.pointSize: 10
            width:5
            text: "https://doc.qt.io/qt-6/classes.html"
            horizontalAlignment: Text.AlignHCenter
        }
    }
    Rectangle
    {
        id: buttonRect
        anchors.top: parent.top
        anchors.left: txtInputObj.right
        height: 50
        width: 400
        Button
        {
            anchors.fill: parent
            text: "crawl"
            onClicked:
            {
                siteCrawlerModel.crawlClicked(buttonTextInput.text)
            }
        }
    }
    Rectangle
    {
        anchors.top: buttonRect.bottom
        anchors.topMargin: 10
        width: parent.width
        height: 600
        clip: true
        ListView
        {
            width: parent.width
            height: parent.height
            anchors.centerIn: parent
            ScrollBar.vertical: ScrollBar { }
            model: siteCrawlerModel
            anchors.topMargin: 10
            spacing: 5
            delegate: Button {
                width: root.width
                Text {
                    id: txtLink
                    text: model.link
                    width: 20
                    anchors.left: parent.left
                }
                onClicked:
                {
                    console.log(model.data)
                }

            }
        }
    }
}
