#include "serialframebuffer.h"
#include <QColor>
#include <QDebug>

SerialFrameBuffer::SerialFrameBuffer(QObject *parent): QObject(parent), mSerialOutputEnable(false)
{

}


void SerialFrameBuffer::SerialFrameChangedHandler(const int &group, const int &frameNo, const PresenterFrame &theFrame)
{
    switch (group) {
    case 0:
        group1Handler(frameNo,theFrame);
        break;
    case 1:
        group2Handler(frameNo,theFrame);
        break;
    case 2:
        group3Handler(frameNo,theFrame);
        break;
    case 3:
        group4Handler(frameNo,theFrame);
        break;
    case 4:
        group5Handler(frameNo,theFrame);
        break;
    case 5:
        group6Handler(frameNo,theFrame);
        break;
    case 6:
        group7Handler(frameNo,theFrame);
        break;
    case 7:
        group8Handler(frameNo,theFrame);
        break;
    case 8:
        group9Handler(frameNo,theFrame);
        break;
    }
}

void SerialFrameBuffer::group1Handler(const int &frameNo,const PresenterFrame &theFrame)
{
    SingleSerialFrame serialFrame = mData.at(frameNo);

    serialFrame.V_CH1_I = static_cast<char>(theFrame.InverterLevel);


    if(theFrame.LedSync && theFrame.InverterLevel == 0 && !theFrame.LedSyncDelay[0])
    {
        QColor theColor(0,0,0);
        serialFrame.L_CH1[0] = static_cast<char>(theColor.red());
        serialFrame.L_CH1[1] = static_cast<char>(theColor.green());
        serialFrame.L_CH1[2] = static_cast<char>(theColor.blue());
    }
    else
    {
        serialFrame.L_CH1[0] = static_cast<char>(QColor(theFrame.LedColors.at(0)).red());
        serialFrame.L_CH1[1] = static_cast<char>(QColor(theFrame.LedColors.at(0)).green());
        serialFrame.L_CH1[2] = static_cast<char>(QColor(theFrame.LedColors.at(0)).blue());
    }







    mData[frameNo] = serialFrame;
}

void SerialFrameBuffer::group2Handler(const int &frameNo,const PresenterFrame &theFrame)
{
    SingleSerialFrame serialFrame =mData.at(frameNo);

    char ValveToggle = 0x00;

    for(int i = 0; i < theFrame.ValveChannels; i++)
    {
        if(theFrame.ValveOnOff.at(i))
        {
            ValveToggle |= (static_cast<char>(1) << static_cast<char>(i));
        }
    }

    serialFrame.V_CH2_T = ValveToggle;

    if(theFrame.LedSync && ValveToggle == 0x00 && !theFrame.LedSyncDelay[0])
    {
        QColor theColor(0,0,0);
        serialFrame.L_CH2[0] = static_cast<char>(theColor.red());
        serialFrame.L_CH2[1] = static_cast<char>(theColor.green());
        serialFrame.L_CH2[2] = static_cast<char>(theColor.blue());
    }
    else
    {
        serialFrame.L_CH2[0] = static_cast<char>(QColor(theFrame.LedColors.at(0)).red());
        serialFrame.L_CH2[1] = static_cast<char>(QColor(theFrame.LedColors.at(0)).green());
        serialFrame.L_CH2[2] = static_cast<char>(QColor(theFrame.LedColors.at(0)).blue());
    }

    mData[frameNo] = serialFrame;

}

void SerialFrameBuffer::group3Handler(const int &frameNo,const PresenterFrame &theFrame)
{
    SingleSerialFrame serialFrame =mData.at(frameNo);

    char ValveToggle_Low = 0x00;
    char ValveToggle_High = 0x00;

    for(int i = 0; i < theFrame.ValveChannels; i++)
    {

        if(i <= 7)
        {
            if(theFrame.ValveOnOff.at(i))
            {
                ValveToggle_Low |= (static_cast<char>(1) << static_cast<char>(i));
            }
        }
        else
        {
            if(theFrame.ValveOnOff.at(i))
            {
                ValveToggle_High |= (static_cast<char>(1) << static_cast<char>(i-8));
            }
        }
    }
    serialFrame.V_CH3_T_L = ValveToggle_Low;
    serialFrame.V_CH3_T_H = ValveToggle_High;

    if(theFrame.LedSync && ValveToggle_Low == 0x00 && ValveToggle_High == 0x00 && !theFrame.LedSyncDelay[0] )
    {
        QColor theColor(0,0,0);
        serialFrame.L_CH3[0] = static_cast<char>(theColor.red());
        serialFrame.L_CH3[1] = static_cast<char>(theColor.green());
        serialFrame.L_CH3[2] = static_cast<char>(theColor.blue());
    }
    else
    {
        serialFrame.L_CH3[0] = static_cast<char>(QColor(theFrame.LedColors.at(0)).red());
        serialFrame.L_CH3[1] = static_cast<char>(QColor(theFrame.LedColors.at(0)).green());
        serialFrame.L_CH3[2] = static_cast<char>(QColor(theFrame.LedColors.at(0)).blue());
    }



    mData[frameNo] = serialFrame;
}


void SerialFrameBuffer::group4Handler(const int &frameNo,const PresenterFrame &theFrame)
{
    SingleSerialFrame serialFrame =mData.at(frameNo);

    serialFrame.V_CH4_I = static_cast<char>(theFrame.InverterLevel);

    if(theFrame.LedSync && theFrame.InverterLevel == 0 && !theFrame.LedSyncDelay[0])
    {
        QColor theColor(0,0,0);

        serialFrame.L_CH4[0] = static_cast<char>(theColor.red());
        serialFrame.L_CH4[1] = static_cast<char>(theColor.green());
        serialFrame.L_CH4[2] = static_cast<char>(theColor.blue());
    }
    else
    {
        serialFrame.L_CH4[0] = static_cast<char>(QColor(theFrame.LedColors.at(0)).red());
        serialFrame.L_CH4[1] = static_cast<char>(QColor(theFrame.LedColors.at(0)).green());
        serialFrame.L_CH4[2] = static_cast<char>(QColor(theFrame.LedColors.at(0)).blue());
    }


    mData[frameNo] = serialFrame;
}

void SerialFrameBuffer::group5Handler(const int &frameNo,const PresenterFrame &theFrame)
{
    SingleSerialFrame serialFrame =mData.at(frameNo);

    if(theFrame.ValveOnOff.at(0))
    {
        serialFrame.V_CH5_CH7_CH9_T |= static_cast<char>(1 << 0);
    }
    else
    {
        serialFrame.V_CH5_CH7_CH9_T &=~(1 << 0);
    }

    if(theFrame.LedSync && !theFrame.ValveOnOff.at(0) && !theFrame.LedSyncDelay[0])
    {
        QColor theColor(0,0,0);
        serialFrame.L_CH5[0] = static_cast<char>(theColor.red());
        serialFrame.L_CH5[1] = static_cast<char>(theColor.green());
        serialFrame.L_CH5[2] = static_cast<char>(theColor.blue());

    }
    else
    {
        serialFrame.L_CH5[0] = static_cast<char>(QColor(theFrame.LedColors.at(0)).red());
        serialFrame.L_CH5[1] = static_cast<char>(QColor(theFrame.LedColors.at(0)).green());
        serialFrame.L_CH5[2] = static_cast<char>(QColor(theFrame.LedColors.at(0)).blue());
    }

    mData[frameNo] = serialFrame;
}

void SerialFrameBuffer::group6Handler(const int &frameNo,const PresenterFrame &theFrame)
{
    SingleSerialFrame serialFrame =mData.at(frameNo);

    serialFrame.V_CH6_I_0 = static_cast<char>(theFrame.InverterLevel);
    serialFrame.V_CH6_I_1 =static_cast<char>(theFrame.InverterLevel1);

    serialFrame.L_CH6_L[0] = static_cast<char>(QColor(theFrame.LedColors.at(0)).red());
    serialFrame.L_CH6_L[1] = static_cast<char>(QColor(theFrame.LedColors.at(0)).green());
    serialFrame.L_CH6_L[2] = static_cast<char>(QColor(theFrame.LedColors.at(0)).blue());

    serialFrame.L_CH6_H[0] = static_cast<char>(QColor(theFrame.LedColors.at(1)).red());
    serialFrame.L_CH6_H[1] = static_cast<char>(QColor(theFrame.LedColors.at(1)).green());
    serialFrame.L_CH6_H[2] = static_cast<char>(QColor(theFrame.LedColors.at(1)).blue());

    if(theFrame.LedSync )
    {
        QColor theColor(0,0,0);

        if(theFrame.InverterLevel ==0 && !theFrame.LedSyncDelay[0])
        {
            serialFrame.L_CH6_L[0] = static_cast<char>(theColor.red());
            serialFrame.L_CH6_L[1] = static_cast<char>(theColor.green());
            serialFrame.L_CH6_L[2] = static_cast<char>(theColor.blue());
        }
        if(theFrame.InverterLevel1 == 0 && !theFrame.LedSyncDelay[1])
        {
            serialFrame.L_CH6_H[0] = static_cast<char>(theColor.red());
            serialFrame.L_CH6_H[1] = static_cast<char>(theColor.green());
            serialFrame.L_CH6_H[2] = static_cast<char>(theColor.blue());
        }
    }
    mData[frameNo] = serialFrame;
}

void SerialFrameBuffer::group7Handler(const int &frameNo,const PresenterFrame &theFrame)
{
    SingleSerialFrame serialFrame =mData.at(frameNo);


    if(theFrame.ValveOnOff.at(0))
    {
        serialFrame.V_CH5_CH7_CH9_T |= 1 << 1;
    }
    else
    {
        serialFrame.V_CH5_CH7_CH9_T &=~(1 << 1);
    }
    if(theFrame.ValveOnOff.at(1))
    {
        serialFrame.V_CH5_CH7_CH9_T |= 1 << 2;
    }
    else
    {
        serialFrame.V_CH5_CH7_CH9_T &=~(1 << 2);
    }

    serialFrame.L_CH7_L[0] = static_cast<char>(QColor(theFrame.LedColors.at(0)).red());
    serialFrame.L_CH7_L[1] = static_cast<char>(QColor(theFrame.LedColors.at(0)).green());
    serialFrame.L_CH7_L[2] = static_cast<char>(QColor(theFrame.LedColors.at(0)).blue());

    serialFrame.L_CH7_H[0] = static_cast<char>(QColor(theFrame.LedColors.at(1)).red());
    serialFrame.L_CH7_H[1] = static_cast<char>(QColor(theFrame.LedColors.at(1)).green());
    serialFrame.L_CH7_H[2] = static_cast<char>(QColor(theFrame.LedColors.at(1)).blue());

    if(theFrame.LedSync)
    {
        QColor theColor(0,0,0);
        if(!theFrame.ValveOnOff.at(0) && !theFrame.LedSyncDelay[0])
        {
            serialFrame.L_CH7_L[0] = static_cast<char>(theColor.red());
            serialFrame.L_CH7_L[1] = static_cast<char>(theColor.green());
            serialFrame.L_CH7_L[2] = static_cast<char>(theColor.blue());
        }
        if(!theFrame.ValveOnOff.at(1) && !theFrame.LedSyncDelay[1])
        {
            serialFrame.L_CH7_H[0] = static_cast<char>(theColor.red());
            serialFrame.L_CH7_H[1] = static_cast<char>(theColor.green());
            serialFrame.L_CH7_H[2] = static_cast<char>(theColor.blue());
        }

    }

    mData[frameNo] = serialFrame;
}


void SerialFrameBuffer::group8Handler(const int &frameNo,const PresenterFrame &theFrame)
{
    SingleSerialFrame serialFrame =mData.at(frameNo);


    char ValveToggle = 0x00;


    serialFrame.L_CH8_0[0] = static_cast<char>(QColor(theFrame.LedColors.at(0)).red());
    serialFrame.L_CH8_0[1] = static_cast<char>(QColor(theFrame.LedColors.at(0)).green());
    serialFrame.L_CH8_0[2] = static_cast<char>(QColor(theFrame.LedColors.at(0)).blue());



    serialFrame.L_CH8_1[0] = static_cast<char>(QColor(theFrame.LedColors.at(1)).red());
    serialFrame.L_CH8_1[1] = static_cast<char>(QColor(theFrame.LedColors.at(1)).green());
    serialFrame.L_CH8_1[2] = static_cast<char>(QColor(theFrame.LedColors.at(1)).blue());

    serialFrame.L_CH8_2[0] = static_cast<char>(QColor(theFrame.LedColors.at(2)).red());
    serialFrame.L_CH8_2[1] = static_cast<char>(QColor(theFrame.LedColors.at(2)).green());
    serialFrame.L_CH8_2[2] = static_cast<char>(QColor(theFrame.LedColors.at(2)).blue());

    serialFrame.L_CH8_3[0] = static_cast<char>(QColor(theFrame.LedColors.at(3)).red());
    serialFrame.L_CH8_3[1] = static_cast<char>(QColor(theFrame.LedColors.at(3)).green());
    serialFrame.L_CH8_3[2] = static_cast<char>(QColor(theFrame.LedColors.at(3)).blue());

    serialFrame.L_CH8_4[0] = static_cast<char>(QColor(theFrame.LedColors.at(4)).red());
    serialFrame.L_CH8_4[1] = static_cast<char>(QColor(theFrame.LedColors.at(4)).green());
    serialFrame.L_CH8_4[2] = static_cast<char>(QColor(theFrame.LedColors.at(4)).blue());

    serialFrame.L_CH8_5[0] = static_cast<char>(QColor(theFrame.LedColors.at(5)).red());
    serialFrame.L_CH8_5[1] = static_cast<char>(QColor(theFrame.LedColors.at(5)).green());
    serialFrame.L_CH8_5[2] = static_cast<char>(QColor(theFrame.LedColors.at(5)).blue());

    serialFrame.L_CH8_6[0] = static_cast<char>(QColor(theFrame.LedColors.at(6)).red());
    serialFrame.L_CH8_6[1] = static_cast<char>(QColor(theFrame.LedColors.at(6)).green());
    serialFrame.L_CH8_6[2] = static_cast<char>(QColor(theFrame.LedColors.at(6)).blue());

    serialFrame.L_CH8_7[0] = static_cast<char>(QColor(theFrame.LedColors.at(7)).red());
    serialFrame.L_CH8_7[1] = static_cast<char>(QColor(theFrame.LedColors.at(7)).green());
    serialFrame.L_CH8_7[2] = static_cast<char>(QColor(theFrame.LedColors.at(7)).blue());




    for(int i = 0; i < theFrame.ValveChannels; i++)
    {
        if(theFrame.ValveOnOff.at(i))
        {
            ValveToggle |= (static_cast<char>(1) << static_cast<char>(i));




        }
        else
        {
            if(theFrame.LedSync)
            {
                switch (i) {

                case 0:
                    if(!theFrame.LedSyncDelay[0])
                    {
                        serialFrame.L_CH8_0[0] = 0x00;
                        serialFrame.L_CH8_0[1] = 0x00;
                        serialFrame.L_CH8_0[2] = 0x00;
                    }

                    break;
                case 1:

                    if(!theFrame.LedSyncDelay[1])
                    {
                        serialFrame.L_CH8_1[0] = 0x00;
                        serialFrame.L_CH8_1[1] = 0x00;
                        serialFrame.L_CH8_1[2] = 0x00;
                    }
                    break;
                case 2:
                    if(!theFrame.LedSyncDelay[2])
                    {
                        serialFrame.L_CH8_2[0] = 0x00;
                        serialFrame.L_CH8_2[1] = 0x00;
                        serialFrame.L_CH8_2[2] = 0x00;
                    }
                    break;
                case 3:


                    if(!theFrame.LedSyncDelay[3])
                    {
                        serialFrame.L_CH8_3[0] = 0x00;
                        serialFrame.L_CH8_3[1] = 0x00;
                        serialFrame.L_CH8_3[2] = 0x00;
                    }
                    break;
                case 4:

                    if(!theFrame.LedSyncDelay[4])
                    {
                        serialFrame.L_CH8_4[0] = 0x00;
                        serialFrame.L_CH8_4[1] = 0x00;
                        serialFrame.L_CH8_4[2] = 0x00;
                    }
                    break;
                case 5:
                    if(!theFrame.LedSyncDelay[5])
                    {
                        serialFrame.L_CH8_5[0] = 0x00;
                        serialFrame.L_CH8_5[1] = 0x00;
                        serialFrame.L_CH8_5[2] = 0x00;
                    }
                    break;
                case 6:
                    if(!theFrame.LedSyncDelay[6])
                    {
                        serialFrame.L_CH8_6[0] = 0x00;
                        serialFrame.L_CH8_6[1] = 0x00;
                        serialFrame.L_CH8_6[2] = 0x00;
                    }
                    break;
                case 7:
                    if(!theFrame.LedSyncDelay[7])
                    {
                        serialFrame.L_CH8_7[0] = 0x00;
                        serialFrame.L_CH8_7[1] = 0x00;
                        serialFrame.L_CH8_7[2] = 0x00;
                    }
                    break;

                }
            }
        }


    }


    serialFrame.V_CH8_T = ValveToggle;


    mData[frameNo] = serialFrame;
}


void SerialFrameBuffer::group9Handler(const int &frameNo,const PresenterFrame &theFrame)
{
    SingleSerialFrame serialFrame =mData.at(frameNo);

    serialFrame.L_CH9_L[0] = static_cast<char>(QColor(theFrame.LedColors.at(0)).red());
    serialFrame.L_CH9_L[1] = static_cast<char>(QColor(theFrame.LedColors.at(0)).green());
    serialFrame.L_CH9_L[2] = static_cast<char>(QColor(theFrame.LedColors.at(0)).blue());
    serialFrame.L_CH9_H[0] = static_cast<char>(QColor(theFrame.LedColors.at(1)).red());
    serialFrame.L_CH9_H[1] = static_cast<char>(QColor(theFrame.LedColors.at(1)).green());
    serialFrame.L_CH9_H[2] = static_cast<char>(QColor(theFrame.LedColors.at(1)).blue());


    if(theFrame.ValveOnOff.at(0))
    {
        serialFrame.V_CH5_CH7_CH9_T |= 1 << 3;


    }
    else
    {
        serialFrame.V_CH5_CH7_CH9_T &=~(1 << 3);
        if(theFrame.LedSync && !theFrame.LedSyncDelay[0])
        {
            serialFrame.L_CH9_L[0] = 0x00;
            serialFrame.L_CH9_L[1] = 0x00;
            serialFrame.L_CH9_L[2] = 0x00;
        }
    }
    if(theFrame.ValveOnOff.at(1))
    {
        serialFrame.V_CH5_CH7_CH9_T |= 1 << 4;
    }
    else
    {
        serialFrame.V_CH5_CH7_CH9_T &=~(1 << 4);
        if(theFrame.LedSync && !theFrame.LedSyncDelay[1])
        {
            serialFrame.L_CH9_H[0] = 0x00;
            serialFrame.L_CH9_H[1] = 0x00;
            serialFrame.L_CH9_H[2] = 0x00;
        }
    }

    mData[frameNo] = serialFrame;
}



void SerialFrameBuffer::regenerateFrameList(const int &numberOfFrame)
{
    mData.clear();

    for (int i = 0; i < numberOfFrame; i++)
    {
        mData.append(SingleSerialFrame());
    }

    // qDebug() << "SerialFrameBuffer::regenerateFrameList completed";
}

void SerialFrameBuffer::playSerialFrame(const int &index)
{

    QByteArray theFrame = frameCombiner(mData.at(index));
//       // qDebug() << theFrame.toHex(':');

    if(mSerialOutputEnable)
    {
        emit SIG_sendFrameToSerialPort(theFrame);
    }
}

void SerialFrameBuffer::setSerialEnableOutput(const bool &enable)
{
    mSerialOutputEnable = enable;
}

QByteArray SerialFrameBuffer::frameCombiner(const SingleSerialFrame &serialFrame)  const
{

    QByteArray data;

    data += serialFrame.V_CH1_I;
    data += serialFrame.V_CH2_T;
    data += serialFrame.V_CH3_T_L;
    data += serialFrame.V_CH3_T_H;
    data += serialFrame.V_CH4_I;
    data += serialFrame.V_CH5_CH7_CH9_T;
    data += serialFrame.V_CH6_I_0;
    data += serialFrame.V_CH6_I_1;
    data += serialFrame.V_CH8_T;

    data += serialFrame.V_extraByte;

    data += serialFrame.L_CH1[0];
    data += serialFrame.L_CH1[1];
    data += serialFrame.L_CH1[2];

    data += serialFrame.L_CH2[0];
    data += serialFrame.L_CH2[1];
    data += serialFrame.L_CH2[2];

    data += serialFrame.L_CH3[0];
    data += serialFrame.L_CH3[1];
    data += serialFrame.L_CH3[2];

    data += serialFrame.L_CH4[0];
    data += serialFrame.L_CH4[1];
    data += serialFrame.L_CH4[2];

    data += serialFrame.L_CH5[0];
    data += serialFrame.L_CH5[1];
    data += serialFrame.L_CH5[2];

    data += serialFrame.L_CH6_L[0];
    data += serialFrame.L_CH6_L[1];
    data += serialFrame.L_CH6_L[2];
    data += serialFrame.L_CH6_H[0];
    data += serialFrame.L_CH6_H[1];
    data += serialFrame.L_CH6_H[2];

    data += serialFrame.L_CH7_L[0];
    data += serialFrame.L_CH7_L[1];
    data += serialFrame.L_CH7_L[2];
    data += serialFrame.L_CH7_H[0];
    data += serialFrame.L_CH7_H[1];
    data += serialFrame.L_CH7_H[2];

    data +=serialFrame.L_CH8_0[0];
    data +=serialFrame.L_CH8_0[1];
    data +=serialFrame.L_CH8_0[2];

    data +=serialFrame.L_CH8_1[0];
    data +=serialFrame.L_CH8_1[1];
    data +=serialFrame.L_CH8_1[2];

    data +=serialFrame.L_CH8_2[0];
    data +=serialFrame.L_CH8_2[1];
    data +=serialFrame.L_CH8_2[2];

    data +=serialFrame.L_CH8_3[0];
    data +=serialFrame.L_CH8_3[1];
    data +=serialFrame.L_CH8_3[2];

    data +=serialFrame.L_CH8_4[0];
    data +=serialFrame.L_CH8_4[1];
    data +=serialFrame.L_CH8_4[2];


    data +=serialFrame.L_CH8_5[0];
    data +=serialFrame.L_CH8_5[1];
    data +=serialFrame.L_CH8_5[2];

    data +=serialFrame.L_CH8_6[0];
    data +=serialFrame.L_CH8_6[1];
    data +=serialFrame.L_CH8_6[2];

    data +=serialFrame.L_CH8_7[0];
    data +=serialFrame.L_CH8_7[1];
    data +=serialFrame.L_CH8_7[2];

    data += serialFrame.L_CH9_L[0];
    data += serialFrame.L_CH9_L[1];
    data += serialFrame.L_CH9_L[2];

    data += serialFrame.L_CH9_H[0];
    data += serialFrame.L_CH9_H[1];
    data += serialFrame.L_CH9_H[2];

    data +=serialFrame.L_extraByte[0];
    data +=serialFrame.L_extraByte[1];
    data +=serialFrame.L_extraByte[2];

    //    serialFrame.Length_Low =

    quint16 checksum = 0;

    for(int i = 0; i < data.size() ;i++)
    {
        checksum += static_cast<quint16>(data.at(i));
    }

    char CheckSum_High = static_cast<char>(checksum >> 8);
    char CheckSum_Low = static_cast<char>(checksum&0xff);


    QByteArray package;

    package+= serialFrame.start;
    package+= serialFrame.opcode;
    package+= serialFrame.length;
    package+= data;
    package+= CheckSum_High;
    package+= CheckSum_Low;
    package+= serialFrame.stop;

    //    // qDebug() << "data size: " + QString::number(data.size());
    //    // qDebug() << "package size: " + QString::number(package.size());

    return package;
}


void SerialFrameBuffer::sendEmptyFrame()
{
    QByteArray theFrame = frameCombiner(SingleSerialFrame());
//       // qDebug() << theFrame.toHex(':');

    qDebug() << "empty Frame: " + theFrame;
    if(mSerialOutputEnable)
    {
        emit SIG_sendFrameToSerialPort(theFrame);
    }
}
