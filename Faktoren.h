/* 
 * Datei:  Faktoren.h
 * Author: Sebastian Müller
 * 
 * IT Praktikum WS 2012/13
 * Gruppe 57
 */

#ifndef FAKTOREN_H
#define	FAKTOREN_H

using namespace std;

class Faktoren {

private:
    double spannung;
    double temperatur;
    short prozess;
    double spannungFaktor;
    double temperaturFaktor;
    double prozessFaktor;

    bool berechneSpannungFaktor();
    bool berechneTemperaturFaktor();
    bool berechneProzessFaktor();
    double berechneFaktor(double wert, double arr[][2], int laenge);            
    double interpolation(double wert, double x1, double x2, double y1, double y2);

public:
    Faktoren();
    ~Faktoren();

    double getSpannung() const;
    double getTemperatur() const;
    short getProzess() const;
    void getFaktoren(double& spgFaktor, double& tmpFaktor, double& przFaktor) const;
    bool setSpannung(double spannung);
    bool setTemperatur(double temperatur);
    bool setProzess(short prozess);
    void ausgabeFaktoren();

};

#endif	/* FAKTOREN_H */

