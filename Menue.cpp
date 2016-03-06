/* 
 * Datei:  Menue.cpp
 * Author: Florian König
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */


#include <fstream>

#include "Menue.h"

using namespace std;

/*
 * Die nachfolgenden Attribute dienen zur Kontrolle, ob jeder für die Analyse benötigte
 * Wert/Pfad gesetzt wurde. Der Konstruktor initialisiert alle Atrribute mit false
 */
Menue::Menue() { 
    bool spannung_gesetzt = false;
    bool temperatur_gesetzt = false;
    bool prozess_gesetzt = false;
    bool bibliothekspfad_gesetzt = false;
    bool schaltnetzpfad_gesetzt = false;
}

// Destruktor - Tut nichts 
Menue::~Menue() { }

 /*
  * Diese Methode wartet so lange, bis eine Eingabe getaetigt wuirde.
  * Preprozessor Abfrage, ob auf Mac oder Windows kompiliert wird.
  */
void Menue::pause() {
    #if defined( WIN32 )
        system( "pause" );
    #endif 
    #if defined( LINUX )
    cout << endl << "Enter drücken..." << endl;
    cin.get();
    #endif
}

// Diese Methode leert das Kommando-Fenster
void Menue::screenLoeschen() {
    //Preprozessor Abfrage, ob auf Mac oder Windows kompiliert wird.
     #if defined( WIN32 ) 
        system( "cls" );
     #endif
     #if defined( LINUX )
        system( "clear" );
     #endif
}

/* 
 * Diese Methode gibt das Hauptmenue auf dem Bildschirm aus.
 * Durch Eingabe einer Zahl (1-6) gelangt man in das jeweilige Untermenue,
 * kann die Analyse starten, Testwerte einfügen oder das Programm beenden
 */
void Menue::start() {
    //Solange bis return kommt
    while( true ) {
        int menuepunkt = 0;
        
        screenLoeschen();
        //Gebe Menuekopf aus
        menueKopf();
        cout << "(1) aeussere Faktoren" << endl;
        //Gibt den Spannungswert aus
        cout << "Spannung [Volt]: " << meineFaktoren.getSpannung() << endl;
        //Gibt die Temperatur aus
        cout << "Temperatur [Grad Celsius]: " << meineFaktoren.getTemperatur() << endl;
        //Gibt den Prozessfaktor aus
        cout << "Prozessor (1=slow, 2=typical, 3=fast) : " << meineFaktoren.getProzess() << "\n\n" << endl;
        cout << "(2) Bibliothek" << endl;
        //Gibt Pfad zur Bibliotheksdatei aus
        cout << "Pfad zur Bibliotheksdatei: "<< meineBibliothek.getPfad()<< "\n\n" << endl;
        cout << "(3) Schaltwerk" << endl;
        //Gibt Pfad zur Schaltnetzdatei aus
        cout << "Pfad zur Schaltwerksdatei: " << meinSignalListeErzeuger.getPfadSchaltnetzdatei() << "\n\n" << endl;
        cout << "(4) Analyse starten\n\n" << endl;
        cout << "(5) Testwerte einfuegen\n\n" << endl;
        cout << "(6) Programm beenden\n\n\n" << endl;
        cout << "Waehle einen Menuepunkt und bestaetige mit Enter: ";

        cin >> menuepunkt;
        
        //Falls keine Zahl zwischen 1 und 6 eingegeben wurde
        if( cin.fail() || menuepunkt > 6 || menuepunkt < 1 ) {
            //gebe Fehler aus
            cout << "\nUngueltige Eingabe! \n\n"; 
            pause();
        }             
        //Löscht Errorbits und Eingabgepuffer von cin
        clear_cin();
        
        switch( menuepunkt ) {
            //Startet die Methode, welche das Untermenue Faktoren ausgibt
            case 1:
                faktorenMenue();
                break;
            //Startet die Methode, welche das Untermenue Bibliothek ausgibt
            case 2: 
                bibliothekMenue();
                break;
            //Startet die Methode, welche das Untermenue Schaltwerk ausgibt
            case 3:
                schaltwerkMenue();
                break;
            //Startet die Analyse
            case 4:
                analyse();
                break;
            //Fügt Testwerte ein
            case 5:
                testWerteEinfuegen();
                cout << "\nPfad zur Bibliotheksdatei erfolgreich eingetragen!\n";
                cout << "\n\nPfad zur Schaltnetzdatei erfolgreich eingetragen!\n\n";
                pause();
                break;
            //Beendet das Programm
            case 6:
                return;
        }
    }
} 

/* 
 * Diese Methode gibt das Untermenue Faktoren auf dem Bildschirm aus.
 * Durch Eingabe einer Zahl (1-5) kann man die Werte für die Spannung, Temperatur
 * und den Prozessfaktor eintragen. Die berechneten Faktoren können mit (4) 
 * ausgegeben werden und mit (5) gelangt man zurück ins Hauptmenü
 */
void Menue::faktorenMenue() {
    unsigned int menuepunkt_faktoren = 0;
     
    //Läuft solange bis return kommt
    while( true ) {          
        screenLoeschen();

        menueKopf();
        cout << "Untermenue Aeussere Faktoren" << endl;
        //Spannungswert ausgeben
        cout << "(1) Spannung [Volt]: " << meineFaktoren.getSpannung() << endl;
        //Temperatur ausgeben
        cout << "(2) Temperatur [Grad Celsius]: " << meineFaktoren.getTemperatur() << endl;         //Prozessfaktor ausgeben
        cout << "(3) Prozess (1=slow, 2=typical, 3=fast): "<< meineFaktoren.getProzess() << endl;
        cout << "(4) Ausgabe errechneter Faktoren" << endl;
        cout << "(5) Hauptmenue\n\n\n" << endl;
        cout << "Waehle einen Menuepunkt aus und bestaetige mit Enter: ";
        cin >> menuepunkt_faktoren;
        cout << "\n\n--------------------------------------------" << endl;
        
        double faktor;
 
        //Wenn kein int-Wert oder keine Zahl zwischen 1 und 6 eingebeben wurde
         if( cin.fail() || menuepunkt_faktoren > 5 || menuepunkt_faktoren < 1 ) {
            //gebe Fehler aus
            cout << "\nUngueltige Eingabe!\n";
            pause();
         }
         //Löscht Errorbits und Eingabgepuffer von cin
         clear_cin();
        
         switch( menuepunkt_faktoren ) {
            case 1:
                //Spannungswert eingeben
                cout << "\nSpannung eingeben [Von 1.08 bis 1.32]: ";
                cin >> faktor;
                //Falls keine Zahl eingegeben wurde
                if( cin.fail() ) {
                    //gebe Fehler aus
                    cout << "Ungueltige Eingabe!";
                //ansonsten trage Spannung ein und setze zugehörige bool-Variable auf true
                } else {
                    meineFaktoren.setSpannung(faktor);
                    spannung_gesetzt = true;
                    pause();
                }
                clear_cin();
                break;
            case 2: 
                //Temperatur eingeben
                cout << "\nTemeratur eingeben [Von -25 bis 125]: ";
                cin >> faktor;
                //Falls keine Zahl eingegeben wurde
                if( cin.fail() ) {
                    //gebe Fehler aus
                    cout << "Ungueltige Eingabe"; 
                //ansonsten trage Temperatur ein und setze zugehörige bool-Varibale auf true
                } else {
                    meineFaktoren.setTemperatur(faktor);
                    temperatur_gesetzt = true;
                    pause();                
                }
                clear_cin();
                break;
            case 3:
                //Prozessfaktor eingeben
                cout << "\nProzessfaktor eingeben: ";
                cin >> faktor;
                //Falls keine Zahl eingeben wurde
                if( cin.fail() ) {
                    //gebe Fehler aus
                    cout << "Ungueltige Eingabe";
                    pause();
                //ansonsten trage Prozessfaktor ein und setze zugehörige bool-Varibale auf true
                } else {
                    meineFaktoren.setProzess(faktor);
                    bool prozess_gesetzt = true;
                    pause();
                }
                clear_cin();
                break;
            //Gibt alle berechneten Faktoren aus
            case 4:
                meineFaktoren.ausgabeFaktoren();
                pause();
                break;
            //return um die while-Schleife zu verlassen und ins Hauptmenü zurückzukehren
            case 5:
                 return;
          }
      }

 }
 
/*
 * Diese Methode gibt das Untermenue Bibliothek auf dem Bildschirm aus.
 * Durch Eingabe einer Zahl (1-3) kann man den Pfad zur Bibliotheksdatei eintragen,
 * die Bibliotheksdatei ausgeben oder zurück ins Hauptmenü gelangen.
 */
void Menue::bibliothekMenue() {
    int menuepunkt_bibliothek = 0;
     //Läuft solange bis return kommt
     while( true ) {
         screenLoeschen();

         menueKopf();
         //Gibt den Pfad zur Bibliotheksdatei aus
         cout << "(1) Pfad zur Bibliotheksdatei: " << meineBibliothek.getPfad() << endl; //Pfad anzeigen
         cout << "(2) Ausgabe der Bibliotheksdatei" << endl;
         cout << "(3) Hauptmenue\n\n\n"  << endl;
         cout << "Waehle einen Menuepunkt und bestaetige mit Enter: ";
         cin >> menuepunkt_bibliothek;
         cout << "----------------------------------------" << endl;         
         
         //Falls keine Zahl zwischen 1 und 3 eingegeben wurde
         if( cin.fail() || menuepunkt_bibliothek > 3 || menuepunkt_bibliothek < 1 ) {
            //gebe Fehler aus
            cout << "\nUngueltige Eingabe!\n";            
            pause();
        }
        
         clear_cin();
         string pfad = "";

         switch( menuepunkt_bibliothek ) {
            //Pfad zur Bibliothek eingeben
            case 1:
                cout << "Pfad zur Bibliotheksdatei eingeben: ";
                cin >> pfad;
                //Wenn der Pfad erfolgreich eingelesen werden konnte, eintragen des Pfades
                //und zugehörige bool-Variable auf true setze
                if( meineBibliothek.pfadEinlesen(pfad) ){
                    meineBibliothek.dateiAuswerten();
                    bibliothekspfad_gesetzt = true;
                    cout << "Pfad erfolgreich eingetragen!\n";  
                //ansonsten gebe Fehler aus
                } else {
                    cout << "Pfad falsch oder Datei kann nicht geoeffnet werden!" << endl;
                } 
                clear_cin();
                pause();
                break;
            //Bibliotheksdatei ausgeben
            case 2: 
                meineBibliothek.dateiAusgabe();
                cout << "\n";
                pause();
                break;
            //Ins Hauptmenü zurückkehren
            case 3:
                return;
          }
     
    }
 }
 
/*
 * Diese Methode gibt das Untermenue Schaltwerk auf dem Bildschirm aus.
 * Durch Eingabe einer Zahl (1-5) kann man den Pfad zur Schaltnetzdatei eintragen,
 * die Schaltnetzdatei, die Signale oder die Graphstruktur ausgeben und ins
 * Menü zurückkehren.
 */
void Menue::schaltwerkMenue() {
     int menuepunkt_schaltwerk = 0;
     //Solange bis return kommt
     while( true ) {
         screenLoeschen();

         menueKopf();
         cout << "Untermenue Schaltwerk" << endl;
         //Gebe Pfad zur Schaltnetzdatei aus
         cout << "(1) Pfad zur Schaltnetzdatei: " << meinSignalListeErzeuger.getPfadSchaltnetzdatei() << endl; //Pfad angeben
         cout << "(2) Ausgabe der Schaltnetzdatei" << endl;
         cout << "(3) Ausgabe der Signale" << endl;
         cout << "(4) Ausgabe der Graphstruktur" << endl;
         cout << "(5) Hauptmenue\n\n" << endl;
         cout << "Waehle einen Menuepunkt und bestaetige mit Enter: ";
         cin >> menuepunkt_schaltwerk;         
         cout << "----------------------------------------" << endl;       

         //Falls keine Zahl zwischen 1 und 5 eingegeben wurde
         if( cin.fail() || menuepunkt_schaltwerk > 5 || menuepunkt_schaltwerk < 1 ) {
            //gebe Fehler aus
            cout << "\nUngueltige Eingabe!\n";            
            pause();
        }
         
        clear_cin();
        
        string pfad = "";
        
          switch( menuepunkt_schaltwerk ) {
            //Pfad zur Schaltnetzdatei eingeben
            case 1:
                cout << "Pfad zur Schaltnetzdatei eingeben: ";
                cin >> pfad;
                //Wenn eine existierende .txt Datei als Pfad angebeben wurde
                if( meinSignalListeErzeuger.setPfadSchaltnetzdatei(pfad) ) {
                        signale = meinSignalListeErzeuger.erzeugeSignalliste();
                    //falls es sicht bei der .txt-Datei nicht um eine Schaltwerksdatei handelt, wird der Pfad
                    //zwar einegtragen, die bool-Variable bleibt jedoch false, also ist ein starten der
                    //Analyse nicht möglich
                    if( signale == NULL ) {
                        cout << "Pfad nicht eingetragen!\n";
                        cout << "Starten der Analyse nicht moeglich!\n" << endl;
                        schaltnetzpfad_gesetzt = false;
                    //trage den Pfad ein und setze die zugehörige bool-Varibable auf true
                    } else {
                        cout << "Pfad erfolgreich eingetragen!\n";
                        schaltnetzpfad_gesetzt = true;
                    }
                 //Gebe Fehler aus, dass der Pfad nicht korrekt ist
                } else {
                    cout << "Pfad falsch oder Datei kann nicht geoeffnet werden.\n" << endl;
                } 
                clear_cin();
                pause();
                break;
            //Gebe die Schaltnetzdatei aus
            case 2: 
                meinSignalListeErzeuger.ausgabeSchaltnetzdatei();
                pause();//Schaltnetzdatei ausgeben
                break;
            //Gebe die Singale aus
            case 3:
                meinSignalListeErzeuger.ausgabeSignale();
                pause();//Signal ausgeben
                break;
            //Setzt im Grapherzeuger die zum Erzeugen benötigten Elemente
            //und startet, wenn alles korrekt, ist die Erzeugung des Graphen und die Ausgabe
            //auf dem Bildschirm
            case 4:
                //Ausgabe der Graphstruktir nur möglich, falls der Pfad zur Bibliothektsdatei gesetzt ist
                if( bibliothekspfad_gesetzt == true ) {
                    meinGraphErzeuger.setBibliothek(&meineBibliothek);                
                    meinGraphErzeuger.setAnzahlSignale(meinSignalListeErzeuger.getAnzahlSignale());
                    meinGraphErzeuger.setSignale(signale);
                    
                    if( meinGraphErzeuger.erzeugeGraph() ) {
                    meinGraphErzeuger.ausgabeGraph();
                    } 
                       
                 } else {
                    cout << "\nPfad zur Bibliotheksdatei nicht eingetragen!\n" << endl;
                    cout << "Ausgabe der Graphstruktur nicht moeglich!\n" << endl;
                 }
                pause();
                break;
            //Ins Hauptmenü zurückkehren
            case 5:
              return;
          }

    }
  }
  
/*
 * Diese Methode trägt für die Spannungswerte,Temperatur und den Prozessfaktor Beispielwerte
 * ein und setzt die Pfade für die Bibliotheksdatei, sowie die Schaltnetzdatei.
 * (Das setzen der Pfade ist nur möglich, falls sich die .txt Dateien im Projektordner befinden)
 *  Sie setzt ebenfalls alle bool-Variablen auf true, damit die Analyse starten kann
 */
void Menue::testWerteEinfuegen() {
      double spannung = 1.2;
      double temperatur = 55;
      short prozess = 1;
      string pfad_bib = "bib.txt";
      string pfad_schaltnetz = "csd.txt";
      
      //alle Faktoren eintragen
      meineFaktoren.setSpannung(spannung);
      meineFaktoren.setTemperatur(temperatur);
      meineFaktoren.setProzess(prozess);
      
      //alle Pfade eintragen
      meineBibliothek.pfadEinlesen(pfad_bib);
      meineBibliothek.dateiAuswerten();
      meinSignalListeErzeuger.setPfadSchaltnetzdatei(pfad_schaltnetz);
      signale = meinSignalListeErzeuger.erzeugeSignalliste();
     
      //alle bool-Variablen auf true setzen
      spannung_gesetzt = true;
      temperatur_gesetzt = true;
      prozess_gesetzt = true;
      bibliothekspfad_gesetzt = true;
      schaltnetzpfad_gesetzt = true;   
  }
  
//Diese Methode startet die Analyse
void Menue::analyse() {

     //Starte die Analyse nur, falls zuvor alle benötigten Werte/Pfade eingetragen wurden
     if ( !( spannung_gesetzt && temperatur_gesetzt && prozess_gesetzt 
                && bibliothekspfad_gesetzt && schaltnetzpfad_gesetzt ) ) {
        //ansonsten gebe Fehler aus
        cout << "\nLaufzeitanalyse fehlgeschlagen!\n" << endl;
        cout << "\nErforderliche Werte oder Pfade fuer die Analyse nicht eingetragen?\n" << endl;
        cout << "Falls erforderliche Wert und Pfade eingetragen wurden: " << endl;
        cout << "Angegebene Datei keine Schaltnetzdatei?\n\n" << endl;
        pause();
        return;
      }
        //Setze die für die Analyse benötigten Elemente
        meinGraphErzeuger.setBibliothek(&meineBibliothek);                
        meinGraphErzeuger.setAnzahlSignale(meinSignalListeErzeuger.getAnzahlSignale());
        meinGraphErzeuger.setSignale(signale);    
        meinGraphErzeuger.erzeugeGraph();
        meinLaufzeitAnalysator.setFaktoren(&meineFaktoren);
        meinLaufzeitAnalysator.setStartElement(meinGraphErzeuger.getStartElement());
     //falls nicht alle Elemente korrekt sind
     if( !meinLaufzeitAnalysator.start_LZA() ) {
        //gebe Fehler aus
        cout << endl << "LZA Fehlgeschlagen!" << endl;
     }
    //ansonsten gebe jeweils den längsten Pfad und die maximale Laufzeit im
    //Überführungs bzw. Ausgangsschaltnetz aus
    else {
        cout << "\nLaengster Pfad im Ueberfuehrungsschaltnetz:" << endl; //ABFANGEN!!! Vergleich der berechneten mit der Frequenz aus der SINGALLLISTE!!!
        cout << meinLaufzeitAnalysator.getUebergangspfad() << endl;
        cout << "Maximale Laufzeit der Pfade im Ueberfuehrungsschaltnetz: ";
        cout << meinLaufzeitAnalysator.getLaufzeitUebergangspfad()/1000 << " ps" << endl << endl;
        //erzeuge 50 mal -
        cout << string( 50, '-' ) << endl;
        cout << "Laengster Pfad im Ausgangsschaltnetz:" << endl;
        cout << meinLaufzeitAnalysator.getAusgangspfad() << endl;
        cout << "Maximale Laufzeit der Pfade im Ausgangsschaltnetz: ";
        cout << meinLaufzeitAnalysator.getLaufzeitAusgangspfad()/1000 << " ps" << endl << endl;
        cout << string( 50, '-' ) << endl;


         //abfangen, ob keine FlipFlops im Netz vorhanden sind
         if( !meinLaufzeitAnalysator.flipflopsVorhanden() ){
                cout << "Es sind keine FlipFlops im Schaltnetz vorhanden. " << endl;
                cout << "Schaltnetz ist unabhaengig von der Frequenz!" << endl;
                pause();
                return;

         } else{
                cout << "Maximale Frequenz: " << meinLaufzeitAnalysator.getFrequenz()/1e6 << " MHz\n" << endl;
         }


        // Vergleicht die berechnete maximal zulässige Frequenz mit der Taktfrequenz aus der Schaltnetzdatei
        // Falls die Frequenz aus der Schaltnetzdatei größer als die berechnete ist
        if ( meinLaufzeitAnalysator.getFrequenz() < meinSignalListeErzeuger.getFrequenz() ) {
                //gebe Fehler aus
                cout << "\nBedigung fuer die Taktfrequenz vom Schaltnetz/-werk ist nicht erfuellt!" << endl;
                cout << "Die Taktfrequenz " << meinSignalListeErzeuger.getFrequenz()/1e6 <<" MHz ist groesser als die maximale Frequenz!\n" << endl;
        } else {
                cout << "\n\n Bedingung fuer die Taktfrequenz vom Schaltnetz/-werk ist erfuellt!" << endl;
        }
    }
pause();
}
  
//leert und resetet den Eingabestream
void Menue::clear_cin(){
    cin.clear();
    cin.ignore(255, '\n');
}

//Gibt den Menuekopf aus
void Menue::menueKopf(){
    cout << "******************************************" << endl;
    cout << "*     IT-Projektpraktikum WS2011/2012    *" << endl;
    cout << "* Laufzeitanalyse synchroner Schaltwerke *" << endl;
    cout << "******************************************\n\n" << endl;           
}
