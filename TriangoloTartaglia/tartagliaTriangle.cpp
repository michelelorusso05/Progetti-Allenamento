#include "tartagliaTriangle.h"

//Metodi pubblici

void tartagliaTriangle::printTriangle(ostream& stream)
{
	int *firstArray;
	int *nextArray;

	nextArray = new int[1] {1};

	for (int i = 0; i < rowsToPrint; i++)
	{
		//Spaziatura dal margine della finestra
		stream << "    "; 

		//Stampa gli spazi
		for (int j = 0; j < rowsToPrint - i; j++)
		{
			stream << " ";
		}
		
		firstArray = nextArray;

		tartagliaTriangle::printRow(stream, firstArray, i + 1);

		nextArray = calculateNextFloor(firstArray, i + 1);

		delete[] firstArray;

	}

	delete[] nextArray;
	stream << endl;
}

void tartagliaTriangle::setRowsToPrint(int rows)
{
	tartagliaTriangle::rowsToPrint = rows;
}

int tartagliaTriangle::getRowsToPrint()
{
	return tartagliaTriangle::rowsToPrint;
}

tartagliaTriangle::tartagliaTriangle()
{
	tartagliaTriangle::rowsToPrint = 0;
}

tartagliaTriangle::tartagliaTriangle(int rows)
{
	tartagliaTriangle::rowsToPrint = rows;
}

tartagliaTriangle::~tartagliaTriangle()
{

}

//Metodi privati

int* tartagliaTriangle::calculateNextFloor(int startArray[], int lenOfStartArray)
{
	int* p;

	if (lenOfStartArray == 1)
		p = new int[2]{ 1, 1 };

	else
	{
		p = new int[lenOfStartArray + 1];
		// Nel triangolo di Tartaglia, a ogni piano il primo e l'ultimo numero equivalgono a 1
		p[0] = 1; 

		for (int i = 1; i < lenOfStartArray; i++)
		{
			//Linea esempio: startArray = { 1, 3, 3, 1 }
			//Risultato: p = { 1, 4, 6, 4, 1 }
			p[i] = startArray[i-1] + startArray[i];
		}

		p[lenOfStartArray] = 1;
	}

	return p;
}

void tartagliaTriangle::printRow(ostream& stream, int arrayToPrint[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arrayToPrint[i] << " ";
	}

	cout << endl;
}