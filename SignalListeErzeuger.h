/* 
 * Datei:  SignalListeErzeuger.h
 * Author: Kristian Maier
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#ifndef SIGNALLISTEERZEUGER_H
#define	SIGNALLISTEERZEUGER_H


#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#include "Signal.h"

using namespace std;


class SignalListeErzeuger {
private:
    Signal* signale;
    short anzahlSignale;
    string datei;
    long frequenz;
    
    void ausgabeOpenError();    
    void ausgabeReadError();
    
    
    //Hilfsfunktionen für Erzeugung der Schaltnetzdatei
    void readEntity(string& input,string& output,string& 
                        intern,string& clock);
    int  countSignals(string& input,string& output,string& intern);
    void fillList(string input, string output, string intern);
    long readFrequenz(string& clock);   
    int extractSignal(string& str);
    bool readGatterInfo();
    bool updateSignallisteMitGatter(string& line);

    //Hilfsfunktionen für Stringoperationen
    string readUntilChar(string& str, char chr) const;
    void eraseUntilChar(string& str, char chr);
    void eraseAfterChar(string& str, char chr);
    
public:
    bool setPfadSchaltnetzdatei(string pfad);
    void setFrequenz(long frequenz);
    
    short getAnzahlSignale() const;
    string getPfadSchaltnetzdatei() const;
    long getFrequenz() const;
    
    Signal* erzeugeSignalliste();      
    void ausgabeSchaltnetzdatei();      
    void ausgabeSignale();
    
    
        
};

#endif	/* SIGNALLISTEERZEUGER_H */

