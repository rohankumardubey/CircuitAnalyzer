/* 
 * Datei:  GraphErzeuger.h
 * Author: Sebastian Müller
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#ifndef GRAPHERZEUGER_H
#define	GRAPHERZEUGER_H

#include "Bibliothek.h"
#include "ListenElement.h"
#include "Signal.h"

class GraphErzeuger { 
private:
    Bibliothek* bibliothek;
    ListenElement* startElement;
    ListenElement* endElement;
    Signal* signale;
    short anzahlSignale;
    
    bool erzeugeListe();
    void push_back(ListenElement* elem);
    SchaltwerkElement* sucheGatter(string gatter);
    SchaltwerkElement* sucheNachNameInListe(string name);
    bool signalBenutztTest(Signal* sig);
    bool gatterFehlerTest(SchaltwerkElement* elem);
    
    
public:
    GraphErzeuger();
    
    //Kris Methoden
    bool erzeugeGraph();
    void ausgabeGraph();
    
    //Sebastian Methoden
    bool erzeugeGraph2();

    
    void setBibliothek(Bibliothek* bib);
    Bibliothek* getBibliothek();
    void setStartElement(ListenElement* element);
    ListenElement* getStartElement();
    void setEndElement(ListenElement* element);
    ListenElement* getEndElement();
    void setSignale(Signal* sig);
    inline Signal* getSignale();
    void setAnzahlSignale(short signale);
    short getAnzahlSignale();
    
};


#endif	/* GRAPHERZEUGER_H */

