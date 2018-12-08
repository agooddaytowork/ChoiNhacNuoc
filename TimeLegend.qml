import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id:root

    property int timeLegendWidth: 500
    property int timeLegendHeight: 20
    property int tick: 5
    property int  miniTick: 2
    property int  tickWidth: 2
    property string  color: "black"
    property int fromMs: 0
    property int  toMs: 5000

    signal requestTimeIndicatorPosition(int position)






    function tickLabel(tickIndex)
    {
        var duration = Math.abs(root.toMs - root.fromMs)

        var theTickLabelNumber = (root.fromMs) + duration* tickIndex/(root.tick)

       var theTickLabel = ""

        if(duration <= 1000)
        {
            theTickLabel = parseInt(theTickLabelNumber) + " ms"
        }
        else if(duration <= 60000)
        {
            theTickLabel = parseFloat(theTickLabelNumber/1000).toFixed(1)+ "s"
        }
        else {
            theTickLabel = parseInt(theTickLabelNumber/60000)+"m"+parseInt(theTickLabelNumber%60000/1000)+"s"
        }

        return theTickLabel

    }



    Rectangle
    {
        id: timeLegendBG
        width: root.width
        height: root.height
        color: "transparent"

        MouseArea{
            id: mouseArea
            anchors.fill: parent

            onClicked: {
                root.requestTimeIndicatorPosition(mouseX/root.width * Math.abs(root.toMs - root.fromMs) + root.fromMs)
            }
        }

        Rectangle{

            width: root.width
            height: 2
            color: root.color
            anchors.bottom: parent.bottom
        }

        Repeater{
            id: drawTickRepeater
            model: root.tick + 1
            delegate: Rectangle{
                id: tickDelegate
                property int  drawTickDelegateIndex: index


                width: root.tickWidth
                height: root.height * 0.9
                color: root.color
                anchors.bottom: parent.bottom

                x: root.width/root.tick * index
                Label   {
                    id: theLabel
                    text: root.tickLabel(tickDelegate.drawTickDelegateIndex)

                    anchors.horizontalCenter: parent.horizontalCenter
                    y:-15

                    Connections{
                        target: root
                        onFromMsChanged:
                        {
                            theLabel.text = root.tickLabel(tickDelegate.drawTickDelegateIndex)
                        }

                        onToMsChanged:
                        {
                             theLabel.text = root.tickLabel(tickDelegate.drawTickDelegateIndex)
                        }

                    }
                }

            }
        }
        Repeater
        {
            id: drawMiniTickRepeater
            model: root.tick * root.miniTick + 1
            delegate: Rectangle{
                id: miniTickDelegate
                width: root.tickWidth
                height: root.height/3
                color: root.color
                anchors.bottom: parent.bottom
                x: (root.width/root.tick / root.miniTick  * index)

            }
        }


    }

}
