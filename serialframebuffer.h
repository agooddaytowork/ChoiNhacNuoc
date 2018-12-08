#ifndef SERIALFRAMEBUFFER_H
#define SERIALFRAMEBUFFER_H

#include <QByteArray>
#include <QObject>
#include <QVector>
#include "presenterframelist.h"



struct SingleSerialFrame{
    char start = 0x02;
    char opcode = 0x01;
    char length = 70;

    //10 byte cho Valve
    //-----------------------------//
    char V_CH1_I = 0x00;
    char V_CH2_T = 0x00;
    char V_CH3_T_L = 0x00;
    char V_CH3_T_H = 0x00;
    char V_CH4_I = 0x00;
    char V_CH5_CH7_CH9_T = 0x00; // CH5 bit 0; CH7 bit 1&2; CH9 bit 3&4
    char V_CH6_I_0 = 0x00;
    char V_CH6_I_1 = 0x00;
    char V_CH8_T = 0x00;
    char V_extraByte = 0x00;


    // 60 byte cho LED RGB
    //----------------------------//

    char L_CH1[3] ={0x00,  0x00,  0x00};
    char L_CH2[3] ={0x00,  0x00,  0x00};
    char L_CH3[3] ={0x00,  0x00,  0x00};
    char L_CH4[3] ={0x00,  0x00,  0x00};
    char L_CH5[3] ={0x00,  0x00,  0x00};
    char L_CH6_L[3] ={0x00,  0x00,  0x00};
    char L_CH6_H[3] ={0x00,  0x00,  0x00};
    char L_CH7_L[3] ={0x00,  0x00,  0x00};
    char L_CH7_H[3] ={0x00,  0x00,  0x00};
    char L_CH8_0[3] ={0x00,  0x00,  0x00};
    char L_CH8_1[3] ={0x00,  0x00,  0x00};
    char L_CH8_2[3] ={0x00,  0x00,  0x00};
    char L_CH8_3[3] ={0x00,  0x00,  0x00};
    char L_CH8_4[3] ={0x00,  0x00,  0x00};
    char L_CH8_5[3] ={0x00,  0x00,  0x00};
    char L_CH8_6[3] ={0x00,  0x00,  0x00};
    char L_CH8_7[3] ={0x00,  0x00,  0x00};
    char L_CH9_L[3] ={0x00,  0x00,  0x00};
    char L_CH9_H[3] ={0x00,  0x00,  0x00};
    char L_extraByte[3] ={0x00,  0x00,  0x00};

    //---------------------------//
    char checkSumHighByte = 0x00; // check sum will be calculated at FrameCombiner function
    char checkSumLowByte = 0x00;
    char stop = 0x03;
};

class SerialFrameBuffer: public QObject
{

    Q_OBJECT

    QVector<SingleSerialFrame> mData;
    bool mSerialOutputEnable;

    void group1Handler(const int &frameNo, const PresenterFrame &theFrame);
    void group2Handler(const int &frameNo,const PresenterFrame &theFrame);
    void group3Handler(const int &frameNo,const PresenterFrame &theFrame);
    void group4Handler(const int &frameNo,const PresenterFrame &theFrame);
    void group5Handler(const int &frameNo,const PresenterFrame &theFrame);
    void group6Handler(const int &frameNo,const PresenterFrame &theFrame);
    void group7Handler(const int &frameNo,const PresenterFrame &theFrame);
    void group8Handler(const int &frameNo,const PresenterFrame &theFrame);
    void group9Handler(const int &frameNo,const PresenterFrame &theFrame);


public:

    SerialFrameBuffer(QObject * parent = nullptr);
    QByteArray frameCombiner( const SingleSerialFrame &serialFrame) const;

    //public slots:
    void SerialFrameChangedHandler(const int &group, const int &frameNo, const PresenterFrame &theFrame);
    void regenerateFrameList(const int &numberOfFrame);
    void playSerialFrame (const int &index);
    void setSerialEnableOutput(const bool &enable);

signals:
    void SIG_sendFrameToSerialPort(const QByteArray &frame);

};

#endif // SERIALFRAMEBUFFER_H
