#ifndef PRESENTERFRAMELIST_H
#define PRESENTERFRAMELIST_H

#include <QObject>
#include <QVector>
#include "timeslotlist.h"

#include "valveeffect_kieu1.h"
#include "valveeffect_kieu2.h"
#include "valveeffect_kieu3.h"
#include "valveeffect_kieu4.h"
#include "valveeffect_kieu5.h"


#include "led_fadeinfadeout.h"
#include "led_fadeinfadeout2colors.h"
#include "led_solid.h"
#include "led_blink.h"
#include "led_bineffects.h"

//#include "anlogger.h"
#include <QMap>


struct PresenterFrame{
    int frameNo;
    bool Inverter;
    QList<QString> LedColors;
    QList<bool> ValveOnOff;
    QList<bool> LedOnOff;
    quint8 InverterLevel;
    quint8 InverterLevel1;
    quint8 LedChannels;
    quint8 ValveChannels;
    bool LedSync;

};

struct PreviousFrame{
    int id;
    int FromFrame;
    int ToFrame;
};

class PresenterFrameList : public QObject
{
    Q_OBJECT

    int mDuration;
    int mFrameDuration;
    int mFrameNo;

    ValveEffect_Kieu1 mValveEffect_1;
    ValveEffect_Kieu2 mValveEffect_2;
    ValveEffect_Kieu3 mValveEffect_3;
    ValveEffect_Kieu4 mValveEffect_4;
    ValveEffect_Kieu5 mValveEffect_5;

    LED_FadeInFadeOut mLED_FadeInFadeOut;
    LED_FadeInFadeOut2Colors mLed_ColorTransition;
    LED_Solid mLED_Solid;
    LED_Blink mLED_Blink;
    LED_BinEffects mLED_BinEffects;


    QVector<PresenterFrame> frameList;
    QVector<PreviousFrame> timeSlotShortVerList;

    PresenterFrame setFramePerGroup(const int &index, const timeSlotItem &timeSlot,  PresenterFrame aFrame);
    PresenterFrame createEmptyFramePerGroup(const int &group) const;
    void emptyFrameCleanUp();

    int timeSlotExistInList(const int &id);
    QString returnLedValue(const int &index, const QString &ledList);
public:

    int mGroup;
    explicit PresenterFrameList(QObject *parent = nullptr);

    void clearList();

    int getFrameDuration() const;
    int getDuration() const;
    int getFrameNo() const;
    PresenterFrame getFrame(const int &frameNo);
    int findFrameFromMs(const int &timePoint);



signals:
    void notifyFrameChanged(const PresenterFrame &frame);

    void SIG_SerialFrameBuffer_regenerateFrameList(const int &totalFrame);
    void SIG_SerialFrameBuffer_notifyFrameChanged(const int &group,const int &frameNo,const PresenterFrame &theFrame);

    void SIG_frameListReconstructed();


public slots:
    void timeSlotChanged(const timeSlotItem &timeSlot);
    void timeSlotRemoved(const timeSlotItem &timeSlot);
    void playFrame(const int &frameNo);
    void regenerateFrameList(const int &Duration, const int &FrameDuration);



};

#endif // PRESENTERFRAMELIST_H
