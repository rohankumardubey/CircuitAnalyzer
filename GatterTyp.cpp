/* 
 * Datei:   GatterTyp.cpp
 * Author:  Maxim Köhler
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#include "GatterTyp.h"

using namespace std;

//Konstruktor: Initialisiert die Attribute
GatterTyp::GatterTyp() {
    name = "";
    grundLaufzeit = -1.0;
    lastFaktor = lastKapazitaet = eingaenge = -1;
}

//Destruktor
GatterTyp::~GatterTyp() {
}

//Überprüft, ob das Gatter fehlerfrei ist
bool GatterTyp::isValid() {
    return ( name != "" && grundLaufzeit >= 0.0 && lastFaktor >= 0 && lastKapazitaet >= 0 && eingaenge >= 0 );
}

//gibt zurück, ob Gatter ein Flipflop ist
bool GatterTyp::getIsFlipflop() {
    return false;
}

//gibt den Namen zurück
string GatterTyp::getName() {
    return name;
}

//gibt die Grundlaufzeit zurück
double GatterTyp::getGrundLaufzeit() {
    return grundLaufzeit;
}

//gibt den Lastfaktor zurück
short GatterTyp::getLastFaktor() {
    return lastFaktor;
}

//gibt die Lastkapazität zurück
short GatterTyp::getLastKapazitaet() {
    return lastKapazitaet;
}

//Gibt die Eingänge zurück
short GatterTyp::getEingaenge() {
    return eingaenge;
}

//setzt den Namen
void GatterTyp::setName( string n ) {
    name = n;
}

//setzt die Grundlaufzeit
void GatterTyp::setGrundLaufzeit( double gl ) {
    if( gl >= 0.0 )
        grundLaufzeit = gl;
}

//setzt den Lastfaktor
void GatterTyp::setLastFaktor( short lf ) {
    if( lf >= 0 )
        lastFaktor = lf;
}

//setzt die Lastkapazitaet
void GatterTyp::setLastKapazitaet( short lk ) {
    if( lk >= 0 )
        lastKapazitaet = lk;
}

//setzt die Eingaenge
void GatterTyp::setEingaenge( short ei ) {
    if( ei >= 0 )
        eingaenge = ei;
}

//gibt alle Attribute aus
void GatterTyp::out () {
    cout << "GatterTyp '" << name << "':" << endl;
    cout << "Grundlaufzeit: " << grundLaufzeit << endl;
    cout << "Lastfaktor: " << lastFaktor << endl;
    cout << "Lastkapazitaet: " << lastKapazitaet << endl;
    cout << "Eingaenge: " << eingaenge << endl << endl;
}