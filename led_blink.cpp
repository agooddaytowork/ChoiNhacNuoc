#include "led_blink.h"

LED_Blink::LED_Blink(): mSpeed(-1)
{

}
bool LED_Blink::setSpeed(const int &speed)
{
    if(mSpeed != speed)
    {
        mSpeed = speed;


        dataWithSpeed.clear();
        for(int i = 0; i < data.count();i++)
        {
            if(mSpeed >= 0)
            {
                for( int ii = 50; ii >= mSpeed; ii--)
                {
                    dataWithSpeed.append(data.at(i));
                }
            }
            else
            {
                for(int ii = 0; ii < 50 - mSpeed; ii++)
                {
                    dataWithSpeed.append(data.at(i));
                }
            }
        }


        return true;
    }

    return false;
}

bool LED_Blink::setEffects(const QColor &color)
{


//    theColor.toHsl();




    if(color != mColor )
    {
        mColor = color;

        data.clear();


        QColor dmColor(0,0,0);

        data.append(color);
        data.append(dmColor);


         setSpeed(5);
        return true;
    }


    return false;
}


QColor LED_Blink::getData(const int &index)
{

//     mEffectBytesWithSpeed.at(index %(mEffectBytesWithSpeed.count() -1))

    return  dataWithSpeed[index %(dataWithSpeed.count() -1)];
}
