#ifndef LED_STROBE_H
#define LED_STROBE_H

#include <QByteArray>
#include <QColor>
#include <QVector>
#include <QList>


class LED_Strobe
{
    int mSpeed;
    QColor mColor;
    QList<QColor> data;
    QList<QColor> dataWithSpeed;

public:
    LED_Strobe();
    bool setSpeed(const int &speed);
    bool setEffects(const QColor &color);

    QColor getData(const int &index) ;

};

#endif // LED_STROBE_H
