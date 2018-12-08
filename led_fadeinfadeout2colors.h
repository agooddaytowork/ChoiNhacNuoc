#ifndef LED_FADEINFADEOUT2COLORS_H
#define LED_FADEINFADEOUT2COLORS_H

#include <QByteArray>
#include <QColor>
#include <QVector>
#include <QList>

class LED_FadeInFadeOut2Colors
{
    QColor mColorHead, mColorTail;
    QList<QColor> data;
    QList<QColor> dataWithSpeed;
    int mFrameNo;

public:
    LED_FadeInFadeOut2Colors();
    bool setEffects(const QColor &Headcolor, const QColor &TailColor, const int &frameNo);

    QColor getData(const int &index) ;
};

#endif // LED_FADEINFADEOUT2COLORS_H
