/* 
 * Datei:  ListenElement.h
 * Author: Sebastian Müller
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#ifndef LISTENELEMENT_H
#define	LISTENELEMENT_H

#include "SchaltwerkElement.h"

using namespace std;

class ListenElement {
private:
    SchaltwerkElement* schaltwerkElement;
    ListenElement* next;
public:
    ListenElement();
    ~ListenElement();
    SchaltwerkElement* getSchaltwerkElement();
    ListenElement* getNextElement();
    void setSchaltwerkElement(SchaltwerkElement* schaltwerkEl);
    void setNextElement(ListenElement* nextEl);
};

#endif	/* LISTENELEMENT_H */

