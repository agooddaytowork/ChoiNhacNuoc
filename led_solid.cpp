#include "led_solid.h"

LED_Solid::LED_Solid()
{

}


bool LED_Solid::setEffects(const QColor &color)
{
    if(mColor != color)
    {
        mColor = color;
        return true;
    }

    return false;
}


QColor LED_Solid::getData()
{
    return mColor;
}
