#ifndef LED_SOLID_H
#define LED_SOLID_H
#include <QByteArray>
#include <QColor>
#include <QVector>
#include <QList>

class LED_Solid
{
    QColor mColor;


public:
    LED_Solid();
    bool setEffects(const QColor &color);
    QColor getData() ;
};

#endif // LED_SOLID_H
