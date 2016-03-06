/* 
 * Datei:  GraphErzeuger.cpp
 * Author: Sebastian Müller
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#include "GraphErzeuger.h"
#include "SignalListeErzeuger.h"
using namespace std;

//Konstruktor: initalisiert Zeiger mit NULL
GraphErzeuger::GraphErzeuger() {
    GraphErzeuger::startElement = NULL;
    GraphErzeuger::endElement = NULL;
    GraphErzeuger::signale = NULL;
    GraphErzeuger::bibliothek = NULL;
}

//Standart Getter und Setter:
Bibliothek* GraphErzeuger::getBibliothek() {
    return GraphErzeuger::bibliothek;
}

void GraphErzeuger::setBibliothek(Bibliothek* bib) {
    GraphErzeuger::bibliothek = bib;
}

ListenElement* GraphErzeuger::getStartElement() {
    return GraphErzeuger::startElement;
}

void GraphErzeuger::setStartElement(ListenElement* element) {
    GraphErzeuger::startElement = element;
}

ListenElement* GraphErzeuger::getEndElement() {
    return GraphErzeuger::endElement;
}

void GraphErzeuger::setEndElement(ListenElement* element) {
    GraphErzeuger::endElement = element;
}

short GraphErzeuger::getAnzahlSignale() {
    return GraphErzeuger::anzahlSignale;
}

void GraphErzeuger::setAnzahlSignale(short signale) {
    GraphErzeuger::anzahlSignale = signale;
}


void GraphErzeuger::setSignale(Signal* sig){
    this->signale = sig;
}

inline Signal* GraphErzeuger::getSignale() {
    return GraphErzeuger::signale;
}

//Neues Element in Liste einfügen
void GraphErzeuger::push_back(ListenElement* elem) {
    //Fall: kein Element in der Liste -> startPointer auf Element
    if(GraphErzeuger::startElement == NULL) {
        GraphErzeuger::startElement = elem;
    }
    //Fall: bereits Element in der Liste -> next-Pointer auf nächstes Element richten
    if(GraphErzeuger::endElement != NULL) {
        GraphErzeuger::endElement->setNextElement(elem);
    }
    //endPointer auf neues Element setzen
    GraphErzeuger::endElement = elem;
    
    //Nächstes Element mit NULL-Pointer initalisieren
    elem->setNextElement(NULL);
}

//Suche Gatter anhand des Namens
SchaltwerkElement* GraphErzeuger::sucheGatter(string gatter) {
    
    //Geht gesamte Liste des Graphen durch
    for(ListenElement * elem = GraphErzeuger::startElement; elem != NULL; elem = elem->getNextElement()) {
        
        //Fall: Zugehöriges Schaltwerkelement heißt wie gesuchtes
        if(elem->getSchaltwerkElement()->getName() == gatter) {
            
            //Gebe Schaltwerkelement-Pointer zurück
            return elem->getSchaltwerkElement();
        }
    }
    //Fall: nichts gefunden
    cout << "Fehler! Gatter nicht in Liste!" << endl;
    return NULL;
}

//Testet, ob ein Signal in ein Gatter führt, wenn es nicht als Ausgang deklariert wurde
bool GraphErzeuger::signalBenutztTest(Signal* sig) {
    
    //Eingang: Muss Ziel haben
    if(sig->getSignalTyp() == Signal::EINGANG && sig->getAnzahlZiele() < 1) {
        return false;
    }
    
    //Internes Signal: muss Quelle und Ziel haben
    else if(sig->getSignalTyp() == Signal::INTERN && (sig->getAnzahlZiele() < 1 || sig->getQuelle() == "")) {
        return false;
    }
    
    //Ausgang: Muss Quelle haben
    else if(sig->getSignalTyp() == Signal::AUSGANG && sig->getQuelle() == "") {
        return false;
    }

    return true;
}

//Testet, ob die Anzahl der Eingangssignale mit der Bibliothek übereinstimmt
bool GraphErzeuger::gatterFehlerTest(SchaltwerkElement* elem) {
    if(elem->getTyp()->getEingaenge() == elem->getAnzahlEingangssignale()) {
        return true;
    }
    else {
        return false;
    }
}

//Erstellt die einfach verkettete Liste mit den bereits bekannten Infos
bool GraphErzeuger::erzeugeListe() {
    
//    Marker für Augsangssignal setzten.
    
    bool thisElemAusg = false;
    
    //Liste neu initalisieren
    GraphErzeuger::setStartElement(NULL);
    GraphErzeuger::setEndElement(NULL);
    
    //Gehe Signalliste durch
    for(int i = 0; i < GraphErzeuger::anzahlSignale; i++) {
        
    
        if(signale[i].getQuelle() != "") {
            
            //Fall Ausgangssignal: Marker setzen
            if(signale[i].getSignalTyp() == Signal::AUSGANG) {
                thisElemAusg = true;
            }
            
            //Listenelement erstellen
            ListenElement* elem = new ListenElement;
            
            GatterTyp* gTyp = bibliothek->getBibElement(signale[i].getQuellenTyp());
            
            //SchaltwerkElement mit ListenElement verknüpfen und bekannte Infos eintragen
            elem->setSchaltwerkElement(new SchaltwerkElement(gTyp));
            elem->getSchaltwerkElement()->setName(signale[i].getQuelle());
            
            //Eingangselement ERSTMAL false setzten (wird später nochmal überprüft)
            elem->getSchaltwerkElement()->setIsEingangsElement(false);
            elem->getSchaltwerkElement()->setIsAusgangsElement(thisElemAusg);
            
            //ListenElement in Liste einfügen
            GraphErzeuger::push_back(elem);
            
            //Ausgangsmarker zurücksetzen
            thisElemAusg = false;
        }
    }
    
    //Eingangsgatter kann erst gesetzt werden, wenn die Liste bereits existiert =(
    for(int i = 0; i < GraphErzeuger::anzahlSignale; i++){
        //Fall Eingangssignal:
        if(signale[i].getSignalTyp() == Signal::EINGANG) {
            
            //Alle Ziele als Eingangselement
            for(int j = 0; j < signale[i].getAnzahlZiele(); j++) {
                sucheGatter((signale[i].getZiel(j)))->setIsEingangsElement(true);
            }
        }
    }
    return true;
}

//Erstellt den Graphen
bool GraphErzeuger::erzeugeGraph() {
    
    //Fehler abfangen
    if(GraphErzeuger::bibliothek == NULL) {
        cout << "Graph: Bibliothek nicht eingebunden!" << endl;
        return false;
    }
    if(GraphErzeuger::signale == NULL) {
        cout << "Graph: Signalliste nicht eingebunden!" << endl;
        return false;
    }
    
    //Liste erzeugen (s.o.)
    if(!erzeugeListe()) {
        return false;
    }
    
    //Gehe alle Signale durch
    for(int i = 0; i<GraphErzeuger::anzahlSignale; i++) {
        
        //Alle Ziele der Signale durchgehen
        for(int j = 0; j < signale[i].getAnzahlZiele(); j++) {
            
            //Gibt es ein Ziel, so erhöhe die Anzahl der Eingänge des Ziels um 1
            if(signale[i].getZiel(j) != "") {
                short signaleAlt = sucheGatter(signale[i].getZiel(j))->getAnzahlEingangssignale();
                sucheGatter(signale[i].getZiel(j))->setAnzahlEingangssignale(signaleAlt + 1);
                
                //Gibt es eine Quelle, so füge alle Ziele als Nachfolger der Quelle hinzu
                if(signale[i].getQuelle() != "") {
                    //Jedes Ziel als Nachfolger hinzufügen
                    sucheGatter(signale[i].getQuelle())->nachfolgerHinzufuegen(sucheGatter(signale[i].getZiel(j)), j);
                }
            }
            
        }
        
    }
    
    //Test auf Unbenutzte Signale und falsch beschaltetete Gatter
    
    //Signalliste erneut durchgehen
    for(int i = 0; i<GraphErzeuger::anzahlSignale; i++) {
        
        //s.o.
        if(!signalBenutztTest(&signale[i])) {
            cout << endl << "Fehler!";
            cout << endl << "Unbenutztes Signal!" << endl;
            return false;
        }
        
        //Quellgatter des Signals überprüfen, falls existent (s.o.)
        if(signale[i].getQuelle() != "" && !gatterFehlerTest(sucheGatter(signale[i].getQuelle()))) {
            cout << endl << "Fehler!";
            cout << endl << sucheGatter(signale[i].getQuelle())->getName() << " hat zu viele / zu wenige Eingangssignale!" << endl;
            return false;
        }
    }
    return true;
}

//Ausgabefunktion für die Konsole
void GraphErzeuger::ausgabeGraph(){
    cout << endl;
    
    //Gehe Liste durch und gebe die Infos aus
    for(ListenElement* elem = getStartElement(); elem != NULL; elem = elem->getNextElement()) {
        cout << "Gatterame: " << elem->getSchaltwerkElement()->getName() << endl;
        cout << "Gattertyp: " << elem->getSchaltwerkElement()->getTyp()->getName() << endl;
        cout << "-->Das Gatter hat " << elem->getSchaltwerkElement()->getAnzahlNachfolger() << " Ziele" << endl;
        cout << "Angeschlossene Gatter : ";
        for(int i = 0; i < elem->getSchaltwerkElement()->getAnzahlNachfolger(); i++) {
            cout << elem->getSchaltwerkElement()->getNachfolger(i)->getName() << " ";
        }
        cout << endl << "--------------------------------" << endl;
    }

}