/*
    Convertire da decimale a binario utilizzando le sottrazioni successive.
*/

#include <stdio.h>

int findPowerOfTwo(int number);

int main()
{
    // Acquisici il numero da convertire
    int input = 0;
    printf("Inserisci un numero: ");
    scanf("%d", &input);

    int pow = findPowerOfTwo(input);
    // Fino a quando la potenza non raggiunge 0, continuiamo a sottrarla al numero inserito e stampiamo 1 se la sottrazione è avvenuta, altrimenti 0. 
    // Poi passiamo alla potenza di 2 successiva.
    for (pow; pow > 0; pow >>= 1)
    {
        if (input >= pow)
        {
            input -= pow;
            printf("1");
        }
        else
            printf("0");
    }
    return 0;
}

// Metodo necessario per trovare la potenza di 2 subito inferiore al numero da convertire
int findPowerOfTwo(int number)
{
    // Variabile temporanea che conserverà la potenza desiderata
    int pow = 1;
    // Continua ad elevare per 2 se non superiamo il numero
    while(pow << 1 <= number)
    {
        pow <<= 1;    
    }
    // Abbiamo trovato ciò che ci serve
    return pow;
}