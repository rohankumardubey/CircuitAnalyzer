/* 
 * Datei:  Signal.h
 * Author: Kristian Maier
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#ifndef SIGNAL_H
#define	SIGNAL_H

#include <string>

using namespace std;


class Signal {
    
public:
    enum signalTypen {
        EINGANG,
        INTERN,
        AUSGANG,
        UNBEKANNT
    };
    
private:    
    
    signalTypen signalTyp;
    string quelle;
    string quellenTyp;
    string ziele[5];
    int anzahlZiele;

    
public:
    
    Signal();
    ~Signal(){};
    
    int getAnzahlZiele() const ;
    signalTypen getSignalTyp() const;
    string getQuelle() const;
    string getQuellenTyp() const;
    string getZiel(int pos) const;
    
    void setAnzahlZiele(int anzahlZiele);
    void setSignalTyp(signalTypen sigTyp);
    void setQuelle(string quelle);
    void setQuellenTyp(string quellenTyp);
    void zielHinzufuegen(string gatterName, int pos);

};

#endif	/* SIGNAL_H */

