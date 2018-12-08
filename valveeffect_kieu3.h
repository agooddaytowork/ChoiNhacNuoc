#ifndef VALVEEFFECT_KIEU3_H
#define VALVEEFFECT_KIEU3_H

#include <QFile>
#include <QString>
#include <QByteArray>
#include <QList>
#include <QBitArray>

class ValveEffect_Kieu3 // Kieu 3
{    bool mEffectValid;
     QString mFilePath;
      QByteArray mEffectBytes;
       QByteArray mEffectBytesWithSpeed;
        QByteArray mEffectBytesForceRepeat;
         int mSpeed;
          bool mForceRepeat;
           bool mForceRepeatJustChanged;
            int mRepeatTime;
             int mFrameNo;
              bool mNewPathJustChanged;
 public:
              ValveEffect_Kieu3();
               bool setNewPath( QString filePath);
                bool isEffectValid();
                 bool setSpeed(const int &speed);
                  bool setForceRepeat(const bool &forcedRepeat, const int &repeatTime);
                   bool getData(const int &index, const int &order);
};

#endif // VALVEEFFECT_KIEU3_H
