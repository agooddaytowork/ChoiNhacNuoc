#ifndef LED_FADEINFADEOUT_H
#define LED_FADEINFADEOUT_H

#include <QByteArray>
#include <QColor>
#include <QVector>
#include <QList>


class LED_FadeInFadeOut
{

    int mSpeed;
    QColor mColor;
    QList<QColor> data;
    QList<QColor> dataWithSpeed;

public:
    LED_FadeInFadeOut();
    bool setSpeed(const int &speed);
    bool setEffects(const QColor &color);

    QColor getData(const int &index) ;
};

#endif // LED_FADEINFADEOUT_H
