/* 
 * Datei:  Menue.h
 * Author: Florian König
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#ifndef MENUE_H
#define	MENUE_H

#include <iostream>
#include <string>
#include <stdlib.h>

#include "Faktoren.h"
#include "Bibliothek.h"
#include "SignalListeErzeuger.h"
#include "GraphErzeuger.h"
#include "LaufzeitAnalysator.h"
#include "Signal.h"

using namespace std;

class Menue {
private:
    Faktoren meineFaktoren;
    Bibliothek meineBibliothek;
    SignalListeErzeuger meinSignalListeErzeuger;
    GraphErzeuger meinGraphErzeuger;
    LaufzeitAnalysator meinLaufzeitAnalysator;
    Signal* signale;
    
    bool spannung_gesetzt;
    bool temperatur_gesetzt;
    bool prozess_gesetzt;
    bool bibliothekspfad_gesetzt;
    bool schaltnetzpfad_gesetzt;
       
    void pause();
    void screenLoeschen();    
    void clear_cin();
    
    void faktorenMenue();
    void bibliothekMenue();
    void schaltwerkMenue();
    void analyse();
    void menueKopf();
    void testWerteEinfuegen();
    
public:
    Menue();
    ~Menue();
    void start();

       
    
};


#endif	/* MENUE_H */

