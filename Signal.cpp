/* 
 * Datei:  Signal.cpp
 * Author: Kristian Maier
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#include "Signal.h"


Signal::Signal(){
    signalTyp = UNBEKANNT;
    anzahlZiele=0;
    quelle = "";
    quellenTyp = "";
    for(int i=0; i<5; i++){
        ziele[i] = "";
    }
}

int Signal::getAnzahlZiele() const {
    return anzahlZiele;
}

Signal::signalTypen Signal::getSignalTyp() const{
    return Signal::signalTyp;
}

string Signal::getQuelle() const {
    return quelle;
}

string Signal::getQuellenTyp() const {
    return quellenTyp;
}

string Signal::getZiel(int pos) const{
    //Test ob Arraygrenzen eingehalten werden
    if(pos>=0 && pos <5){
        return ziele[pos];
    }
    return "";
}

void Signal::setAnzahlZiele(int anzahlZiele) {
    this->anzahlZiele = anzahlZiele;
}

void Signal::setSignalTyp(signalTypen sigTyp){
    signalTyp = sigTyp;
}

void Signal::setQuelle(string quelle) {
    this->quelle = quelle;
}

void Signal::setQuellenTyp(string quellenTyp) {
    this->quellenTyp = quellenTyp;
}

void Signal::zielHinzufuegen(string gatterName, int pos){
    //Test ob Arraygrenzen eingehalten werden
    if(pos>=0 && pos <5){
        ziele[pos] = gatterName; 
        anzahlZiele++;
    }
   
}
