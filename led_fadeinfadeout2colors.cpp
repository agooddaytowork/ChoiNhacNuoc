#include "led_fadeinfadeout2colors.h"
#include "QDebug"

LED_FadeInFadeOut2Colors::LED_FadeInFadeOut2Colors(): mFrameNo(0)
{

}


bool LED_FadeInFadeOut2Colors::setEffects(const QColor &Headcolor, const QColor &TailColor, const int &frameNo)
{



//    theColor.toHsl();

    qreal hueHead,  saturationHead, lightnessHead;
    qreal hueTail, saturationTail, lightnessTail;


    Headcolor.getHslF(&hueHead, &saturationHead,&lightnessHead);
    TailColor.getHslF(&hueTail,&saturationTail,&lightnessTail);



    qreal hueStep = (hueTail - hueHead) / (frameNo + 2);
    qreal lightstep = (lightnessTail - lightnessHead ) /(frameNo + 2);
    qreal saturationStep = (saturationTail - saturationHead  ) /(frameNo + 2);

    if(Headcolor != mColorHead || TailColor != mColorTail  || mFrameNo != frameNo + 2 )
    {
        mColorHead = Headcolor;
        mColorTail = TailColor;
        mFrameNo = frameNo + 2;

        data.clear();

//        // qDebug() << "hue ah hihi: " + QString::number(hue);

        QColor dmColor = Headcolor;
         for(int i = 0; i < mFrameNo; i++)
         {

             dmColor.setHslF(hueHead + (hueStep * i),saturationHead +(saturationStep * i), lightnessHead + (lightstep*i));

             data.append(dmColor);
//             // qDebug() << "Color at i: " + theColor.name();
         }

        return true;
    }


    return false;
}


QColor LED_FadeInFadeOut2Colors::getData(const int &index)
{

//     mEffectBytesWithSpeed.at(index %(mEffectBytesWithSpeed.count() -1))

    return  data[index %(data.count() -1)];
}
