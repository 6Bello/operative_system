/*
    Name: algoritmo SJF
    Copyright:
    Author: Albamonte Giuseppe
    Date: 10/04/23 11:45
    Description: funzionamento di un algoritmo SJF 
*/

#include <iostream>
#include <vector>
#include "general_scheduling.h"
#include "signature.h"
#include "alghoritm_SJF.h"
using namespace std;

// MAIN
int main()
{

    vector<processo> processi = {{0, 2, 4, 4}, {1, 0, 6, 6}, {2, 1, 1, 1}, {3, 3, 4, 4}, {4, 4, 1, 1}};
    // inizializza(processi);

    vector<int> sequenzaTemporale;

    esecuzioneSJFPrentive(processi, sequenzaTemporale);
    stampaSequenzaTemporale(sequenzaTemporale);

    // signatureWalterWhite();
    return 0;
}
