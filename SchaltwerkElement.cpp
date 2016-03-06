/*
 * Datei:  SchaltwerkElement.cpp
 * Author: Kristian Maier
 *
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#include <vector>
#include "SchaltwerkElement.h"

SchaltwerkElement::SchaltwerkElement(GatterTyp* gTyp){
     this->typ = gTyp;
     
     this->name = "NULL";     
     this->laufzeitEinzelgatter = 0;
     this->anzahlNachfolger = 0;
     this->anzahlEingangssignale = 0;
 }
 
SchaltwerkElement::~SchaltwerkElement(){}

int SchaltwerkElement::getAnzahlNachfolger() const {
    return anzahlNachfolger;
}
short SchaltwerkElement::getAnzahlEingangssignale() const {
    return anzahlEingangssignale;
}


bool SchaltwerkElement::getIsAusgangsElement() const {
    return isAusgangsElement;
}

bool SchaltwerkElement::getIsEingangsElement() const {
    return isEingangsElement;
}

double SchaltwerkElement::getLaufzeitEinzelgatter() const {
    return laufzeitEinzelgatter;
}

string SchaltwerkElement::getName() const {
    return name;
}

GatterTyp* SchaltwerkElement::getTyp() const{
    return typ;
}

SchaltwerkElement* SchaltwerkElement::getNachfolger(int pos) const{
    if(pos < 0 || pos >= anzahlNachfolger){
        return NULL;
    }
    return nachfolgerElemente[pos];
}

void SchaltwerkElement::setName(string n){
    this->name = n;
}

void SchaltwerkElement::setAnzahlNachfolger(int anzahlN){
    this->anzahlNachfolger = anzahlN;
}

void SchaltwerkElement::setAnzahlEingangssignale(short anzahlE){
    this->anzahlEingangssignale = anzahlE;
}

void SchaltwerkElement::setIsEingangsElement(bool isEingangsEl){
    this->isEingangsElement = isEingangsEl;
}

void SchaltwerkElement::setIsAusgangsElement(bool isAusgangsEl){
    this->isAusgangsElement = isAusgangsEl;
}

void SchaltwerkElement::setLaufzeitEinzelgatter(double lfz){
    this->laufzeitEinzelgatter = lfz;
}

void SchaltwerkElement::nachfolgerHinzufuegen(SchaltwerkElement* schaltwerkElement, int pos){
    
    if(!(pos < 0 || pos >= 5)){
        nachfolgerElemente[pos] = schaltwerkElement;
        anzahlNachfolger++;
    }
}