#include "led_bineffects.h"
#include <QDebug>
LED_BinEffects::LED_BinEffects():mEffectValid(false), mSpeed(0), mForceRepeat(false), mForceRepeatJustChanged(false),mRepeatTime(0),mFrameNo(0),mLedNo(0), mFilePathJustChanged(false)
{

}

bool LED_BinEffects::setNewPath(QString filePath, const int &ledNo)
{
    if(mFilePath != filePath || mLedNo != ledNo)
    {
        qDebug() << "filePath changed";
        mFilePath = filePath;
        mLedNo = ledNo;
        mFilePathJustChanged = true;
        QFile file(mFilePath);

        rawColorMatrix.clear();
        if(file.open(QIODevice::ReadOnly ))
        {
            mEffectValid = true;

            mEffectBytes = file.readAll();

            if(mEffectBytes.size() %3 != 0 || (mEffectBytes.size()/3) < (mLedNo*3))
            {
                //emit error

                qDebug() << "LED BIN EFFECT SIZE cannot % 3 || EFFECT size is not correct to LED Size";
                return false;
            }

            int ledNo = 0;
            QList<QColor> memberList;
            for(int i = 0; i < mEffectBytes.size() / 3; i++)
            {


                if(ledNo < mLedNo)
                {
                    QColor theColor;
                    theColor.setRgb(static_cast<quint8>(mEffectBytes.at(i*3))
                                    ,static_cast<quint8>(mEffectBytes.at((i*3)+1))
                                    ,static_cast<quint8>(mEffectBytes.at((i*3)+2)));
                    memberList.append(theColor);
                    ledNo++;
                }
                if(ledNo == mLedNo)
                {
                    rawColorMatrix.append(memberList);
                    memberList.clear();
                    ledNo = 0;
                }
            }

            setSpeed(50);

            return true;
        }
        else
        {
            qDebug() << "Khong mo dc file bin";
            mEffectValid = false;
        }
    }
    return true;
}

bool LED_BinEffects::isEffectValid()
{
    return mEffectValid;
}

bool LED_BinEffects::setForceRepeat(const bool &forcedRepeat, const int &repeatTime)
{

//    qDebug() <<"force request: " + QString::number(forcedRepeat) + " repeat time: " + QString::number(repeatTime);
    if(mForceRepeat != forcedRepeat || repeatTime != mRepeatTime || mFilePathJustChanged)
    {

        mRepeatTime = repeatTime;
        mForceRepeat = forcedRepeat;
        mFilePathJustChanged = false;

        if(mForceRepeat)
        {
            forcedColorMatrix.clear();

            for(int i =0; i < repeatTime;i++)
            {
                forcedColorMatrix.append(rawColorMatrix);
            }
        }

        mForceRepeatJustChanged = true;


//               qDebug() << "forcedColorMatrix size: " + QString::number(forcedColorMatrix.size());
        return true;

    }


    return false;
}



bool LED_BinEffects::setSpeed( const int &theSpeed)
{

    if(mSpeed != theSpeed || mForceRepeatJustChanged)
    {
        mSpeed = theSpeed;
        mForceRepeatJustChanged = false;


        speedColorMatrix.clear();

        if(mForceRepeat)
        {
            for(int i = 0; i < forcedColorMatrix.count();i++)
            {
                if(mSpeed >= 0)
                {
                    for( int ii = 50; ii >= mSpeed; ii--)
                    {
                        speedColorMatrix.append(forcedColorMatrix[i]);
                    }
                }
                else
                {

                    for(int ii = 0; ii < 50 - mSpeed; ii++)
                    {
                        speedColorMatrix.append(forcedColorMatrix[i]);
                    }
                }
            }
        }
        else
        {
            for(int i = 0; i < rawColorMatrix.count();i++)
            {
                if(mSpeed >= 0)
                {
                    for( int ii = 50; ii >= mSpeed; ii--)
                    {
                        speedColorMatrix.append(rawColorMatrix[i]);
                    }
                }
                else
                {
                    for(int ii = 0; ii < 50 - mSpeed; ii++)
                    {
                        speedColorMatrix.append(rawColorMatrix[i]);
                    }
                }
            }
        }
        return true;
    }

    return false;
}
QColor LED_BinEffects::getData(const int &index, const int &ledOrder)
{

    return  speedColorMatrix.at(index %(speedColorMatrix.count())).at(ledOrder);
}
