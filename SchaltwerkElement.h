/* 
 * Datei:  SchaltwerkElement.h
 * Author: Kristian Maier
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#ifndef SCHALTWERKELEMENT_H
#define	SCHALTWERKELEMENT_H

#include <string>
#include "GatterTyp.h"


using namespace std;

class SchaltwerkElement {
private:

    string name;
    GatterTyp* typ;
    double laufzeitEinzelgatter;
    SchaltwerkElement* nachfolgerElemente[5];
    int anzahlNachfolger;
    bool isEingangsElement;
    bool isAusgangsElement;
    short anzahlEingangssignale;
       
public:
    SchaltwerkElement(GatterTyp* gTyp);
    ~SchaltwerkElement();
    
      
    int getAnzahlNachfolger() const;
    short getAnzahlEingangssignale() const;
    bool getIsEingangsElement() const;
    bool getIsAusgangsElement() const;
    string getName() const;
    double getLaufzeitEinzelgatter() const;
    
    GatterTyp* getTyp() const;
    SchaltwerkElement* getNachfolger(int pos) const; 
    
    void setName(string n);
    void setAnzahlNachfolger(int anzahlN);
    void setAnzahlEingangssignale(short anzahlE);
    void setIsEingangsElement(bool isEingangsEl);
    void setIsAusgangsElement(bool isAusgangsEl);
    void setLaufzeitEinzelgatter(double lfz);
    
    void nachfolgerHinzufuegen(SchaltwerkElement* schaltwerkElement, int pos);

        
};

#endif	/* SCHALTWERKELEMENT_H */

