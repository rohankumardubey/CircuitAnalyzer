/* 
 * Datei:  Bibliothek.h
 * Author: Maxim Köhler
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#ifndef BIBLIOTHEK_H
#define	BIBLIOTHEK_H

#include <string>
#include <vector>
#include <fstream>
#include "GatterTyp.h"

using namespace std;

class Bibliothek {
private:
    vector<GatterTyp*> bibElemente;
    string datei;
    
    void openError();
    void readError();
    
public:
    Bibliothek( string pfad = "" );
    ~Bibliothek();
    string getPfad();
    GatterTyp* getBibElement( string typ );
    void dateiAusgabe();
    void dateiAuswerten();
    bool pfadEinlesen( string pfad );
    
};

#endif	/* BIBLIOTHEK_H */

