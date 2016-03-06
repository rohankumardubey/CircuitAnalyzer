/* 
 * Datei:  ListenElement.cpp
 * Author: Sebastian Müller
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#include "ListenElement.h"
#include "SchaltwerkElement.h"
#include <iostream>
using namespace std;



//Tut nichts.
ListenElement::~ListenElement() { }

//Getter
SchaltwerkElement* ListenElement::getSchaltwerkElement() {
    return ListenElement::schaltwerkElement;
}

ListenElement* ListenElement::getNextElement() {
    return ListenElement::next;
}

void ListenElement::setSchaltwerkElement(SchaltwerkElement* schaltwerkEl) {
    ListenElement::schaltwerkElement = schaltwerkEl;
}

void ListenElement::setNextElement(ListenElement* nextEl) {
    ListenElement::next = nextEl;
}

//Setzt alle Zeiger auf NULL
ListenElement::ListenElement() {
    ListenElement::setSchaltwerkElement(NULL);
    ListenElement::setNextElement(NULL);
}