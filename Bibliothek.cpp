/* 
 * Datei:  Bibliothek.cpp
 * Author: Maxim Köhler
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#include "Bibliothek.h"
#include "Flipflop.h"
#include <istream>
#include <sstream>
using namespace std;


//Diese Methode gibt eine Fehlermeldung, dass die Datei nicht geoeffnet werden konnte, aus
void Bibliothek::openError() {
    cout << "FEHLER: Die Datei konnte nicht geoeffnet werden!" << endl; //PAUSE!!!
}

//Diese Methode gibt eine Fehlermeldung, dass die Datei nicht gelesen werden konnte, aus
void Bibliothek::readError() {
    cout << "FEHLER beim Lesen der Datei!" << endl; //PAUSE!!!
}

/* 
 * Diese Methode gibt einen Zeiger auf den GatterTyp zurück, der den Namen,
 * den man über den String typ der Funktion übergibt, hat
 */
GatterTyp* Bibliothek::getBibElement( string typ ) {
    unsigned long length = bibElemente.size();
    
    /*
     * Für jeden GatterTyp im vector bibElemente wird überprüft, ob der Name
     * mit typ übereinstimmt, und gegebenenfalls zurückgegeben
     */
    for( int i = 0; i < length; i++ ) {
        if( bibElemente.at( i )->getName() == typ )
            return bibElemente.at( i );
    }
    cout << endl << "GatterTyp nicht gefunden!" << endl;
    return NULL;
}

//gibt die Bibliothekdatei mit nummerierten Zeilen aus
void Bibliothek::dateiAusgabe() {
    //Datei öffnen
    ifstream file;
    file.open( Bibliothek::datei.c_str(), ios::in );
    
    //überprüfen, ob Datei geöffnet werden konnte
    if ( !file.is_open() ) {
        openError();
        return;
    }
    
    string line;
    int counter = 0;
    
    //Für jede Zeile der Datei: Zeilennummer und die Zeile an sich ausgeben
    while( !file.eof()) {
        //Überprüfung, ob Zeile gelesen werden kann
        if ( getline( file, line ))
            cout << " #" << counter << ":\t" << line << endl;
        else
            readError();
        counter++;
    }
}

//Wertet die Datei aus und speichert die gefundenen Gattertypen im vector bibElemente
void Bibliothek::dateiAuswerten() {
    //Datei öffnen
    ifstream file;
    file.open( Bibliothek::datei.c_str(), ios::in );
    
    //Überprüfung, ob die Datei geöffnet werden konnten
    if( !file.is_open() ) {
        openError();
        return;
    }
    
    string line;
    GatterTyp* tempGatter = new GatterTyp();
    Flipflop* tempFF = NULL;
    bool currentIsFF = false;
    
    //Liest jede einzelne Zeile in einer while-Schleife aus
    while( !file.eof() ) {
        //Kann Zeile gelesen werden?
        if( getline( file, line )) {
            
            //Handelt es sich um eine Zeile, die einen neuen GatterTyp beginnt?
            if( line[0] == '[' && line[1] != '[' ) {
                
                //Der zuletzt bearbeitete Gattertyp wird gespeichert, falls er fehlerfrei ist, sonst gelöscht
                //Unterscheidung zwischen GatterTyp und Flipflop
                if( !currentIsFF && tempGatter->isValid() )
                    bibElemente.push_back( tempGatter );
                else if( currentIsFF && tempFF->isValid() )
                    bibElemente.push_back( tempFF );
                else
                    delete tempGatter;
                
                //Ein neuer Gattertyp wird erstellt und der in der Zeile angegebene Name gespeichert
                //Das Flipflop dff wird gesondert behandelt
                if( line.find( "dff" ) == 1 ) {
                    currentIsFF = true;
                    tempFF = new Flipflop();
                    tempFF->setName( "dff" );
                    tempGatter = tempFF;
                }
                else {
                    currentIsFF = false;
                    tempGatter = new GatterTyp();
                    tempGatter->setName( line.substr( 1, line.find( "]" )-1 ));
                }
            }
            
            //Spaghetticode, der alle möglichen Fälle für Zeilen abarbeitet und dementsprechend Attribute speichert
            //Zeile gibt Eingaenge an?
            else if( line.find( "ei" ) == 0 || line.find( "ed" ) == 0 || line.find( "et" ) == 0) {
                short ei; 
                stringstream ss( line.substr( 3 ));
                if( ss >> ei ) {
                    tempGatter->setEingaenge( ei );
                }
            }
            //Zeile gibt Grundlaufzeit an?
            else if( line.find( "tpd0" ) == 0 || line.find( "tpdt" ) == 0 ) {
                double tpd0;
                stringstream ss( line.substr( 5 ));
                if( ss >> tpd0 ) {
                    tempGatter->setGrundLaufzeit( tpd0 );
                }
            }
            //Zeile gibt Lastfaktor an?
            else if( line.find( "kl" ) == 0 ) {
                short kl;
                stringstream ss( line.substr( 3 ));
                if( ss >> kl ) {
                    tempGatter->setLastFaktor( kl );
                }
            }
            //Zeile gibt Lastkapazitaet an?
            else if( line.find( "cl" ) == 0 || line.find( "cd" ) == 0 ) {
                short cl;
                stringstream ss( line.substr( 3 ));
                if( ss >> cl ) {
                    tempGatter->setLastKapazitaet( cl );
                }
            }
            //Fängt die zusätzlichen Fälle für Flipflops ab
            else if( currentIsFF ) {
                //Zeile gibt Setupzeit an?
                if( line.find( "tsetup" ) == 0 ) {
                    short tsetup;
                    stringstream ss( line.substr( 7 ));
                    if( ss >> tsetup ) {
                        tempFF->setSetupTime( tsetup );
                    }
                }
                //Zeile gibt Haltezeit an?
                else if( line.find( "thold" ) == 0 ) {
                    short thold;
                    stringstream ss( line.substr( 6 ));
                    if( ss >> thold ) {
                        tempFF->setHoldTime( thold );
                    }
                }
                //Zeile gibt Takt-Lastkapazität an?
                else if( line.find( "ct" ) == 0 ) {
                    short ct;
                    stringstream ss( line.substr( 3 ));
                    if( ss >> ct ) {
                        tempFF->setLastKapazitaetClock( ct );
                    }
                }
            }
        }
        else {
            readError();
            delete tempGatter;
            return;
        }
    }
    
    //Speichern des zuletzt bearbeiteten Gattertyps, falls dieses fehlerfrei ist
    //Sonst: Speicherbereinigung
    if( !currentIsFF && tempGatter->isValid() )
        bibElemente.push_back( tempGatter );
    else if( currentIsFF && tempFF->isValid() )
        bibElemente.push_back( tempFF );
    else
        delete tempGatter;
}

//Liest den Pfad zur Bibliotheksdatei ein
bool Bibliothek::pfadEinlesen( string pfad ) {
    //Datei öffnen
    ifstream file;
    file.open( pfad.c_str(), ios::in );
    
    //konnte Datei geöffnet werden?
    if( file ) {
        Bibliothek::datei = pfad;
        file.close();
        return true;
    }
    else {
        return false;
    }
}

//Konstruktor: Initialisierung des pfad-Attributs
Bibliothek::Bibliothek( string pfad ) {
    if( pfad == "" )
        return;
    
    //Überprüfung, ob Datei vorhanden ist
    ifstream file;
    file.open( pfad.c_str(), ios::in );
    if( file.is_open() ) {
        datei = pfad;
    }
    else {
        datei = "";
    }
}

//Destruktor: Speicherbereinigung
Bibliothek::~Bibliothek() {
    unsigned long length = bibElemente.size();
    
    //gibt den Speicher aller bibElemente frei
    for( int i = 0; i < length; i++ ) {
        delete bibElemente.at( i );
    }
}

//gibt den Pfad zur Bibliotheksdatei zurück
string Bibliothek::getPfad() {
    return datei;
}