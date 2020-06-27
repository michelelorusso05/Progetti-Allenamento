#pragma once

#include <iostream>

using namespace std;

class tartagliaTriangle
{
public:

	void printTriangle(ostream& stream);
	//Stampa: il triangolo di Tartaglia fino alla riga selezionata.

	void setRowsToPrint(int rows);
	//Metodo: SET di (int)rowsToPrint

	int getRowsToPrint();
	//Metodo: GET di (int)rowsToPrint

	tartagliaTriangle();
	//Costruttore: default

	tartagliaTriangle(int rows);
	//Costruttore: assegna un valore a (int)rowsToPrint alla creazione della classe.

	~tartagliaTriangle();
	//Distruttore: libera le zone di memoria a cui fanno riferimento i puntatori usati dalla classe.

	int* calculateNextFloor(int startArray[], int lenOfStartArray);
	//Ritorna: un puntatore che ha come bersaglio l'array contenente il piano successivo del triangolo.

	void printRow(ostream& stream, int arrayToPrint[], int len);
	//Stampa: l'array "piano" attuale.

	int rowsToPrint;
	//Intero che indica fino a che piano (potenza N di binomio) bisogna stampare.


};

