/* 
 * Datei:   main.cpp
 * Author: Sebastian Müller, Kristian Maier, Maxim Köhler, Florian König
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */


#include <iostream>
#include "Bibliothek.h"
#include "Faktoren.h"
#include "Flipflop.h"
#include "GatterTyp.h"
#include "LaufzeitAnalysator.h"
#include "ListenElement.h"
#include "SchaltwerkElement.h"
#include "Signal.h"
#include "SignalListeErzeuger.h"
#include "Menue.h"

using namespace std;

//void maxim_testing(){
//    Bibliothek bib;
//    bib.pfadEinlesen();
//    bib.dateiAusgabe();
//    bib.dateiAuswerten();
//    GatterTyp* tempGatter;
//    cout << endl;
//    string title[9] = {"inv1a", "inv1b", "inv1c", "and2", "or2", "nand2", "nor2", "xor2", "xnor2"};
//    for( int i = 0; i < 9; i++) {
//        tempGatter = bib.getBibElement(title[i]);
//        tempGatter->out();
//    }
//    tempGatter = bib.getBibElement("dff");
//    dynamic_cast<Flipflop*>(tempGatter)->out();
//    string moin;
//    cin >> moin;
//}

void signal_testing(){
    SignalListeErzeuger s;
    cout << "Pfad zur Schaltnetzdatei:" << endl;
    string buf;
    getline(cin, buf);    
    
    if(s.setPfadSchaltnetzdatei(buf)) {      
        s.ausgabeSchaltnetzdatei();  
        Signal* sig = s.erzeugeSignalliste();
        if(sig != NULL){
            s.ausgabeSignale();
        }
   }else{
        cout << "Falscher Pfad" << endl;    
   }    
}

void faktoren_testing() {
    double kv, kt, kp, sp, tm, pr;
    Faktoren faktoren;
    cout << "Spannung? ";
    cin >> sp;
    cout << "Temperatur? ";
    cin >> tm;
    cout << "Prozess? ";
    cin >> pr;
    faktoren.setProzess(pr);
    cout << "setProzess() ausgefuehrt." << endl;
    faktoren.setSpannung(sp);
    cout << "setSpannung() ausgefuehrt" << endl;
    faktoren.setTemperatur(tm);
    cout << "setTemperatur() ausgefuehrt." << endl;
    cout << "getProzess() ausgefuehrt: " << faktoren.getProzess() << endl;
    cout << "getSpannung() ausgefuehrt: " << faktoren.getSpannung() << endl;
    cout << "getTemperatur() ausgefuehrt: " << faktoren.getTemperatur() << endl;
    cout << "ausgabeFaktoren() wird jetzt ausgefuehrt:" << endl;
    faktoren.ausgabeFaktoren();
    faktoren.getFaktoren(kv, kt, kp);
    cout << "getFaktoren() Ergebnis: KV=" << kv << " , KT=" << kt << " , KP=" << kp << endl;
}

void menue_testing() {
    Menue menue;
    menue.start();
}

//void graph_testing() {
//    
//    GraphErzeuger graph;
//    Bibliothek bib;
//    bib.pfadEinlesen();
//    bib.dateiAuswerten();
//    graph.setBibliothek(&bib);
//    
//    SignalListeErzeuger s;
//    cout << "Pfad zur Schaltnetzdatei:" << endl;
//    string buf;
//    cin >> buf;
//    bool ok;
//    ok = s.setPfadSchaltnetzdatei(buf);
//    if(!ok){
//        cout << "Falscher Pfad" << endl;
//    }
//    Signal* sig = s.erzeugeSignalliste();
//    graph.setAnzahlSignale(s.getAnzahlSignale());
//    graph.setSignale(sig);
//    
//    graph.erzeugeGraph();
//    graph.ausgabeGraph();
//    cout << endl;
//    for(ListenElement* elem = graph.getStartElement(); elem != NULL; elem = elem->getNextElement()) {
//        cout << "Gatterame: " << elem->getSchaltwerkElement()->getName() << endl;
//        cout << "Eingangssignale: " << elem->getSchaltwerkElement()->getAnzahlEingangssignale() << endl;
//        cout << "Ist Ausgang: " << elem->getSchaltwerkElement()->getIsAusgangsElement() << endl;
////        cout << "Ist Eingang: " << elem->getSchaltwerkElement()->getIsEingangsElement() << endl;
////        cout << "Gattertyp: " << elem->getSchaltwerkElement()->getTyp()->getName() << endl;
////        cout << "Ziele:" << endl;
////        for(int i = 0; i < elem->getSchaltwerkElement()->getAnzahlNachfolger(); i++) {
////            cout << elem->getSchaltwerkElement()->getNachfolger(i)->getName() << endl;
////        }
////        cout << "--------------------------------" << endl;
////    }
//    
//    
//}
//
////void LZA_testing(){
//    GraphErzeuger graph;
//    Bibliothek bib;
//    bib.pfadEinlesen();
//    bib.dateiAuswerten();
//    graph.setBibliothek(&bib);
//    
//    SignalListeErzeuger s;
//    cout << "Pfad zur Schaltnetzdatei:" << endl;
//    string buf;
//    cin >> buf;
//    bool ok;
//    ok = s.setPfadSchaltnetzdatei(buf);
//    if(!ok){
//        cout << "Falscher Pfad" << endl;
//    }
//    Signal* sig = s.erzeugeSignalliste();
//    graph.setAnzahlSignale(s.getAnzahlSignale());
//    graph.setSignale(sig);    
//    graph.erzeugeGraph();
//    graph.ausgabeGraph();
//    
//    double sp, tm, pr;
//    Faktoren faktoren;
//    cout << "Spannung? ";
//    cin >> sp;
//    cout << "Temperatur? ";
//    cin >> tm;
//    cout << "Prozess? ";
//    cin >> pr;
//    faktoren.setProzess(pr);
//    faktoren.setSpannung(sp);
//    faktoren.setTemperatur(tm);
//    
//    LaufzeitAnalysator lza;
//    lza.setFaktoren(&faktoren);
//    lza.setStartElement(graph.getStartElement());
//    lza.start_LZA();
//}

int main() {
     
    Menue menue;
    menue.start();
    //kristian_testing();
    //signal_testing();
    //faktoren_testing();
    //maxim_testing();
    //graph_testing();
    //LZA_testing();
    return 0;
}

