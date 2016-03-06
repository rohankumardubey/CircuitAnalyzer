/* 
 * Datei:  LaufzeitAnalysator.h
 * Author: Kristian Maier
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#ifndef LAUFZEITANALYSATOR_H
#define	LAUFZEITANALYSATOR_H

#include <map>
#include <iostream>
#include <string>
#include "ListenElement.h"
#include "Faktoren.h"
#include "Flipflop.h"

using namespace std;

class LaufzeitAnalysator {
private:
    Faktoren* faktoren;
    ListenElement* startElement;
    long frequenz;
    string uebergangspfad;
    string ausgangspfad;
    double laufzeitUebergangspfad;
    double laufzeitAusgangspfad;
    
    struct DFS_Daten {
        SchaltwerkElement* vaterElement;
        double pfadLaufzeit;
    };       
    map<SchaltwerkElement*, DFS_Daten> DFS_Zwischenspeicher;
    
    
    void berechneLaufzeitEinzelgatter();
    bool dfs(ListenElement* start);
    bool dfs_visit(SchaltwerkElement* k, SchaltwerkElement* s, string pfad);
    double berechneFrequenz(SchaltwerkElement* flipFlop, double laufzeitUeberfuehrung);
    bool zyklensuche(SchaltwerkElement* v);
    
public:
    LaufzeitAnalysator();
    
    void setFaktoren(Faktoren* fak);
    void setStartElement(ListenElement* start);
    
    bool start_LZA();
    bool flipflopsVorhanden();
    
    long getFrequenz();
    string getUebergangspfad();
    string getAusgangspfad();
    double getLaufzeitUebergangspfad();
    double getLaufzeitAusgangspfad();
    
};

#endif	/* LAUFZEITANALYSATOR_H */

