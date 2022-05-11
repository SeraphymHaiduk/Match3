import QtQuick 2.0
import QtQml 2.15
import QtQuick.Controls 2.15
import Plugins.ModelPlugin 1.0

GridView{
    id: root
    anchors.centerIn: parent
    height: parent.width/model.columnsCount > parent.height/model.rowsCount? parent.height : cellHeight*model.rowsCount
    width: parent.width/model.columnsCount < parent.height/model.rowsCount ? parent.width : cellWidth*model.columnsCount
    cellWidth: parent.width/model.columnsCount < parent.height/model.rowsCount ? parent.width/model.columnsCount : parent.height/model.rowsCount
    cellHeight: cellWidth

    property int moveDuration: 400
    property int pressDuration: 200
    property int unpressDuration: pressDuration
    property int unpressWrongDuration: pressDuration*5
    property int deleteDuration: pressDuration*2

    property int draggedItemIndex: -1
    property int draggedItemX
    property int draggedItemY

    property int circleW: cellWidth*0.9
    property int circleH: cellHeight*0.9

    property int horizontalOffset: 0
    property int verticalOffset: 0
    property bool isOffsetHorizontal
    property int offsetIndex: -1

    property bool moveTransitionEnabled: true
    signal offset(int x, int y)

    Item{
        id:dndContainer
    }
    visible: true
    Connections{
        target: root.model
        function onMatchesHappened(){
            moveTransitionEnabled = true
            mouseHandler.enabled = false
            animationTimer.exec(root.moveDuration,function(){
                root.model.readyToDisappear()
                animationTimer.exec(root.deleteDuration,function(){
                    root.model.readyToRemove()
                })
            })
        }
        function onMatchesNotHappened(){
            mouseHandler.enabled = true
        }
    }
    interactive: false


    add:Transition{
        NumberAnimation{
            properties: "y"
            from: -cellHeight-(root.height-to)
            duration: root.moveDuration
        }
    }
    move:Transition{
        enabled: root.moveTransitionEnabled
        NumberAnimation{
            properties: "x,y"
            duration:  root.moveDuration
        }
    }
    displaced : Transition {
        enabled: root.moveTransitionEnabled
        NumberAnimation{
            properties: "x,y"
            duration: root.moveDuration
        }
    }
    Timer{
        id: animationTimer
        repeat: false
        property var functionToExec
        function exec(duration, foo){
            animationTimer.functionToExec = foo
            animationTimer.interval = duration
            animationTimer.start()
        }
        onTriggered: {
            functionToExec()
        }
    }



    delegate: Item{
        id: tile
        width: cellWidth
        height: cellHeight
        visible: true
        Connections{
            target: root
            function onOffset(x,y){
                if(index === root.offsetIndex){
                    if(x !== 0){
                        circle.anchors.horizontalCenterOffset = -x
                    }
                    else if(y !== 0){
                        circle.anchors.verticalCenterOffset = -y
                    }

                }
                else{
                    circle.anchors.horizontalCenterOffset = 0
                    circle.anchors.verticalCenterOffset = 0
                }
            }
        }

        Rectangle{
            id: circle
            width: circleW
            height: circleH
            anchors.centerIn: tile

            radius: width/2
            color: colorName
            visible: true
            clip:true

            states: [
                State{
                    name: "pressed"
                    when: model.state === MyModel.ElementState.Pressed
                    PropertyChanges {
                        target: circle
                        parent: index === root.draggedItemIndex ? dndContainer : parent
                        x: index === root.draggedItemIndex ? root.draggedItemX : x
                        y: index === root.draggedItemIndex ? root.draggedItemY : y
                        anchors.centerIn: index === root.draggedItemIndex ? undefined : parent
                    }
                    PropertyChanges {
                        target: root
                        draggedItemX: mouseHandler.mouseX - circleW/2
                        draggedItemY: mouseHandler.mouseY - circleH/2
                    }
                },
                State{
                    name: "wrong"
                    when: model.state === MyModel.ElementState.Wrong
                },
                State{
                    name: "deleted"
                    when: model.state === MyModel.ElementState.Deleted
                    PropertyChanges {
                        target: circle
                        opacity: 0
                        anchors.margins: -tile.width*0.05
                    }
                }
            ]

            transitions: [
                Transition {        //press
                    to: "pressed"
                },
                Transition {        //wrong
                    from: "*"
                    to: "wrong"
                    SequentialAnimation{
                        NumberAnimation{
                            target: circle
                            property: "scale"
                            duration: root.unpressWrongDuration/4*1
                            easing.type: Easing.InSine
                            to: 0.8
                        }
                        NumberAnimation {
                            target: circle
                            properties: "scale"
                            to: 1
                            duration: root.unpressWrongDuration/4*3
                            easing.type: Easing.OutElastic
                        }
                    }
                    onRunningChanged: console.log("wrong")
                },
                Transition{         //delete
                    to: "deleted"
                    NumberAnimation{
                        properties: "anchors.margins,opacity"
                        duration: root.deleteDuration
                    }
                }

            ]

        }
    }

    MouseArea{
        id: mouseHandler
        anchors.fill: parent
        onReleased: {
            if(root.draggedItemIndex !== -1){
                root.model.setState(root.indexAt(mouseX,mouseY),MyModel.ElementState.Pressed)
                if(root.indexAt(mouseX,mouseY) === root.draggedItemIndex){
                    root.model.pressOn(root.draggedItemIndex)
                }
                else{
                    root.model.pressOn(root.offsetIndex)
                }
                root.draggedItemIndex = -1
            }
            root.offsetIndex = -1
            root.offset(0,0)
            root.moveTransitionEnabled = false
        }
        onPositionChanged: {
            if(root.draggedItemIndex !== -1){
                var j = root.draggedItemIndex%root.model.columnsCount
                var i = Math.trunc(root.draggedItemIndex/root.model.columnsCount)

                var normalX = cellWidth * j + (cellWidth-circleW)/2
                var normalY = cellHeight * i + (cellHeight-circleH)/2

                var xBigLimit, yBigLimit, xLittleLimit, yLittleLimit, centerY, centerX

                if(mouseX > (j+2) * cellWidth - cellWidth/2 ||
                    mouseX > cellWidth * root.model.columnsCount ||
                    mouseX < (j-1) * cellWidth + cellWidth/2){
                    xBigLimit = false
                }
                else{
                    if(mouseX > (j+1) * cellWidth + cellWidth/8 ||
                        mouseX < j * cellWidth + cellWidth/8){
                        xLittleLimit = false
                    }
                    else{
                        xLittleLimit = true
                    }
                    xBigLimit = true
                }

                if(mouseY < (i-1) * cellHeight + cellHeight/2 ||
                    mouseY > (i+2) * cellHeight - cellHeight/2 ||
                    mouseY > cellHeight * root.model.rowsCount){
                    yBigLimit = false
                }
                else{
                    if(mouseY < i * cellHeight - cellHeight/8 ||
                       mouseY > (i+1) * cellHeight + cellHeight/8 ){
                        yLittleLimit = false
                    }
                    else{
                        yLittleLimit = true
                    }
                    yBigLimit = true
                }
                if(xLittleLimit && yLittleLimit){
                    root.isOffsetHorizontal = Math.abs(root.horizontalOffset) > Math.abs(root.verticalOffset)
                }

                centerY = root.isOffsetHorizontal
                centerX = !root.isOffsetHorizontal

                if(xBigLimit && mouseX > 0+circleW/2 && mouseX < root.width - circleW/2){
                    root.draggedItemX = centerX ? normalX : mouseX - circleW/2
                    root.horizontalOffset = mouseX - (normalX + circleW/2)
                }
                if(yBigLimit && mouseY > 0+circleH/2 && mouseY < root.height - circleH/2){
                    root.draggedItemY = centerY ? normalY : mouseY - circleH/2
                    root.verticalOffset = mouseY - (normalY + circleH/2)
                }

                var indx
                var offset
                if(root.isOffsetHorizontal){
                    offset = root.horizontalOffset
                    if(root.horizontalOffset > 0){
                        indx = root.draggedItemIndex + 1
                    }
                    else{
                        indx = root.draggedItemIndex - 1
                    }
                    if(indx >= 0 && indx < root.model.columnsCount*root.model.rowsCount){
                        if(root.draggedItemIndex%root.model.columnsCount === 0 && indx === root.draggedItemIndex-1 ||
                           (root.draggedItemIndex+1)%root.model.columnsCount === 0 && indx === root.draggedItemIndex+1){
                            root.offsetIndex = -1
                        }
                        else{
                            root.offsetIndex = indx
                        }
                        root.offset(offset,0)
                    }
                }
                else{
                    offset = root.verticalOffset
                    if(root.verticalOffset > 0){
                        indx = root.draggedItemIndex + root.model.columnsCount
                    }
                    else{
                        indx =  root.draggedItemIndex - root.model.columnsCount
                    }
                    if(indx >= 0 && indx < root.model.columnsCount*root.model.rowsCount){
                        root.offsetIndex = indx
                        root.offset(0,offset)
                    }
                }
            }
        }

        onPressed: {
            root.draggedItemIndex = root.indexAt(mouseX,mouseY)
            root.model.pressOn(root.draggedItemIndex)
        }


    }
}
