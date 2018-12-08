#include "valveeffect_kieu1.h"
#include <QDebug>
ValveEffect_Kieu1::ValveEffect_Kieu1(): mEffectValid(false), mSpeed(0), mForceRepeat(false),mForceRepeatJustChanged(false),  mNewPathJustChanged(false),mRepeatTime(0),mFrameNo(0)
{


}

bool ValveEffect_Kieu1::setNewPath(QString filePath)
{
    if(mFilePath != filePath)
    {
        mFilePath = filePath;
        mNewPathJustChanged = true;
        QFile file(mFilePath);
        if(file.open(QIODevice::ReadOnly ))
        {
            mEffectValid = true;

            mEffectBytes = file.readAll();


            setSpeed(50);

            return true;
        }
        else
        {
            mEffectValid = false;
        }
    }
    return false;
}

bool ValveEffect_Kieu1::isEffectValid()
{
    return mEffectValid;
}

bool ValveEffect_Kieu1::setForceRepeat(const bool &forcedRepeat, const int &repeatTime)
{



    if(mForceRepeat != forcedRepeat || repeatTime != mRepeatTime || mNewPathJustChanged)
    {

        mRepeatTime = repeatTime;
        mForceRepeat = forcedRepeat;
        mNewPathJustChanged = false;

        if(mForceRepeat)
        {
                    mEffectBytesForceRepeat.clear();

                    for(int i =0; i < repeatTime;i++)
                    {
                        mEffectBytesForceRepeat.append(mEffectBytes);
                    }
        }

        mForceRepeatJustChanged = true;


//        qDebug() << "effectByte with speed size: " + QString::number(mEffectBytesWithSpeed.size());
     return true;

    }


    return false;
}



bool ValveEffect_Kieu1::setSpeed( const int &theSpeed)
{

    if(mSpeed != theSpeed || mForceRepeatJustChanged)
    {
        mSpeed = theSpeed;
        mForceRepeatJustChanged = false;


        mEffectBytesWithSpeed.clear();
         qDebug() << "chan vl vay";
        if(mForceRepeat)
        {
            qDebug() << "mForceRepeatSet";
            for(int i = 0; i < mEffectBytesForceRepeat.count();i++)
            {
                if(mSpeed >= 0)
                {
                    for( int ii = 50; ii >= mSpeed; ii--)
                    {
                        mEffectBytesWithSpeed.append(mEffectBytesForceRepeat[i]);
                    }
                }
                else
                {

                    for(int ii = 0; ii < 50 - mSpeed; ii++)
                    {
                        mEffectBytesWithSpeed.append(mEffectBytesForceRepeat[i]);
                    }
                }
            }
        }
        else
        {
            for(int i = 0; i < mEffectBytes.count();i++)
            {
                if(mSpeed >= 0)
                {
                    for( int ii = 50; ii >= mSpeed; ii--)
                    {
                        mEffectBytesWithSpeed.append(mEffectBytes[i]);
                    }
                }
                else
                {
                    for(int ii = 0; ii < 50 - mSpeed; ii++)
                    {
                        mEffectBytesWithSpeed.append(mEffectBytes[i]);
                    }
                }
            }
        }

        return true;

    }

    return false;
}
quint8 ValveEffect_Kieu1::getData(const int &index)
{

    return static_cast<quint8>( mEffectBytesWithSpeed.at(index %(mEffectBytesWithSpeed.count())));
}
