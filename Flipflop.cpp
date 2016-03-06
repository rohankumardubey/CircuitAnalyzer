/* 
 * Datei:   Flipflop.cpp
 * Author:  Maxim Köhler
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#include "Flipflop.h"
#include "GatterTyp.h"

//Konstrutor: Initialisiert die Attribute
Flipflop::Flipflop() {
    setupTime = holdTime = lastKapazitaetClock = -1;
}

//Destruktor
Flipflop::~Flipflop() {
}

//setzt die Setupzeit
void Flipflop::setSetupTime (short st) {
    if( st >= 0 )
        setupTime = st;
}

//setzt die Haltezeit
void Flipflop::setHoldTime(short ht) {
    if( ht >= 0 )
        holdTime = ht;
}

//setzt die Takt-Lastkapazität
void Flipflop::setLastKapazitaetClock(short lkc) {
    if( lkc >= 0 )
        lastKapazitaetClock = lkc;
}

//gibt die Setupzeit zurück
short Flipflop::getSetupTime() {
    return setupTime;
}

//gibt die Haltezeit zurück
short Flipflop::getHoldTime() {
    return holdTime;
}

//gibt die Takt-Lastkapazität zurück
short Flipflop::getLastKapazitaetClock() {
    return lastKapazitaetClock;
}

//gibt zurück, dass es sich um ein Flipflop handelt
bool Flipflop::getIsFlipflop() {
    return true;
}

//gibt alle Attribute aus
void Flipflop::out() {
    cout << "Flipflop '" << name << "':" << endl;
    cout << "Grundlaufzeit: " << grundLaufzeit << endl;
    cout << "Lastfaktor: " << lastFaktor << endl;
    cout << "Lastkapazitaet: " << lastKapazitaet << endl;
    cout << "Eingaenge: " << eingaenge << endl;
    cout << "Setupzeit: " << setupTime << endl;
    cout << "Haltezeit: " << holdTime << endl;
    cout << "Takt-Lastkapazitaet: " << lastKapazitaetClock;
}

//gibt zurück, ob das Objekt fehlerfrei ist
bool Flipflop::isValid() {
    return (name != "" && grundLaufzeit >= 0.0 && lastFaktor >= 0 && lastKapazitaet >= 0 
            && eingaenge >= 0 && setupTime >= 0 && holdTime >= 0 && lastKapazitaetClock >= 0);
}