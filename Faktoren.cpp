/* 
 * Datei:  Faktoren.cpp
 * Author: Sebastian Müller
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#include <iostream>
#include <sstream>
#include "Faktoren.h"
using namespace std;

//Konstruktor: initalisiert alle Größen mit Wert 0
Faktoren::Faktoren() {
    Faktoren::spannung = 0;
    Faktoren::temperatur = 0;
    Faktoren::prozess = 0;
    Faktoren::spannungFaktor = 0;
    Faktoren::temperaturFaktor = 0;
    Faktoren::prozessFaktor = 0;
}

//Tut nichts.
Faktoren::~Faktoren() { }    

//Findet gemittelten Wert im R^2
double Faktoren::interpolation(double wert, double x1, double x2, double y1, double y2) {
    //Steigung per Steigungsdreieck
    double steigung = ( y2 - y1 ) / ( x2 - x1 );
    //Anwenden des Steigungsdreiecks ausgehend von x1
    double ergebnis = y1 + ( wert - x1 ) * steigung;
    
    return ergebnis;
}

//Berechnet Faktor
double Faktoren::berechneFaktor(double wert, double arr[][2], int laenge) {
    //Lineare Suche zum finden des benötigten Wertes
        for (int i = 0; i<laenge; i++) {
            //Fall: Wert ist in Tabelle
            if(arr[i][0] == wert) {
                return arr[i][1];
                break;
            }
            //Fall: Wert ist nicht in Tabelle
            else if(arr[i][0] > wert) {
                return Faktoren::interpolation(wert, arr[i-1][0], arr[i][0], arr[i-1][1], arr[i][1]);
                break;
            }
        }
        return 0;
}  
    
//Berechnet den Faktor der Spannung
bool Faktoren::berechneSpannungFaktor() {
    //Prüfen ob Spannung in angegebenen Grenzen liegt
    if(Faktoren::spannung >= 1.08 && Faktoren::spannung <= 1.32) {
        //Wertetabelle aus Spezifikation
        double werte[7][2] = { {1.08, 1.121557}, {1.12, 1.075332}, {1.16, 1.035161}, {1.20, 1.000000}, {1.24, 0.968480}, {1.28, 0.940065}, {1.32, 0.914482}};
        
        //Berechnen
        Faktoren::spannungFaktor = Faktoren::berechneFaktor(Faktoren::spannung, werte, 7);
        cout << "\nSpannung erfolgreich eingetragen!\n\n";
        return true;
    }
    //Spannung liegt nicht in angegebenen Grenzen
    else {
        cout << endl << "Spannung hat keinen gueltigen Wert!" << endl;
        cout << "Bitte Spannung erneut eingeben!\n"<< endl;
        return false;
    }
}


bool Faktoren::berechneTemperaturFaktor() {
    //Prüfen ob Temperatur in angegebenen Grenzen liegt
    if(Faktoren::temperatur >= -25 && Faktoren::temperatur <= 125) {
        //Wertetabelle
        double werte[15][2] = { {-25, 0.897498}, {-15, 0.917532}, {0, 0.948338}, {15, 0.979213}, {25, 1.000000}, {35, 1.020305}, {45, 1.040540}, {55, 1.061831}, {65, 1.082983}, {75, 1.103817} ,{85, 1.124124}, {95, 1.144245}, {105, 1.164563}, {115, 1.184370}, {125, 1.204966} };
        
        //Berechnen
        Faktoren::temperaturFaktor = Faktoren::berechneFaktor(Faktoren::temperatur, werte, 15);
        cout << "\nTemperatur erfolgreich eingetragen!\n\n";
        return true;
    }
    else {
        cout << endl << "Temperatur hat keinen gueltigen Wert!" << endl;
        cout << "Bitte Temperatur erneut eingeben!\n"<< endl;
        return false;
    } 
}

//Berechnet Faktor für den Prozess
bool Faktoren::berechneProzessFaktor() {
    //Einfache Abfrage der 3 möglichen Werte, ansonsten Fehlermeldung
    if (Faktoren::prozess == 1) {
        Faktoren::prozessFaktor = 1.174235;
        cout << "\nProzessfaktor erfolgreich eingetragen!\n\n";
        return true;
    }
    else if (Faktoren::prozess == 2) {
        Faktoren::prozessFaktor = 1.000000;
        cout << "\nProzessfaktor erfolgreich eingetragen!\n\n";
        return true;
    }
    else if (Faktoren::prozess == 3) {
        Faktoren::prozessFaktor = 0.876148;
        cout << "\nProzessfaktor erfolgreich eingetragen!\n\n";
        return true;
    }
    //Fehler:
    else {
        cout << endl << "Prozess hat keinen gueltigen Wert (1, 2, 3)!" << endl;
        cout << "Bitte Prozessfaktor erneut eingeben!\n"<< endl;
        return false;
    }
            
}          

double Faktoren::getSpannung() const {
    return Faktoren::spannung;
}

double Faktoren::getTemperatur() const {
    return Faktoren::temperatur;
}

short Faktoren::getProzess() const {
    return Faktoren::prozess;
}

void Faktoren::getFaktoren(double& spgFaktor, double& tmpFaktor, double& przFaktor) const {
    spgFaktor = Faktoren::spannungFaktor;
    tmpFaktor = Faktoren::temperaturFaktor;
    przFaktor = Faktoren::prozessFaktor;
}

bool Faktoren::setSpannung(double spannung) {
    double temp = Faktoren::spannung;
    Faktoren::spannung = spannung;
    //Faktor berechnen und auf Fehler überprüfen
    if(Faktoren::berechneSpannungFaktor()) {
        return true;
    }
    else {
        Faktoren::spannung = temp;
        return false;
    }
}

bool Faktoren::setTemperatur(double temperatur) {
    double temp = Faktoren::temperatur;
    Faktoren::temperatur = temperatur;
    //Faktor berechnen und auf Fehler überprüfen
    if(Faktoren::berechneTemperaturFaktor()) {
        return true;
    }
    else {
        Faktoren::temperatur = temp;
        return false;
    }
}

bool Faktoren::setProzess(short prozess) {
    double temp = Faktoren::prozess;
    Faktoren::prozess = prozess;
    //Faktor berechnen und auf Fehler überprüfen
    if(Faktoren::berechneProzessFaktor()) {
        return true;
    }
    else {
        Faktoren::prozess = temp;
        return false;
    }
}

void Faktoren::ausgabeFaktoren() {    
    //Konvertieren der Double in String-Werte
    stringstream NumberString;
    NumberString << Faktoren::spannungFaktor;   
    string KV = NumberString.str();
    NumberString.str("");
    NumberString << Faktoren::temperaturFaktor;
    string KT = NumberString.str();
    NumberString.str("");
    NumberString << Faktoren::prozessFaktor;
    string KP = NumberString.str();
            
    //Ausgabe
    cout << "\nFaktoren: KV: " + KV + " | KT: " + KT + " | KP: " + KP + "\n" << endl;
} 