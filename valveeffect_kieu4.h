#ifndef VALVEEFFECT_KIEU4_H
#define VALVEEFFECT_KIEU4_H
#include <QFile>
#include <QString>
#include <QByteArray>
#include <QList>
#include <QBitArray>

class ValveEffect_Kieu4 // Kieu 7 va Kieu 9 // Kieu 5 lay odd = true
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
              ValveEffect_Kieu4();
               bool setNewPath( QString filePath);
                bool isEffectValid();
                 bool setSpeed(const int &speed);
                  bool setForceRepeat(const bool &forcedRepeat, const int &repeatTime);
                   bool getData(const int &index, const bool &odd);
};

#endif // VALVEEFFECT_KIEU4_H
