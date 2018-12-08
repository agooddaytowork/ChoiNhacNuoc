import QtQuick 2.9

Item {
    id: root
    property int  edgePixelLength: 400
    property string frameBackGroundColor: "transparent"

    Rectangle{
        width: root.edgePixelLength
        height: root.edgePixelLength

        color: root.frameBackGroundColor
        opacity: 1
    }
}
