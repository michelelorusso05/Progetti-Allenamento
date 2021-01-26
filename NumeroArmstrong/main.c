/*
	Determina se un numero inserito in input è un numero di Armstrong
*/

#include <stdio.h>
#include <math.h>

// Oh no
#define bool int
#define true 1
#define false 0

bool checkArmstrong(int num, int length);
int numberLength(int num);

int main()
{
	// Dichiaro il numero, e lo prendo in input
	int num = 0;

	printf("Inserisci un numero: ");
	scanf("%d", &num);
	printf("\n");

	int numberLen = numberLength(num);

	// Controllo se il numero è un numero di armstrong
	if (checkArmstrong(num, numberLen) == true)
		printf("Il numero inserito e' un numero di Armstrong\n");
	else
		printf("Il numero inserito non e' un numero di Armstrong\n");

	// Fine del programma
	return 0;
}

bool checkArmstrong(int num, int length)
{
	int temp = num;
	int finalResult = 0;

	// Per ogni cifra contenuta nel numero
	for (int i = length - 1; i >= 0; i--)
	{
		// Trovo la cifra attuale
		int currentNum = temp / pow(10, i);

		// Cancello quella cifra dal numero, per trovare la successiva
		temp -= currentNum * pow(10, i);

		// Aggiungo al risultato finale la cifra attuale elevata a n (lunghezza del numero)
		finalResult += pow(currentNum, length);
	}

	// Controllo finale
	return (num == finalResult);
}

int numberLength(int num)
{
	// Ritorna la lunghezza del numero
	return floor(log10(num)) + 1;
}