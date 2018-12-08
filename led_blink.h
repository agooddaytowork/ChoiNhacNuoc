#ifndef LED_BLINK_H
#define LED_BLINK_H

#include <QByteArray>
#include <QColor>
#include <QVector>
#include <QList>

class LED_Blink
{
public:
    int mSpeed;
    QColor mColor;
    QList<QColor> data;
    QList<QColor> dataWithSpeed;

public:
    LED_Blink();
    bool setSpeed(const int &speed);
    bool setEffects(const QColor &color);

    QColor getData(const int &index) ;
};

#endif // LED_BLINK_H
