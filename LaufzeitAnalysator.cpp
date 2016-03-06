
/*
 * Datei:  LaufzeitAnalysator.cpp
 * Author: Kristian Maier
 *
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#include "LaufzeitAnalysator.h"

using namespace std;


LaufzeitAnalysator::LaufzeitAnalysator(){
    faktoren = NULL;
    startElement = NULL;
    frequenz = 0;
    uebergangspfad = "";
    ausgangspfad = "";
    laufzeitUebergangspfad = 0;
    laufzeitAusgangspfad = 0;
}

void LaufzeitAnalysator::setFaktoren(Faktoren* fak){
    this->faktoren = fak;
}

void LaufzeitAnalysator::setStartElement(ListenElement* start){
    this->startElement = start;
}


long LaufzeitAnalysator::getFrequenz(){
    return this->frequenz;
}

string LaufzeitAnalysator::getUebergangspfad(){
    return this->uebergangspfad;
}

string LaufzeitAnalysator::getAusgangspfad(){
    return this->ausgangspfad;
}

double LaufzeitAnalysator::getLaufzeitUebergangspfad(){
    return this->laufzeitUebergangspfad;
}

double LaufzeitAnalysator::getLaufzeitAusgangspfad(){
    return this->laufzeitAusgangspfad;
}

/*
 * Startet die Laufzeitanalyse des Schaltwerks. Dazu muss vorher das Start-
 * element und die Faktoren gesetzt sein.
 */
bool LaufzeitAnalysator::start_LZA(){
    //eventuell alte Berechnungen zuruecksetzen
    uebergangspfad = "";
    ausgangspfad = "";
    laufzeitUebergangspfad = 0;
    laufzeitAusgangspfad = 0;
    frequenz = 0;
    
    berechneLaufzeitEinzelgatter();
        
    //fuer alle gueltigen Startknoten(Eingangsgatter oder FF) die Tiefensuche aufrufen
    SchaltwerkElement* sE;
    for(ListenElement* k = startElement; k->getNextElement() != NULL; k = k->getNextElement()){
        sE = k->getSchaltwerkElement();
        if(sE->getIsEingangsElement() || sE->getTyp()->getIsFlipflop()){
            if(!dfs(k)) { //Tiefensuche aufrufen
                return false;
            }
        }
    }
    return true;
}


/*
 * Tiefensuche vorbereiten und durchfuehren
 */
bool LaufzeitAnalysator::dfs(ListenElement* start){
     
    //alte Analysen verwerfen
    DFS_Zwischenspeicher.clear();
    
    //alle Knoten = SchaltwerkElemente in der Map initialisieren mit 0
    SchaltwerkElement* sE;
    for(ListenElement* k = this->startElement; k->getNextElement() != NULL; k = k->getNextElement()){        
        sE = k->getSchaltwerkElement();
        DFS_Zwischenspeicher[sE].pfadLaufzeit = 0;
        DFS_Zwischenspeicher[sE].vaterElement = NULL;
    }
    
    sE = start->getSchaltwerkElement();
    //Tiefensuche durchfuehren
    if(!dfs_visit(sE,sE, "")) {
        return false;
    }
    
    return true;
}


//Zyklensuche: Überprüft, ob die Folgeknoten des übergebenen Knoten bereits entdeckt wurden
bool LaufzeitAnalysator::zyklensuche(SchaltwerkElement* v) {
    
//    Vorherige Version:
//    if(LaufzeitAnalysator::DFS_Zwischenspeicher[v].pfadLaufzeit > 0) {
//        return true;
//    }
    
    //Fall: Betrachteter Knoten hat überhaupt Nachfolger
    if(v->getAnzahlNachfolger() > 0) {
        
        //Gehe alle Nachfolger durch...
        for(int i = 0; i < v->getAnzahlNachfolger(); i++) {
            
            //...und Prüfe, ob schon eine Pfadlaufzeit für diese gesetzt wurde (=schon entdeckt)
            if(LaufzeitAnalysator::DFS_Zwischenspeicher[v->getNachfolger(i)].pfadLaufzeit > 0) {
                cout << endl << "Fehler! Zyklus an " << v->getNachfolger(i)->getName() << " gefunden!" << endl;
                return true;
            }
            //return zyklensuche(v->getNachfolger(i));
        }
    }
    return false;
}


/*
 * Fuehrt die Tiefensuche durch, verwendet den vorgegeben Pseudo-Code
 */
bool LaufzeitAnalysator::dfs_visit(SchaltwerkElement* k, SchaltwerkElement* s, string pfad){
    SchaltwerkElement* v;
    double tempZeit;
    
    //verfolgter Pfad speichern
    pfad += "->" + k->getName();
    
    //alle Nachfolger iterieren
    for(int i = 0; i < k->getAnzahlNachfolger(); i++){
        v = k->getNachfolger(i);
        tempZeit = DFS_Zwischenspeicher[k].pfadLaufzeit + k->getLaufzeitEinzelgatter();
        
        //wenn Flipflop ist Endelement des Uebergangpfades gefunden
        if(v->getTyp()->getIsFlipflop()){            
            //wenn neue Laufzeit groesser, neue Maximale Laufzeit setzen
            if(laufzeitUebergangspfad < tempZeit){
                laufzeitUebergangspfad = tempZeit;
                uebergangspfad = pfad + "->" + v->getName();    //Pfadstring der groessten Laufzeit speichern
                Flipflop* ff = (Flipflop*)(v->getTyp());        //Referenz auf den FlipFloptyp
                //berechne Frequenz in Hz
                frequenz = (long) ( 1e15 / ( laufzeitUebergangspfad + 1000 * ff->getSetupTime()) );              
            } 
        //sonst wenn moeglicher laengerer Pfad
        }else if(DFS_Zwischenspeicher[v].pfadLaufzeit < tempZeit){
            //möglicher Zyklus pruefen
            if(((DFS_Zwischenspeicher[v].pfadLaufzeit != 0) || (v == s)) && 
                    DFS_Zwischenspeicher[v].vaterElement != k){
                
                    DFS_Zwischenspeicher[v].vaterElement = k;
                    if(zyklensuche(v)){
                        return false;
                    }
            }
            //setzen der Werte des Folgeknotens und rekursiver Aufruf der dfs
            tempZeit = DFS_Zwischenspeicher[k].pfadLaufzeit + k->getLaufzeitEinzelgatter();
            DFS_Zwischenspeicher[v].pfadLaufzeit = tempZeit;
            DFS_Zwischenspeicher[v].vaterElement = k;
            if(!dfs_visit(v, s, pfad)){
                //wenn Zyklus gefunden
                return false;
            }
            
        }
    }
    
    tempZeit = DFS_Zwischenspeicher[k].pfadLaufzeit + k->getLaufzeitEinzelgatter();
    
    //wenn Knoten mit Ausgang verbunden ist, ist neuer Ausgangspfad gefunden
    if(k->getIsAusgangsElement() && laufzeitAusgangspfad < tempZeit){
        laufzeitAusgangspfad = tempZeit;
        ausgangspfad = pfad;
    }
    
    return true;
    
}







/*
 * Berechnet die Laufzeit der Einzelgatter und speichert sie im 
 * SchaltwerkElement ab
 */
void LaufzeitAnalysator::berechneLaufzeitEinzelgatter(){
    ListenElement* li = startElement;
    SchaltwerkElement* sE;
    double laufzeitEinzelgatter;
    double spg, temp, prozess;
    double lastKapazitaet;
    GatterTyp typ;
    
    //Faktoren Spannung, Temperatur, Prozess holen
    faktoren->getFaktoren(spg, temp, prozess);
    
    //alle Elemente durchgehen
    while(li->getNextElement() != NULL){
        sE = li->getSchaltwerkElement();
        typ = *(sE->getTyp());
        
        //Lastkapazitaeten der Zielelmente aufaddieren
        lastKapazitaet=0;
        for(int i=0; i < sE->getAnzahlNachfolger(); i++){
            lastKapazitaet += sE->getNachfolger(i)->getTyp()->getLastKapazitaet();
        }
        
        //Laufzeit berechnen
        laufzeitEinzelgatter = typ.getGrundLaufzeit() * 1000;   //*1000 wegen Einheit, piko in femto
        laufzeitEinzelgatter += typ.getLastFaktor() * lastKapazitaet;
        laufzeitEinzelgatter *= spg * temp * prozess;
        //Laufzeit im SchaltwerkElement speichern
        li->getSchaltwerkElement()->setLaufzeitEinzelgatter(laufzeitEinzelgatter);
        //Pointer aufs nächste Element setzen
        li = li->getNextElement();
    }
}


/*
 * Gibt zurueck, ob in dem Graphen mindestens 1 FlipFlops vorhanden ist.
 */
bool LaufzeitAnalysator::flipflopsVorhanden(){
    ListenElement* element = startElement;
    //alle ELemente durchgehen
    while(element->getNextElement() != NULL){
        if(element->getSchaltwerkElement()->getTyp()->getIsFlipflop()){
            return true;
        }
        element = element->getNextElement();
    }
    
    return false;
}