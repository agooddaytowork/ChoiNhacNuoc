import QtQuick 2.9

Item {

    id: root
    property int  duration: 5000
    property int  fromMs: 0
    property int  toMs: 5000
    property int  position: 2500
    signal changeFromAndToMoment(int from, int to)
    signal timeIndicatorPositionChanged(int mYposition)
    property bool  movable: false
    property bool  autoPlay: false
    property int  deltaFromPreviousPosition: 0


    Rectangle{
        id: indicator
        width: 2
        color: "red"
        height: root.height
        x: 0



        MouseArea{
            id: mouseArea
            anchors.fill: parent

            hoverEnabled: true


            onEntered: {
                mouseArea.cursorShape = Qt.IBeamCursor

            }
            onExited: {


            }
            onPressed: {
                root.movable = true

            }
            onReleased: {
                root.movable = false
            }

            onMouseXChanged: {

                if(root.movable)
                {

                    var newX = 0
                    newX = indicator.x + mouseArea.mouseX
                    var newPosition = parseInt(newX * Math.abs(root.toMs - root.fromMs) / root.width) + root.fromMs

                    if(newPosition < 0)
                    {
                        newPosition = 0
                    }
                    if(newPosition > root.duration)
                    {
                        newPosition = root.duration
                    }

                    root.timeIndicatorPositionChanged(newPosition)

                }
            }

        }
    }

    onPositionChanged: {


        indicator.x = (root.position - root.fromMs) * (root.width/ Math.abs(root.toMs - root.fromMs))

            if(root.position < root.fromMs || root.position > root.toMs && root.position > 0 && root.position < root.duration)
            {
                indicator.visible = false
            }
            else
            {
                indicator.visible = true
            }

        if(root.autoPlay)
        {
            if((root.position - root.fromMs) / Math.abs(root.toMs - root.fromMs) >= 0.8 && root.toMs != root.duration)
            {
                root.changeFromAndToMoment(root.fromMs+ root.deltaFromPreviousPosition, root.toMs + root.deltaFromPreviousPosition)
            }
        }


    }

    onFromMsChanged: {

        indicator.x = (root.position - root.fromMs) * (root.width/ Math.abs(root.toMs - root.fromMs))
        if(root.position < root.fromMs || root.position > root.toMs)
        {
            indicator.visible = false
        }
        else
        {
            indicator.visible = true
        }

        root.movable = false

    }
    onToMsChanged: {
        indicator.x = (root.position - root.fromMs) * (root.width/ Math.abs(root.toMs - root.fromMs))
        if(root.position < root.fromMs || root.position > root.toMs)
        {
            indicator.visible = false
        }
        else
        {
            indicator.visible = true
        }
        root.movable = false
    }
}
