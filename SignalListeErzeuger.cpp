/* 
 * Datei:  SignalListeErzeuger.cpp
 * Author: Kristian Maier
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#include "SignalListeErzeuger.h"

using namespace std;

void SignalListeErzeuger::setFrequenz(long frequenz){
    this->frequenz = frequenz;
}


short SignalListeErzeuger::getAnzahlSignale() const{
    return this->anzahlSignale;
}


string SignalListeErzeuger::getPfadSchaltnetzdatei() const{
    return this->datei;
}


long SignalListeErzeuger::getFrequenz() const{
    return this->frequenz;
}


/*
 * Gibt den String von Anfang von str bis zum ersten Auftreten von chr zurueck.
 * Gibt es kein chr, wird alles zurueckgegeben
 */
string SignalListeErzeuger::readUntilChar(string& str, char chr) const{
    stringstream ss(str);
    string tmp;
    getline(ss, tmp, chr);  
    return tmp;
}


/*
 * Loescht innerhalb von str alles bis zum ersten Auftreten von chr 
 * inklusive chr. Gibt es dies nicht, wird alles geloescht.
 * 
 */
void SignalListeErzeuger::eraseUntilChar(string& str, char chr){
    stringstream ss(str);
    string tmp;
    getline(ss, tmp, chr);  
    str.erase(0, tmp.length() + 1);
}


/*
 * Loescht im string str alles hinter dem ersten vorkommenden Zeichen 
 * chr inklusive dem Zeichen.
 * 
 */
void SignalListeErzeuger::eraseAfterChar(string& str, char chr){
    stringstream ss(str);
    getline(ss, str, chr);    
}


/*
 * Öffnet die Datei wenn dies moeglich ist, sonst wird der Pfad 
 * nicht gespeichert. Der Rueckgabetyp gibt an, ob das oeffnen der Datei 
 * erfolgreich war.
 */
bool SignalListeErzeuger::setPfadSchaltnetzdatei(string pfad){
    ifstream file (pfad.c_str(), ios::in);
    if(file){
        datei = pfad;
        file.close();
        return true;
    }
    return false;
    
}

/*
 * Erzeugt die Signalliste und gibt sie als Zeiger auf ein dynamisches Array 
 * zurueck. Dazu wird die Schaltnetzdatei geoeffnet und ausgelesen. Ist
 * dies nicht moeglich, wird der Nullzeiger zurückgegeben und die Listen-
 * laenge betraegt den Wert 0. Eine entsprechende Fehlermeldung wird ausgegeben.
 *  
 * Die Laenge der Liste kann über getAnzahlSignale() abgerufen werden. 
 */
Signal* SignalListeErzeuger::erzeugeSignalliste(){
  
    if(signale != NULL){
       delete[] signale;
       signale = NULL;
    }
    anzahlSignale = 0;
    
    
    //Exceptions abfangen, falls die Schaltnetzdatei nicht ausgelesen werden 
    //kann, weil sie z.B. fehlerhaft ist.
    try{
        string input, output, intern, clock;
        //die Signalaufzaehlung auslesen
        readEntity(input, output, intern, clock);
        //Signale zaehlen
        anzahlSignale = countSignals(input, output, intern);
        //dynamisches Array erzeugen
        signale = new Signal[anzahlSignale];
        //Frequenz auslesen
        frequenz = readFrequenz(clock);
        //Signalliste erzeugen und den Signaltyp zuweisen
        fillList(input, output, intern);        
        
        //Gatter bestimmen, welche durch die Signale verknuepft 
        //sind und Kurzschluss auswerten
        if(readGatterInfo()){
            cout << "Kurzschluss im Schaltnetz entdeckt" << endl;
            return NULL;
        }
        
    }catch(...){
       //Ausgabe einer Fehlermeldung bei Fehler
        anzahlSignale = 0;
        ausgabeReadError(); 
        if(signale != NULL){
            signale = NULL;
            delete[] signale;
        }
        return NULL;       
    }
        
    return signale;
}

/*
 * Liest den Entity Teil der Schaltnetzdatei und speichert die Signale 
 * in den entsprechenden Referenzen.
 */
void SignalListeErzeuger::readEntity(string& input, string& output, 
                                     string& intern, string& clock){
    
        
    ifstream file (datei.c_str(), ios::in);
    
    //auf Fehler beim oeffnen testen
    if(!file){
        ausgabeOpenError();
        return;       
    } 
    
    string line;
    int count = 0;
    while(getline(file, line)){
        if(line.find("INPUT") == 0){
                input = line;
                //"INPUT" am Anfang entfernen
                eraseUntilChar(input, ' ');
                //Semikolon am Ende entfernen
                eraseAfterChar(input, ';');
                count++;
        }else if(line.find("OUTPUT") == 0){
                output = line;
                eraseUntilChar(output, ' ');
                eraseAfterChar(output, ';');
                count++;
        }else if(line.find("SIGNALS") == 0){
                intern = line;
                eraseUntilChar(intern, ' ');
                eraseAfterChar(intern, ';');
                count++;
        }else if(line.find("CLOCK") == 0){
                clock = line;
                eraseUntilChar(clock, ' ');
                eraseAfterChar(clock, ';');
                count++;
         }
        if(count == 4){
            file.close();
            return;
        }
    }
    file.close();
    //Fehler ausloesen, falls ENTITY Kopf nicht ausgelesen werden konnte
    throw 1;        
 }


/*
 * Liefert die Anzahl der Signale zurueck, die in input, output, und intern
 * definiert sind, indem alle Zeichen zusammengezaehlt werden und durch die
 * Anzahl der Zeichen (=5) geteilt wird,  die ein Signal zur Beschreibung 
 * braucht.
 * 
 */
int SignalListeErzeuger::countSignals(string& input,string& output,string& intern){
    return (input.length() + output.length() + intern.length() + 3)/5;
    
}

/*
 * Weißt ihnen den Signalen den richtigen Signal Typ zu, aber noch nicht Ziele 
 * und Quelle. Die Position im Array entspricht dabei der Signalnummer und kann 
 * so weiter eindeutig zugeordnet bleiben.
 */
void SignalListeErzeuger::fillList(string input, string output, string intern){
    
    //Alle zu erzeugende Signale durchgehen
    for(int i = 0; i < anzahlSignale; i++){      
       //Den Typ des Signals ermitteln, indem der Index mit der Liste, die durch
       //input, output und intern gegeben ist, verglichen wird. Die Signale mit
       //der niedrigsten Nummer stehen immer vorne in der Liste.
       if(i+1 == extractSignal(input)){
           signale[i].setSignalTyp(Signal::EINGANG); 
           //gespeichertes Signal aus Liste loeschen   
           eraseUntilChar(input, ',');          
       }
       else if(i+1 == extractSignal(output)){
           signale[i].setSignalTyp(Signal::AUSGANG);        
           //gespeichertes Signal aus Liste loeschen
           eraseUntilChar(output, ',');   
           
       }
       else if(i+1 == extractSignal(intern)){
           signale[i].setSignalTyp(Signal::INTERN);   
           //gespeichertes Signal aus Liste loeschen
           eraseUntilChar(intern, ',');    //gespeichertes Signal aus Liste loeschen
           
       }
    }
    
}
    

/*
 * Liest den Teil zwischen BEGIN und END aus, um die Gatter zu bestimmen
 * welche durch die Signale verknuepft sind. Gibt außerdem true zurueck,
 * wenn Kurzschluesse erkannt wurden, sonst false;
 */
bool SignalListeErzeuger::readGatterInfo(){
        
    ifstream file (datei.c_str(), ios::in);
    
    //auf Fehler beim oeffnen testen
    if(!file){
        return false;       
    } 
    
    string line;
    //nach Finden von "BEGIN" in der Datei wird gatterInfo = true und die 
    //folgenden Zeilen sind die Signalbeziehungen zu den Gattern bis "END"
    bool gatterInfo = false;
    while(getline(file, line)){
        if(!gatterInfo  && (line.find("BEGIN") == 0)){            
            gatterInfo=true;
            continue;
        }
        if(gatterInfo  && (line.find("END") == 0)){
            break;
        }
        if(gatterInfo){
            //Eine Zeile verarbeiten
            //wenn Rueckgabe true ist, wurde ein Kurzschluss gefunden
            if(updateSignallisteMitGatter(line)){
                return true;
            }
           
        }        
    }    
    file.close();
    return false;
}

/*
 * Liest die Informationen aus einer Zeile des Teils zwischen BEGIN und END
 * und speichert diese innerhalb der Signalliste ab. Erkennt außerdem Kurz-
 * schluesse im Schaltwerk und gibt true zurueck, wenn einer gefunden wurde.
 */
bool SignalListeErzeuger::updateSignallisteMitGatter(string& line){
    string gatterName;
    //Gattername steht am Anfang                
    gatterName = readUntilChar(line, ':');      //line=g003:dff(s024,clk,s043);
    //Nach Auslesen loeschen
    eraseUntilChar(line, ':');                  //line=dff(s024,clk,s043);
    
    string gatterTyp;
    //Gattertyp steht jetzt am Anfang
    gatterTyp = readUntilChar(line, '(');       
    eraseUntilChar(line, '(');                  //line=s024,clk,s043);
    
    line = readUntilChar(line, ')');            //line = s024,clk,s043
    //hinteres Komma raussuchen, rechts davon steht das Ausgangssignal des Gatters
    unsigned long letztesKomma = line.find_last_of(',', string::npos);
    string ausgangssignal = line.substr(letztesKomma+1, string::npos);
    //int wert des Signals bestimmen
    int intAusgangssignal = extractSignal(ausgangssignal);      
        
    //Referenz auf Ausgangssignal besorgen
    Signal& sig = signale[intAusgangssignal-1];
    
    if((sig.getQuelle() != "") || (sig.getSignalTyp() == Signal::EINGANG)){
        //Kurzschluss wenn Signal schon Quelle hat oder
        //externer Eingang auf interner Ausgang
        return true;
    }   
    sig.setQuelle(gatterName);
    sig.setQuellenTyp(gatterTyp);
    
    line = line.substr(0,letztesKomma);         //line = s024,clk
    
    //Mehrere verbleibende Eingangssignale nacheinander einschreiben
    while(!line.empty()){
        string eingangssignal;
        eingangssignal = readUntilChar(line,',');        
        eraseUntilChar(line, ',');               //line = clk
        if(eingangssignal == "clk"){
            //clk kann ignoriert werden
           continue;
        }
        int intEingangssignal = extractSignal(eingangssignal);
        
        //Referenz auf Eingangssignal besorgen
        Signal& sig = signale[intEingangssignal-1];
        //Ziel Gatter im Signal speichern
        sig.zielHinzufuegen(gatterName, sig.getAnzahlZiele());
    }
       
    return false;
    
}

/*
 * Im uebergebenen String befinden sich die durch Komma getrennten Signale.
 * Das erste Signal wird dabei in ein int Wert gewandelt.
 */
int SignalListeErzeuger::extractSignal(string& str){         
    string number;
    number = readUntilChar(str, ',');
    number.erase(0,1);
    stringstream ss(number);
    int num;
    ss >> num;
    return num;
}

/*
 * Gibt die Frequenz zurueck, die in der CLOCK Zeile angegeben war und
 * mit clock uebergeben wurde.
 */
long SignalListeErzeuger::readFrequenz(string& clock){
    stringstream ss(clock);
    string tmp;
    long freq;
    
    //clock hat jetzt das zB. Format "clk, ZZZZ MHz"
    
    //clk, abschneiden:
    getline(ss, tmp, ',');      //tmp="clk" 
    
    ss >> freq;                 //freq = ZZZZ
    ss >> tmp;                  //tmp = MHz   
      
    if(tmp.compare("MHz") == 0){
        freq*=1000000L;
    }else if(tmp.compare("kHz") == 0){        
        freq*=1000L;
    }//sonst in Hz
    return freq;
}

/*
 * Gibt die komplette Schaltnetzdatei auf der Konsole aus. Dazu wird die 
 * Schaltnetzdatei geoeffnet und ausgelesen. Ist dies nicht moeglich,
 * wird eine entsprechende Fehlermeldung ausgegeben.
 */
void SignalListeErzeuger::ausgabeSchaltnetzdatei(){
    ifstream file (datei.c_str(), ios::in);
    
    if(!file){
        ausgabeOpenError();
        return;       
    } 
    
    int i=1;
    string line;
    //Datei zeilenweise ausgeben mit Zeilennummern
    while(getline(file, line)){
        cout << "#" << i << ": " << line << endl;
        i++;
    }
        
    file.close();
    
}

/*
 * Gibt die Signalliste auf der Konsole aus. Dazu muss vorher die Liste 
 * ueber erzeugeSignalliste() erfolgreich erzeugt werden. 
 */
void SignalListeErzeuger::ausgabeSignale(){
    
    if(anzahlSignale == 0){        
        cout << "Keine Signale vorhanden" << endl;
        return;
    }
    
    cout << "Signale:" << endl;
    
    for(int i=0; i < anzahlSignale; i++){  
        //Ausgabe Trennstriche
        cout << "-----" << endl;
        
        //Ausgabe Signalname
        cout << "Signalname : s";
        if(i+1 < 10){
            cout << "00";
        }else if(i+1 < 100){
            cout << "0";
        }
        cout << i+1 << endl;
        
        //Ausgabe Signaltyp        
        cout << "Signaltyp : ";
        switch(signale[i].getSignalTyp()){
            case Signal::AUSGANG:
                cout << "Ausgangssignal";
                break;
            case Signal::EINGANG:
                cout << "Eingangssignal";
                break;
            case Signal::INTERN:
                cout << "Internes Signal";
                break;
            default:
                cout << "unbekanntes Signal";
                break;
        }
        cout << endl;
        
        
        //Ausgabe der Signalquelle wenn vorhanden
        cout << "Signalquelle : ";
        if(signale[i].getSignalTyp() == Signal::EINGANG){
            cout << "keine Quelle" << endl;
        }else{
            cout << signale[i].getQuelle() << endl;
        }
        
        
        int ziele = signale[i].getAnzahlZiele();
        cout << "--> Das Signal hat " << ziele;
        cout << " Ziele" << endl;        
        
        if(ziele > 0){
            cout << "Ziel-Gatter :";
            while(ziele){
                cout << " " << signale[i].getZiel(ziele-1);
                ziele--;
            }
            cout << endl;
        }
        
        
    }
}

/*
 * Gibt eine Fehlermeldung aus, wenn die Schaltnetzdatei nicht 
 * geoeffnet werden konnte;
 */
void SignalListeErzeuger::ausgabeOpenError(){
    cout << "Fehler beim Oeffnen der Schaltnetzdatei"  << endl;
    cout << "Pfad richtig oder Datei schon geoeffnet?" << endl;
}

/*
 * Gibt eine Fehlermeldung aus, wenn die Schaltnetzdatei nicht 
 * ausgelesen werden konnte;
 */
void SignalListeErzeuger::ausgabeReadError(){
    cout << "Fehler beim Lesen der Schaltnetzdatei"  << endl;
    cout << "Datei korrekt?" << endl;
}