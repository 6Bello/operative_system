#pragma once
#include <vector>
#include "struct_processo.h"

using namespace std;

// inizializzazione funzione per far vedere la sequenza temporale
void printSequenzaTemporale(vector<processo> processi, int attesaCoda[]);
// funzione per trovare l'attesa di ogni singolo processo, ritorna un vettore
void trovaAttesaSingola(int attesaCoda[], vector<processo> processi);

// FUNZIONI

void printSequenzaTemporale(vector<processo> processi, int attesaCoda[])
{
	int processoSuccessivo = 0;
	int istante = 0;
	for (int i = 0; i < processi.size(); i++)
	{
		for (int j = 0; j < processi[i].tempoDiEsecuzione; j++)
		{
			cout << "|" << processi[i].id << "|";
			istante++;
		}
	}
}

void trovaAttesaSingola(int attesaCoda[], vector<processo> processi)
{

	attesaCoda[0] = 0;
	int tempoDiEsecuzioneTotale = 0;
	for (int i = 1; i < processi.size(); i++)
	{
		tempoDiEsecuzioneTotale += processi[i - 1].tempoDiEsecuzione;
		attesaCoda[i] = tempoDiEsecuzioneTotale - processi[i].istanteDiArrivo;
	}
}
