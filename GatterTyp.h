/* 
 * Datei:  GatterTyp.h
 * Author: Maxim Köhler
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#ifndef GATTERTYP_H
#define	GATTERTYP_H

#include <iostream>
using namespace std;

class GatterTyp {
    

protected:
    string name;
    double grundLaufzeit;
    short lastFaktor;
    short lastKapazitaet;
    short eingaenge;
    
public:
    GatterTyp();
    ~GatterTyp();
    string getName();
    double getGrundLaufzeit();
    short getLastFaktor();
    short getLastKapazitaet();
    short getEingaenge();
    virtual bool getIsFlipflop();
    void setName( string n );
    void setGrundLaufzeit( double gl );
    void setLastFaktor( short lf );
    void setLastKapazitaet( short lk );
    void setEingaenge( short ei );
    bool isValid();
    void out();
    
    
};

#endif	/* GATTERTYP_H */

