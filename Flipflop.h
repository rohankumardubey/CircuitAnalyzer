/* 
 * Datei:  Flipflop.h
 * Author: Maxim Köhler
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#ifndef FLIPFLOP_H
#define	FLIPFLOP_H

#include "GatterTyp.h"

using namespace std;

class Flipflop: public GatterTyp{
private:
     short setupTime;
     short holdTime;
     short lastKapazitaetClock;
        
public:
     Flipflop();
     ~Flipflop();
     bool getIsFlipflop();
     short getSetupTime();
     short getHoldTime();
     short getLastKapazitaetClock();
     void setSetupTime(short st);
     void setHoldTime(short ht);
     void setLastKapazitaetClock(short lkc);
     bool isValid();
     void out();
};


#endif	/* FLIPFLOP_H */

