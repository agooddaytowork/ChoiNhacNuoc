#include "valveeffect_kieu4.h"


ValveEffect_Kieu4::ValveEffect_Kieu4(): mEffectValid(false), mSpeed(0), mForceRepeat(false), mForceRepeatJustChanged(false),mRepeatTime(0),mFrameNo(0), mNewPathJustChanged(false)
{

}


bool ValveEffect_Kieu4::setNewPath(QString filePath)
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

bool ValveEffect_Kieu4::setForceRepeat(const bool &forcedRepeat, const int &repeatTime)
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


        //        // qDebug() << "effectByte with speed size: " + QString::number(mEffectBytesWithSpeed.size());
        return true;

    }


    return false;
}

bool ValveEffect_Kieu4::setSpeed( const int &theSpeed)
{
    //    if(mSpeed != theSpeed)
    //    {
    //        mSpeed = theSpeed;

    //        mEffectBytesWithSpeed.clear();

    //        for(int i = 0; i < mEffectBytes.count();i++)
    //        {
    //            if(mSpeed >= 0)
    //            {
    //                for( int ii = 50; ii >= mSpeed; ii--)
    //                {
    //                    mEffectBytesWithSpeed.append(mEffectBytes[i]);
    //                }
    //            }
    //            else
    //            {

    //                for(int ii = 0; ii < 50 - mSpeed; ii++)
    //                {
    //                    mEffectBytesWithSpeed.append(mEffectBytes[i]);
    //                }
    //            }
    //        }

    //        return true;

    //    }

    //    return false;

    if(mSpeed != theSpeed || mForceRepeatJustChanged)
    {
        mSpeed = theSpeed;
        mForceRepeatJustChanged = false;


        mEffectBytesWithSpeed.clear();
        if(mForceRepeat)
        {
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

bool ValveEffect_Kieu4::getData(const int &index, const bool &odd)
{

    quint8 theValue = static_cast<quint8>( mEffectBytesWithSpeed.at(index %(mEffectBytesWithSpeed.count())));


    if(odd)
    {
        if(theValue & (1 << 0))
        {
            return true;
        }

    }
    else
    {
        if(theValue & (1 << 1))
        {
            return true;
        }

    }
    return false;

}

bool ValveEffect_Kieu4::isEffectValid()
{
    return mEffectValid;
}

