import QtQuick 2.9
import MusicPresenter 1.0

Item {

    id: root
    property int  groupID: 0
    property ListModel presenterModel: ListModel{}
    property double  group6P1: 1.1463414634146343
    property double  group6P2: 0.05746815829737426
    property double  group6P3: 2.4878048780487805
    property double  group6P4: 0.157

    Component.onCompleted: {
        presenterModel.clear()
        createGroup(root.groupID)
    }

    onGroup6P1Changed:
    {
        presenterModel.clear()
        createGroup_6()
    }

    onGroup6P2Changed:
    {
        presenterModel.clear()
        createGroup_6()
    }
    onGroup6P3Changed:
    {
        presenterModel.clear()
        createGroup_6()
    }
    onGroup6P4Changed:
    {
        presenterList_5.clear()
        createGroup_6()
    }

    function createGroup(i)
    {
        presenterModel.clear()
        switch(i)
        {
        case 0: createGroup_1()
            break
        case 1: createGroup_2()
            break
        case 2: createGroup_3()
            break
        case 3: createGroup_4()
            break
        case 4: createGroup_5()
            break
        case 5: createGroup_6()
            break
        case 6: createGroup_7()
            break
        case 7: createGroup_8()
            break
        case 8: createGroup_9()
            break

        }
    }

    function createGroup_1()
    {
        //        presenterModel.clear()
        //        presenterModel.append([
        //                                  {"presenterId":0,
        //                                      "xPos" : theFrame.edgePixelLength /2,
        //                                      "yPos" : theFrame.edgePixelLength/2}
        //                              ])

        presenterList_0.appendItem(0,theFrame.edgePixelLength /2,theFrame.edgePixelLength/2 )
    }

    function createGroup_2()
    {
        for (var i = 0; i < 8; i++)
        {
            //            presenterModel.append({"presenterId":i,
            //                                      "xPos" : x_polarToCatersian(meterToPixel(2),Math.PI / 4 * i),
            //                                      "yPos" : y_polarToCatersian(meterToPixel(2),Math.PI / 4  * i)})

            presenterList_1.appendItem(1,
                                       x_polarToCatersian(meterToPixel(2),Math.PI / 4 * i),
                                       y_polarToCatersian(meterToPixel(2),Math.PI / 4  * i))
        }
    }

    function createGroup_3()
    {
        for (var i = 0; i < 16; i++)
        {
            //            presenterModel.append({"presenterId":i,
            //                                      "xPos" : x_polarToCatersian(meterToPixel(4),Math.PI / 8 * i),
            //                                      "yPos" : y_polarToCatersian(meterToPixel(4),Math.PI / 8  * i)})

            presenterList_2.appendItem(2,
                                       x_polarToCatersian(meterToPixel(4),Math.PI / 8 * i),
                                       y_polarToCatersian(meterToPixel(4),Math.PI / 8  * i))
        }
    }

    function createGroup_4()
    {
        for (var i = 0; i < 32; i++)
        {
            //            presenterModel.append({"presenterId":i,
            //                                      "xPos" : x_polarToCatersian(meterToPixel(10.7/2),Math.PI / 16 * i),
            //                                      "yPos" : y_polarToCatersian(meterToPixel(10.7/2),Math.PI / 16  * i)})

            presenterList_3.appendItem(3,
                                       x_polarToCatersian(meterToPixel(10.7/2),Math.PI / 16 * i),
                                       y_polarToCatersian(meterToPixel(10.7/2),Math.PI / 16  * i))
        }
    }

    function createGroup_5()
    {
        for (var i = 0; i < 12; i++)
        {
            //            presenterModel.append({"presenterId":i,
            //                                      "xPos" : x_polarToCatersian(meterToPixel(10) ,Math.PI / 6 * i + (Math.PI /12)),
            //                                      "yPos" : y_polarToCatersian(meterToPixel(10),Math.PI / 6 * i + (Math.PI /12))})


            presenterList_4.appendItem(4,
                                       x_polarToCatersian(meterToPixel(10) ,Math.PI / 6 * i + (Math.PI /12)),
                                       y_polarToCatersian(meterToPixel(10),Math.PI / 6 * i + (Math.PI /12)))
        }
    }

    function createGroup_6()
    {
        var p1 = root.group6P1
        var p2 = root.group6P2
        var p3 = root.group6P3
        var p4 = root.group6P4
        for (var i = 0; i < 8; i++)
        {

            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel(35/2),Math.PI / 4 * i),
                                                       y_polarToCatersian(meterToPixel(35/2),Math.PI / 4  * i))

            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel((35 -(p1*1))/2),Math.PI / 4 * i - p2 ),
                                                       y_polarToCatersian(meterToPixel((35 -(p1*1))/2),Math.PI / 4  * i - p2))


            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel((35 -(p1*1))/2),Math.PI / 4 * i + p2 ),
                                                       y_polarToCatersian(meterToPixel((35 -(p1*1))/2),Math.PI / 4  * i + p2))

            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel((35 -(p1*2))/2),Math.PI / 4 * i - p2 *2),
                                                       y_polarToCatersian(meterToPixel((35 -(p1*2))/2),Math.PI / 4  * i - p2 *2))

            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel((35 -(p1*2))/2),Math.PI / 4 * i + p2 *2),
                                                       y_polarToCatersian(meterToPixel((35 -(p1*2))/2),Math.PI / 4  * i + p2 *2))

            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel((35 -(p1*3))/2),Math.PI / 4 * i - p2 *3),
                                                       y_polarToCatersian(meterToPixel((35 -(p1*3))/2),Math.PI / 4  * i - p2 *3))

            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel((35 -(p1*3))/2),Math.PI / 4 * i + p2 *3),
                                                       y_polarToCatersian(meterToPixel((35 -(p1*3))/2),Math.PI / 4  * i + p2 *3))

            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel((35 -(p1*4))/2),Math.PI / 4 * i - p2 *4),
                                                       y_polarToCatersian(meterToPixel((35 -(p1*4))/2),Math.PI / 4  * i - p2 *4))

            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel((35 -(p1*4))/2),Math.PI / 4 * i + p2 *4),
                                                       y_polarToCatersian(meterToPixel((35 -(p1*4))/2),Math.PI / 4  * i + p2 *4))

            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel((35 -(p1*5))/2),Math.PI / 4 * i - p2 *5),
                                                       y_polarToCatersian(meterToPixel((35 -(p1*5))/2),Math.PI / 4  * i - p2 *5))

            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel((35 -(p1*5))/2),Math.PI / 4 * i + p2 *5),
                                                       y_polarToCatersian(meterToPixel((35 -(p1*5))/2),Math.PI / 4  * i + p2 *5))



            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel((35 -(p1*6))/2),Math.PI / 4 * i - p2 *6),
                                                       y_polarToCatersian(meterToPixel((35 -(p1*6))/2),Math.PI / 4  * i - p2 *6))



            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel((35 -(p1*6))/2),Math.PI / 4 * i + p2 *6),
                                                       y_polarToCatersian(meterToPixel((35 -(p1*6))/2),Math.PI / 4  * i + p2 *6))


            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel((35 -(p1*7))/2),Math.PI / 4 * i - p2 *7),
                                                       y_polarToCatersian(meterToPixel((35 -(p1*7))/2),Math.PI / 4  * i - p2 *7))

            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel((35 -(p1*8))/2),Math.PI / 4 * i - p2 *8),
                                                       y_polarToCatersian(meterToPixel((35 -(p1*8))/2),Math.PI / 4  * i - p2 *8))
            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel((35 -(p1*9))/2),Math.PI / 4 * i - p2 *9),
                                                       y_polarToCatersian(meterToPixel((35 -(p1*9))/2),Math.PI / 4  * i - p2 *9))
            presenterList_5.appenItemGroup6(i%2 == 0 ? false:true,
                                                       x_polarToCatersian(meterToPixel((35 -(p1*10))/2),Math.PI / 4 * i - p2 *10),
                                                       y_polarToCatersian(meterToPixel((35 -(p1*10))/2),Math.PI / 4  * i - p2 *10))


            presenterList_5.appenItemGroup6(i%2 == 0 ? true:false,
                                                       x_polarToCatersian(meterToPixel((35 -(p3*5))/2),Math.PI / 4 * i + p4 ),
                                                       y_polarToCatersian(meterToPixel((35 -(p3*5))/2),Math.PI / 4  * i + p4 ))
            presenterList_5.appenItemGroup6(i%2 == 0 ? true:false,
                                                       x_polarToCatersian(meterToPixel((35 -(p3*6))/2),Math.PI / 4 * i + p4 ),
                                                       y_polarToCatersian(meterToPixel((35 -(p3*6))/2),Math.PI / 4  * i + p4 ))
            presenterList_5.appenItemGroup6(i%2 == 0 ? true:false,
                                                       x_polarToCatersian(meterToPixel((35 -(p3*7))/2),Math.PI / 4 * i + p4 ),
                                                       y_polarToCatersian(meterToPixel((35 -(p3*7))/2),Math.PI / 4  * i + p4 ))
            presenterList_5.appenItemGroup6(i%2 == 0 ? true:false,
                                                       x_polarToCatersian(meterToPixel((35 -(p3*8))/2),Math.PI / 4 * i + p4),
                                                       y_polarToCatersian(meterToPixel((35 -(p3*8))/2),Math.PI / 4  * i + p4 ))
            presenterList_5.appenItemGroup6(i%2 == 0 ? true:false,
                                                       x_polarToCatersian(meterToPixel((35 -(p3*9))/2),Math.PI / 4 * i + p4 ),
                                                       y_polarToCatersian(meterToPixel((35 -(p3*9))/2),Math.PI / 4  * i + p4 ))

        }
    }

    function createGroup_7()
    {
        for (var i = 0; i < 16; i++)
        {
            //            presenterModel.append({"presenterId":i,
            //                                      "xPos" : x_polarToCatersian(meterToPixel(23/2) ,Math.PI / 8 * i ),
            //                                      "yPos" : y_polarToCatersian(meterToPixel(23/2) ,Math.PI / 8 * i )})

            presenterList_6.appendItem(6,
                                       x_polarToCatersian(meterToPixel(23/2) ,Math.PI / 8 * i ),
                                       y_polarToCatersian(meterToPixel(23/2) ,Math.PI / 8 * i ))
        }
    }

    function createGroup_8()
    {
        for (var i = 0; i < 8; i++)
        {
            //            presenterModel.append({"presenterId":i,
            //                                      "xPos" : x_polarToCatersian(meterToPixel(31.5/2) ,Math.PI / 4 * i),
            //                                      "yPos" : y_polarToCatersian(meterToPixel(31.5/2),Math.PI / 4  * i)})

            presenterList_7.appendItem(7,
                                       x_polarToCatersian(meterToPixel(31.5/2) ,(Math.PI / 4 ) * i + Math.PI/8),
                                       y_polarToCatersian(meterToPixel(31.5/2),(Math.PI / 4 )  * i + Math.PI/8))
        }
    }

    function createGroup_9()
    {
        for (var i = 0; i < 8; i++)
        {
            //            presenterModel.append({"presenterId":i,
            //                                      "xPos" : x_polarToCatersian(meterToPixel(2.5/2),Math.PI / 4 * i),
            //                                      "yPos" : y_polarToCatersian(meterToPixel(2.5/2),Math.PI / 4  * i)})

            presenterList_8.appendItem(8,
                                       x_polarToCatersian(meterToPixel(2.5/2),Math.PI / 4 * i),
                                       y_polarToCatersian(meterToPixel(2.5/2),Math.PI / 4  * i))
        }
        for ( i = 0; i < 16; i++)
        {
            //            presenterModel.append({"presenterId":i,
            //                                      "xPos" : x_polarToCatersian(meterToPixel(3),Math.PI / 8 * i),
            //                                      "yPos" : y_polarToCatersian(meterToPixel(3),Math.PI / 8  * i)})

            presenterList_8.appendItem(8,
                                       x_polarToCatersian(meterToPixel(3),Math.PI / 8 * i),
                                       y_polarToCatersian(meterToPixel(3),Math.PI / 8  * i))
        }
    }

    function x_polarToCatersian(r, angle)
    {

        return r * Math.cos(angle) + theFrame.edgePixelLength /2
    }

    function y_polarToCatersian(r, angle)
    {

        return r * Math.sin(angle) + theFrame.edgePixelLength /2
    }

    function meterToPixel(met)
    {
        return (42/ theFrame.edgePixelLength -10) * met
    }

    function returnPresenterList(id)
    {
        switch(id)
        {
        case 0:
            return presenterList_0

        case 1:
            return presenterList_1
        case 2:
            return presenterList_2

        case 3:
            return presenterList_3

        case 4:
            return presenterList_4

        case 5:
            return presenterList_5

        case 6:
            return presenterList_6

        case 7:
            return presenterList_7

        case 8:
            return presenterList_8

        }
    }



    MusicPresensterFrame{

        id: theFrame


        Repeater{
            id: groupRepeater
            model: MusicPresenterModel
            {
                list: root.returnPresenterList(root.groupID)
            }

            delegate: MusicPresensterElement
            {


                presenterId: theId
                x: XPos
                y: YPos
                odd: Odd
                valveON: ValveOnOff
                ledON: LedOnOff
                ledColor: LEDColor
                valveLevelControl: Inverter
                valveLevel: InverterLevel
//                idOn: root.groupID ==5 ? true: false
//                ledColor:{
//                    if(root.groupID ==5 )
//                    {
//                        if(Odd)
//                        {
//                            "red"
//                        }
//                        else
//                        {
//                            "black"
//                        }
//                    }
//                    else
//                    {
//                        "red"
//                    }
//                }




            }
        }
    }

    ListModel{
        id: presenterGroupData

    }

}



