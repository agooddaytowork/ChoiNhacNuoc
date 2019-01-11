import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: root

    property int  timeLineToMs: 0
    property int  timeLineFromMs: 0
    property int  timeSlotToMs: 0
    property int  timeSlotFromMs: 0
    property int  timeLineWidth: 0
    property int  duration: 0
    property int  slotDuration: 0
    property int  valveMode: 0
    property int  dmLedMode: 0
    signal deleteTimeSlot()
    signal checkCollision()
    signal copyTimeSlot()
    property bool collided: false
    property bool rightCollision: false
    property bool  edgeSelected: false
    property bool timeSlotSelected: false
    signal timeSlotSelect()
    property string valveModeName: "-"
    property int valveSpeed: 0
    property string ledModeName: "+"
    property int  ledSpeed: 0
    property string ledColorList: "#8e8e8e;#8e8e8e"
    property bool useBuiltIntLedEffect: false
    property bool  valveForceRepeat: false
    property int valveForceRepeatTimes: 0
    property bool ledForceRepeat: false
    property int  ledForceRepeatTimes: 0



    onLedColorListChanged: {
//        // console.trace()
        firstColorRec.color = returnColor(0)
        secondColorRec.color = returnColor(1)
    }


    x: root.refreshX()
    width: root.refreshWidth()

    onValveModeChanged: {
//        // console.trace()
//        console.log("current valve Mode: " + root.valveMode)
    }

    Component.onCompleted: {
      returnColor(0)
    }

    function returnColor(index)
    {

        var colorArray = root.ledColorList.split(";")
        if(colorArray.length <= index)
        {
            return "#8e8e8e"
        }
        return colorArray[index]
    }

    function refreshPosition()
    {
        root.x = refreshPosition()
        root.width = refreshWidth()
    }

    function refreshWidth()
    {
        var newWidth = Math.abs(root.timeSlotToMs - root.timeSlotFromMs) / Math.abs(root.timeLineToMs - root.timeLineFromMs) * root.timeLineWidth

        var newPos =  (root.timeSlotFromMs  - root.timeLineFromMs) / Math.abs(root.timeLineToMs - root.timeLineFromMs) * root.timeLineWidth

        if(newPos <= 0 && Math.abs(newPos) <= newWidth)
        {
            return newWidth = newWidth - Math.abs(newPos)
        }
        else if(newPos <=0 && Math.abs(newPos) > newWidth)
        {
            return 0
        }
        else if((newPos+newWidth) >= root.timeLineWidth)
        {
            return newWidth = newWidth - Math.abs(newPos+newWidth-root.timeLineWidth)
        }
        else
        {
            return newWidth
        }
    }

    function refreshX()
    {
        var newPos =  (root.timeSlotFromMs  - root.timeLineFromMs) / Math.abs(root.timeLineToMs - root.timeLineFromMs) * root.timeLineWidth

        if(newPos <0)
        {
            return 0
        }
        else
        {
            return newPos
        }
    }
    Rectangle{
        id: theTimeSlot
        anchors.fill: parent
        property int  xOffsetValue: 0
        z:1

        Rectangle{
            id: infoRec
            width: 90
            height: 60
            anchors.top: parent.top
            anchors.left: parent.left
            color: "transparent"
            z:3
            visible: inforColumn.width -60 >= theTimeSlot.width ? false: true
            Column{
                id: inforColumn
                anchors.fill: parent
                spacing: 3
                anchors.topMargin: 3
                anchors.leftMargin: 2
                Row
                {
                    Label{
                        text: "V: "
                        visible: inforColumn.width >= theTimeSlot.width ? false: true
                        color: "white"

                        onWidthChanged: {
//                            console.log("width: " + width)
                        }
                    }
                    Label{
                        id: valveNameLabel
                        text: root.valveModeName.replace(".bin","")
                        color: "white"
                        wrapMode: Label.WrapAnywhere

                        Connections{
                            target: root
                            onWidthChanged:
                            {
                               valveNameLabel.width = root.width
                            }
                        }

                    }
                }
                Row
                {
                     visible: inforColumn.width >= theTimeSlot.width ? false: true
                    Label{
                        text: "VS: "
                        color: "white"
                    }
                    Label{
                        text: root.valveSpeed
                        color: "white"
                    }
                    Label{
                        text: " |FR: "
                        color: "white"
                    }
                    Label{
                        text: root.valveForceRepeat ? "Y" : "N"
                        color: "white"
                    }
                    Label{
                        text: " |R: "
                        color: "white"
                    }
                    Label{
                        text: root.valveForceRepeatTimes
                        color: "white"
                    }
                }

                Row
                {
                    spacing: 2
                    Label{
                        text: "L: "
                        visible: inforColumn.width >= theTimeSlot.width ? false: true
                        color: "white"
                    }
                    Label{
                        id: ledModeNameLabel
                        text: root.ledModeName.replace(".bin","")
                        color: "white"

                        wrapMode: Label.WrapAnywhere

                        Connections{
                            target: root
                            onWidthChanged:
                            {
                               ledModeNameLabel.width = root.width
                            }
                        }

                    }

                        Rectangle{
                            id: firstColorRec
                            visible: root.useBuiltIntLedEffect
                            width: 15
                            height: 15
                            radius: 7.5
                            border.width: 1
                            border.color: "white"
                            color: returnColor(0)
                        }
                        Rectangle{
                            id: secondColorRec
                            visible: root.useBuiltIntLedEffect
                            width: 15
                            height: 15
                            radius: 7.5
                            border.width: 1
                            border.color: "white"
                            color: returnColor(1)
                        }

                }
                Row
                {
                     visible: inforColumn.width >= theTimeSlot.width ? false: true
                    Label{
                        text: "LS: "
                        color: "white"
                    }
                    Label{
                        text: root.ledSpeed
                        color: "white"
                    }
                    Label{
                        text: " |FR: "
                        color: "white"
                    }
                    Label{
                        text: root.ledForceRepeat ? "Y":"N"
                        color: "white"
                    }
                    Label{
                        text: " |R: "
                        color: "white"
                    }
                    Label{
                        text: root.ledForceRepeatTimes
                        color: "white"
                    }
                }


            }


        }

        MouseArea{
            id: timeSlotMouseArea
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            property int  mouseOffset: 0
            property bool  selected: false
            property bool fromEdge: false // only valid when root.edgeSelected = true
            hoverEnabled: true

            onPressed:
            {
                if(pressedButtons & Qt.RightButton)
                {
                    theTimeSlotMenu.open()
                }
                if(pressedButtons & Qt.LeftButton && timeSlotMouseArea.cursorShape === Qt.ArrowCursor)
                {
                    timeSlotMouseArea.mouseOffset = mouseX
                    timeSlotMouseArea.selected = true
                    root.edgeSelected = false
                }
                else
                {
                    timeSlotMouseArea.mouseOffset = mouseX
                    root.edgeSelected = true
                    timeSlotMouseArea.selected = false
                }

            }
            onReleased: {

                timeSlotMouseArea.selected = false
                root.edgeSelected = false
            }

            onMouseXChanged: {

                // SLIDE FUNCTION
                if(pressedButtons & Qt.LeftButton && timeSlotMouseArea.selected)
                {
                    root.slotDuration = Math.abs(root.timeSlotFromMs - root.timeSlotToMs)
                    root.timeSlotFromMs = (root.x - timeSlotMouseArea.mouseOffset +mouseX) /  root.timeLineWidth * Math.abs(root.timeLineToMs - root.timeLineFromMs) + root.timeLineFromMs


                    if(root.timeSlotFromMs <0)
                    {
                        root.timeSlotFromMs = 0
                    }
                    root.timeSlotToMs = root.timeSlotFromMs + root.slotDuration

                    root.checkCollision()
                }
                // SLOT EDGE DETECTION
                if(Math.abs(mouseX) <= 3 )
                {
                    timeSlotMouseArea.cursorShape = Qt.IBeamCursor
                    timeSlotMouseArea.fromEdge = true
                }
                else if(Math.abs(mouseX) >= theTimeSlot.width-3)
                {
                    timeSlotMouseArea.cursorShape = Qt.IBeamCursor
                    timeSlotMouseArea.fromEdge = false
                }

                else
                {
                    timeSlotMouseArea.cursorShape = Qt.ArrowCursor
                }

                if(root.edgeSelected && pressedButtons & Qt.LeftButton)
                {


                    if(timeSlotMouseArea.fromEdge)
                    {
                        var previousFromMs = root.timeSlotFromMs
                        var previousTimeSlotDuration = root.slotDuration
                        root.timeSlotFromMs = (root.x  +mouseX) /  root.timeLineWidth * Math.abs(root.timeLineToMs - root.timeLineFromMs) + root.timeLineFromMs
                        if(collided && !root.rightCollision)
                        {
                            if(previousFromMs > root.timeSlotFromMs)
                            {
                                root.timeSlotFromMs = previousFromMs - 1
                                root.slotDuration = previousTimeSlotDuration
                            }

                        }
                        else
                        {
                            root.slotDuration = Math.abs(root.timeSlotToMs - root.timeSlotFromMs)
                        }

                    }
                    else
                    {
                        var previousToMs = root.timeSlotToMs
                        previousTimeSlotDuration = root.slotDuration

                        root.timeSlotToMs  =  (root.x  +mouseX) /  root.timeLineWidth * Math.abs(root.timeLineToMs - root.timeLineFromMs) + root.timeLineFromMs

                        if(collided && root.rightCollision)
                        {
                            if(previousToMs < root.timeSlotToMs){
                                root.timeSlotToMs = previousToMs + 1
                                root.slotDuration = previousTimeSlotDuration
                            }
                        }
                        else
                        {
                            root.slotDuration = Math.abs(root.timeSlotToMs - root.timeSlotFromMs)
                        }
                    }
                    root.checkCollision()
                }

            }

            onClicked: {
                // implement shit here
                root.timeSlotSelect()
            }
        }
        Menu
        {
            id: theTimeSlotMenu
            MenuItem{
                text: qsTr("Copy")
                onClicked: {
                    root.copyTimeSlot()
                }
            }

            MenuItem{
                text: qsTr("Delete")
                onClicked: {

                    root.deleteTimeSlot();
                }
            }
        }
        color:  root.timeSlotSelected ? "orange":"black"
        border.width: 1
        border.color: "white"

    }
}
