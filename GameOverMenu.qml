import QtQuick 2.0
import QtQuick.Controls 2.15
Rectangle {
    id: root
    property int score
    property int steps
    signal newGame()
    color: "#CC666666"
    MouseArea{
        anchors.fill: parent
    }
    Rectangle{
        width: parent.width < parent.height ? parent.width/2 : parent.height/3
        height: width*0.7
        anchors.centerIn: parent
        Column{
            anchors.fill: parent
            Text{
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Score: "+root.score
            }
            Text{
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Steps: "+root.steps
            }
            Button{
                 anchors.horizontalCenter: parent.horizontalCenter
                 width: parent.width*0.8
                 height: width*0.5
                 text: "New Game"
                 onClicked: root.newGame()
            }
        }
    }
}
