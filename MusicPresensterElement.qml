import QtQuick 2.9
import QtQuick.Controls 2.2

Item {

    id: root
    property int  presenterId: 0
    property bool valveON: false
    property bool valveLevelControl: false
    property int valveLevel: 0
    property  int presenerGroup: 0
    property bool ledON: false
    property string ledColor: "red"
    property int  ledMode: 0
    property double scale : 1.0
    property int edgePixelLength: 8
    property bool  odd: false
    property int initialX: 0
    property int  initialY: 0

//    property bool idOn: false

    onLedColorChanged: {
//        console.log("Led color changed")
//        console.log("color: " + ledColor)
    }


    Component.onCompleted: {

        root.initialX = x
        root.initialY = y

    }


    onValveLevelChanged: {
//        if(valveLevelControl)
//        {
//            root.x = root.initialX -(valveLevel+1)/255 * 3
//            root.y = root.initialY - (valveLevel+1) /255 * 3
//        }

    }
//    onValveLevelControlChanged: {
//        // console.trace()
//        console.log(valveLevelControl)
//    }


    Rectangle
    {
        id: theElement
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: root.valveLevelControl ? (root.edgePixelLength - 2) * scale + (valveLevel+1) /255 * 6  : root.edgePixelLength * scale
        height: root.valveLevelControl ? (root.edgePixelLength - 2)* scale + (valveLevel+1) /255 * 6  : root.edgePixelLength * scale
//        radius: root.valveLevelControl == true ? ((root.edgePixelLength * scale) /2 /255 * valveLevel) +5 :(root.edgePixelLength * scale) /2
        radius:  root.edgePixelLength * scale / 2
//        color: root.valveON == true ? "black" : "white"

        color: {
            if(root.valveLevelControl)
            {
                if(root.valveLevel === 0)
                {
                    "white"
                }
                else
                {
                    "black"
                }
            }
            else
            {
                if(root.valveON)
                {
                    "black"
                }
                else
                {
                    "white"
                }
            }
        }

        border.width:  2
        border.color: root.ledON? root.ledColor : "#515151"

    }

}

