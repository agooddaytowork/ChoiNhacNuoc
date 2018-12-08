#include "presenterframelist.h"
#include <QDebug>
#include <QString>

PresenterFrameList::PresenterFrameList(QObject *parent) : QObject(parent),  mDuration(0), mFrameDuration(0),mFrameNo(0),mGroup(0)
{

}


void PresenterFrameList::clearList()
{
    frameList.clear();

    for(int i = 0; i < mFrameNo; i++)
    {
        frameList.append(createEmptyFramePerGroup(mGroup));
    }

    emit SIG_frameListReconstructed();
}

void PresenterFrameList::regenerateFrameList(const int &Duration, const int &FrameDuration)
{

    bool isAnyThingChanged = false;

    if(mFrameDuration != FrameDuration)
    {
        mFrameDuration = FrameDuration;
        isAnyThingChanged = true;
    }
    if(mDuration != Duration)
    {
        mDuration = Duration;
        isAnyThingChanged = true;
    }

    if(isAnyThingChanged)
    {
        mFrameNo = static_cast<int>(Duration/FrameDuration);

        if(Duration%FrameDuration != 0)
        {
            mFrameNo ++;
        }

        emit SIG_SerialFrameBuffer_regenerateFrameList(mFrameNo);
    }
    clearList();

    //    qDebug() << "Frame List ---------";
    //    qDebug() << "total Frame: " + QString::number(mFrameNo);
    //    qDebug() << "frame list count: " + QString::number(frameList.count());


}

int  PresenterFrameList::getFrameDuration() const
{
    return mFrameDuration;
}

int PresenterFrameList::getDuration() const
{

    return mDuration;
}

int PresenterFrameList::getFrameNo() const
{
    return mFrameNo;
}


void PresenterFrameList::playFrame(const int &frameNo)
{
    if(frameNo <= this->mFrameNo)
    {
        emit notifyFrameChanged(getFrame(frameNo));
    }

}


PresenterFrame PresenterFrameList::getFrame(const int &frameNo)
{
    return frameList.at(frameNo);
}

void PresenterFrameList::timeSlotChanged(const timeSlotItem &timeSlot)
{


//        qDebug() << "Time SLot Changed";
    int fromFrame = findFrameFromMs(timeSlot.fromMs);
    int toFrame = findFrameFromMs(timeSlot.toMs);

    int previousFrameIndex = timeSlotExistInList(timeSlot.id);
    if(previousFrameIndex >= 0)
    {
//                 qDebug() << "previous Frame Found";
        PreviousFrame thePreviousFrame = timeSlotShortVerList[previousFrameIndex];


        thePreviousFrame.FromFrame = fromFrame;
        thePreviousFrame.ToFrame = toFrame;
        timeSlotShortVerList[previousFrameIndex] = thePreviousFrame;

    }
    else
    {
        PreviousFrame aTimeSlotShort;

        aTimeSlotShort.FromFrame = fromFrame;
        aTimeSlotShort.ToFrame = toFrame;
        aTimeSlotShort.id = timeSlot.id;

        timeSlotShortVerList.append(aTimeSlotShort);
    }

    int i = 0;
    while(fromFrame <= toFrame)
    {

        frameList[fromFrame] = setFramePerGroup(i,timeSlot, frameList.at(fromFrame));

        emit SIG_SerialFrameBuffer_notifyFrameChanged(mGroup,fromFrame,frameList[fromFrame]);
        fromFrame++;
        i++;
    }

    emptyFrameCleanUp();



}

int PresenterFrameList::findFrameFromMs(const int &timePoint)
{
    //    qDebug() << "timePoint: " + QString::number(timePoint);
    if(timePoint<0)
    {
        return  0;
    }
    else if(timePoint > mDuration)
    {
        return mDuration /mFrameDuration ;
    }
    return static_cast<int>(timePoint/mFrameDuration );
}

PresenterFrame PresenterFrameList::setFramePerGroup(const int &index, const timeSlotItem &timeSlot, PresenterFrame aFrame)
{

    aFrame.LedOnOff.clear();
    aFrame.ValveOnOff.clear();


    if(mGroup ==0 || mGroup == 3)
    {
        mValveEffect_1.setNewPath(timeSlot.fileBinPath);

        if(mValveEffect_1.isEffectValid())
        {

            if(timeSlot.ValveForceRepeat)
            {
                mValveEffect_1.setForceRepeat(true,timeSlot.ValveForceRepeatTimes);
            }
            else
            {
                mValveEffect_1.setForceRepeat(false,timeSlot.ValveForceRepeatTimes);

            }
            mValveEffect_1.setSpeed(timeSlot.ValveSpeed);
            aFrame.InverterLevel = mValveEffect_1.getData(index);
        }

    }
    else if(mGroup == 1 || mGroup == 7)
    {
        mValveEffect_2.setNewPath(timeSlot.fileBinPath);

        if(mValveEffect_2.isEffectValid())
        {
            if(timeSlot.ValveForceRepeat)
            {
                mValveEffect_2.setForceRepeat(true,timeSlot.ValveForceRepeatTimes);
            }
            else
            {
                mValveEffect_2.setForceRepeat(false,timeSlot.ValveForceRepeatTimes);
            }
            mValveEffect_2.setSpeed(timeSlot.ValveSpeed);

            for(int i = 0; i < timeSlot.ValveChannels; i++)
            {
                aFrame.ValveOnOff.append(mValveEffect_2.getData(index, i));
            }
        }

    }
    else if(mGroup == 2)
    {
        mValveEffect_3.setNewPath(timeSlot.fileBinPath);

        if(mValveEffect_3.isEffectValid())
        {
            if(timeSlot.ValveForceRepeat)
            {
                mValveEffect_3.setForceRepeat(true,timeSlot.ValveForceRepeatTimes);
            }
            else
            {
                mValveEffect_3.setForceRepeat(false,timeSlot.ValveForceRepeatTimes);
            }

            mValveEffect_3.setSpeed(timeSlot.ValveSpeed);
            for(int i = 0; i < timeSlot.ValveChannels; i++)
            {
                aFrame.ValveOnOff.append(mValveEffect_3.getData(index, i));


            }
        }
    }
    else if(mGroup == 6 || mGroup == 8)
    {
        mValveEffect_4.setNewPath(timeSlot.fileBinPath);




        if(mValveEffect_4.isEffectValid())
        {
            if(timeSlot.ValveForceRepeat)
            {
                mValveEffect_4.setForceRepeat(true,timeSlot.ValveForceRepeatTimes);
            }
            else
            {
                mValveEffect_4.setForceRepeat(false,timeSlot.ValveForceRepeatTimes);
            }
            mValveEffect_4.setSpeed(timeSlot.ValveSpeed);
            aFrame.ValveOnOff.append(mValveEffect_4.getData(index,false));
            aFrame.ValveOnOff.append(mValveEffect_4.getData(index,true));
        }
    }
    else if(mGroup == 4)
    {
        mValveEffect_4.setNewPath(timeSlot.fileBinPath);
        if(mValveEffect_4.isEffectValid())
        {
            if(timeSlot.ValveForceRepeat)
            {
                mValveEffect_4.setForceRepeat(true,timeSlot.ValveForceRepeatTimes);
            }
            else
            {
                mValveEffect_4.setForceRepeat(false,timeSlot.ValveForceRepeatTimes);
            }
            mValveEffect_4.setSpeed(timeSlot.ValveSpeed);
            aFrame.ValveOnOff.append(mValveEffect_4.getData(index,true));
        }
    }
    else if(mGroup == 5)
    {
        mValveEffect_5.setNewPath(timeSlot.fileBinPath);
        if(mValveEffect_5.isEffectValid())
        {
            if(timeSlot.ValveForceRepeat)
            {
                mValveEffect_5.setForceRepeat(true,timeSlot.ValveForceRepeatTimes);
            }
            else
            {
                mValveEffect_5.setForceRepeat(false,timeSlot.ValveForceRepeatTimes);
            }

            mValveEffect_5.setSpeed(timeSlot.ValveSpeed);


            aFrame.InverterLevel = mValveEffect_5.getData(index,true);
            aFrame.InverterLevel1= mValveEffect_5.getData(index,false);

        }
    }

    if(aFrame.ValveOnOff.count() == 0)
    {
        for(int i = 0; i < timeSlot.ValveChannels; i++)
        {
            aFrame.ValveOnOff.append(timeSlot.ValveOnOff);

        }
    }

    if(timeSlot.UseLedBuiltInEffects)
    {
        if(timeSlot.LedModeName == "Fade In/Out")
        {
            QColor theColor;


            theColor.setNamedColor(returnLedValue(0,timeSlot.LedValuesList));


            mLED_FadeInFadeOut.setEffects(theColor);
            mLED_FadeInFadeOut.setSpeed(timeSlot.LedSpeed);
            for(int i = 0; i < timeSlot.LedChannels; i++)
            {
                aFrame.LedColors[i]= mLED_FadeInFadeOut.getData(index).name();
            }
        }
        else if(timeSlot.LedModeName == "Color Transition")
        {
            QColor headColor;
            QColor tailColor;

            headColor.setNamedColor(returnLedValue(0,timeSlot.LedValuesList));
            tailColor.setNamedColor(returnLedValue(1,timeSlot.LedValuesList));


            mLed_ColorTransition.setEffects(headColor
                                            ,tailColor
                                            ,(timeSlot.toMs - timeSlot.fromMs)/50);

            for(int i = 0; i < timeSlot.LedChannels; i++)
            {
                aFrame.LedColors[i]= mLed_ColorTransition.getData(index).name();
            }
        }
        else if(timeSlot.LedModeName == "Solid")
        {
            QColor theColor;

            theColor.setNamedColor(returnLedValue(0,timeSlot.LedValuesList));
            mLED_Solid.setEffects(theColor);

            for(int i = 0; i < timeSlot.LedChannels; i++)
            {
                aFrame.LedColors[i]= mLED_Solid.getData().name();
            }

        }
        else if(timeSlot.LedModeName == "Blink")
        {

            QColor theColor;


            theColor.setNamedColor(returnLedValue(0,timeSlot.LedValuesList));


            mLED_Blink.setEffects(theColor);
            mLED_Blink.setSpeed(timeSlot.LedSpeed);
            for(int i = 0; i < timeSlot.LedChannels; i++)
            {
                aFrame.LedColors[i]= mLED_Blink.getData(index).name();
            }

        }
    }
    else
    {
        // use external LED effects

        mLED_BinEffects.setNewPath(timeSlot.LedBinPath, timeSlot.LedChannels);

        if(mLED_BinEffects.isEffectValid())
        {
            if(timeSlot.LedForceRepeat)
            {
                mLED_BinEffects.setForceRepeat(true, timeSlot.LedForceRepeatTimes);
            }
            else
            {
                mLED_BinEffects.setForceRepeat(false, timeSlot.LedForceRepeatTimes);
            }

            mLED_BinEffects.setSpeed(timeSlot.LedSpeed);

            for(int i = 0; i < timeSlot.LedChannels; i++)
            {
                aFrame.LedColors[i]= mLED_BinEffects.getData(index,i).name();
            }
        }

    }



    aFrame.LedSync = timeSlot.LedSync;
    for(int i = 0; i < timeSlot.LedChannels; i++)
    {
        aFrame.LedOnOff.append(timeSlot.LedOnOff);
    }





    return aFrame;
}

PresenterFrame PresenterFrameList::createEmptyFramePerGroup(const int &group) const
{
    PresenterFrame item;

    item.InverterLevel = 0;
    item.Inverter = false;


    switch(group)
    {
    case 0:
        item.Inverter = true;
        item.LedChannels = 1;
        item.ValveChannels = 1;
        item.ValveOnOff.append(false); // 1
        item.LedOnOff.append(false);

        break;
    case 1:
        item.LedChannels = 1;
        item.ValveChannels = 8;


        for(int i = 0; i < 8; i++)
        {
            item.ValveOnOff.append(false);
        }
        item.LedOnOff.append(false);
        break;
    case 2:
        item.LedChannels = 1;
        item.ValveChannels = 16;
        for(int i = 0; i < 16; i++)
        {
            item.ValveOnOff.append(false);
        }
        item.LedOnOff.append(false);
        break;
    case 3:
        item.LedChannels = 2;
        item.Inverter = true;
        item.ValveChannels = 1;
        item.ValveOnOff.append(false);
        for(int i = 0; i < 2; i++)
        {
            item.LedOnOff.append(false);
        }
        break;
    case 4:
        item.LedChannels = 3;
        item.ValveChannels = 1;
        item.ValveOnOff.append(false);
        for(int i = 0; i < 3; i++)
        {

            item.LedOnOff.append(false);
        }
        break;
    case 5:
        item.LedChannels = 12;
        item.Inverter = true;
        item.InverterLevel = 0;
        item.InverterLevel1 = 0;
        item.ValveChannels = 2;
        item.ValveOnOff.append(false);
        item.ValveOnOff.append(false);
        for(int i = 0; i < 12; i++)
        {

            item.LedOnOff.append(false);
        }
        break;
    case 6:
        item.LedChannels = 6;
        item.ValveChannels = 2;
        item.ValveOnOff.append(false);
        item.ValveOnOff.append(false);

        for(int i = 0; i < 6; i++)
        {

            item.LedOnOff.append(false);
        }

        break;
    case 7:
        item.LedChannels = 8;
        item.ValveChannels = 8;
        for(int i = 0; i < 8; i++)
        {
            item.ValveOnOff.append(false);
            item.LedOnOff.append(false);
        }

        break;
    case 8:
        item.LedChannels = 2;
        item.ValveChannels = 2;
        for(int i = 0; i < 2; i++)
        {
            item.ValveOnOff.append(false);
            item.LedOnOff.append(false);
        }
        break;

    }

    for(int i = 0; i < item.LedChannels; i++)
    {
        item.LedColors.append("#000000");
    }

    return item;

}



bool operator<(const PreviousFrame& a, const PreviousFrame& b) { return a.FromFrame < b.FromFrame; }

void PresenterFrameList::emptyFrameCleanUp()
{
    int frameCnt = 0;


    std::sort(timeSlotShortVerList.begin(),timeSlotShortVerList.end());

    for(int i =0; i < timeSlotShortVerList.count(); i++)
    {
        //        qDebug() << "fromFrame: " + QString::number(timeSlotShortVerList[i].FromFrame) << "frameCnt: " + QString::number(frameCnt);
        while(frameCnt < timeSlotShortVerList[i].FromFrame)
        {
            frameList[frameCnt]= createEmptyFramePerGroup(mGroup);

            emit SIG_SerialFrameBuffer_notifyFrameChanged(mGroup,frameCnt,frameList[frameCnt]);
            frameCnt++;
        }
        frameCnt = timeSlotShortVerList[i].ToFrame + 1;
        //          qDebug() << "frameCnt after: " + QString::number(frameCnt);
    }

    while(frameCnt < mFrameNo)
    {
        frameList[frameCnt]= createEmptyFramePerGroup(mGroup);
        emit SIG_SerialFrameBuffer_notifyFrameChanged(mGroup,frameCnt,frameList[frameCnt]);
        frameCnt++;
    }


}

void PresenterFrameList::timeSlotRemoved(const timeSlotItem &timeSlot)
{



    int index = timeSlotExistInList(timeSlot.id);

    if(index >= 0)
    {
        timeSlotShortVerList.remove(index);
    }

    emptyFrameCleanUp();
    //    while(fromFrame <= toFrame)
    //    {
    //        frameList[fromFrame] = createEmptyFramePerGroup(mGroup);
    //        fromFrame++;
    //    }

    //    for(int i = 0; i < timeSlotShortVerList.count(); i++)
    //    {
    //        if(timeSlotShortVerList[i].id == timeSlot.id)
    //        {
    //            timeSlotShortVerList.remove(timeSlotShortVerList[i].FromFrame);
    //            return;
    //        }
    //    }
}


int PresenterFrameList::timeSlotExistInList(const int &id)
{
    if(timeSlotShortVerList.count() > 0)
    {
        for(int i = 0; i < timeSlotShortVerList.count(); i++)
        {
            if(timeSlotShortVerList[i].id == id)
            {
                return i;
            }
        }
    }
    return -1;
}

QString PresenterFrameList::returnLedValue(const int &index, const QString &ledList)
{

    QStringList theList = ledList.split(';');

    if(index >= theList.size())
    {
        return "#8e8e8e";
    }

    return theList.at(index);
}

