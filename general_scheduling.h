#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "struct_processo.h"

using namespace std;

// inizializzazione funzione per far scrivere nel terminale il numero totale di processi
int nProcessi();

// inizializzazione funzione per inizializzare i processi da parte dell'utente
void inizializza(vector<processo> processi);
// inizializzazione funzione per ordinare i processi in base all'istante di arrivo (bubbleSort)
void ordinamentoProcessiPerIstanteDiArrivo(vector<processo> &processi);
// inizializzazione funzione per ordinare i processi in base al tempo di esecuzione (bubbleSort)
void ordinamentoProcessiPerTempoDiEsecuzione(vector<processo> &processi, int processiLength);
// inizializzazione funzione per ordinare i processo in base all'id
void ordinamentoProcessiPerId(vector<processo> &processi);
// inizializzazione funzione per scrivere i processi con il loro istante di arrivo ed il loro cpuBurst
void printProcessi(vector<processo> &processi);
// inizializzazione funzione per trovare l'attesa media dei processi

float trovaAttesaMedia(int attesaCoda[], int processiLength);
// inizializzazione funzione per trovare il tempo totale di completamento
int trovaCompletamento(vector<processo> processi, int attesaCoda[], int processiLength);
// inizializzazione funzione per trovare la media di completamento di un processo singolo
float trovaCompletamentoMedia(int completamentoTotale, int processiLength);
// ritorna il tempo totale che la cpu ha messo per terminare l'esecuzione
int trovaTempoTotale(vector<processo> processi, int numeroDiProcessi);
// // Definizione della funzione ordinamentoProcessiPerId
// processo *ordinamentoProcessiPerId(vector<processo> processi, int numeroDiProcessi)

void stampaSequenzaTemporale(int tempoTotale, vector<int> stampaSequenzaTemporale);

int nProcessi()
{
	int n;
	cout<<"inserire il numero di processi ";
	cin >> n;
	return n;
}

void inizializza(vector<processo> processi)
{
	int numeroDiProcessi = nProcessi();
	processo p;
	for (int i = 0; i < numeroDiProcessi; i++)
	{
		p.id = i;
		leggeProcesso(p);
		stampaProcesso(p);
		p.tempoRimanente = p.tempoDiEsecuzione;
		processi.push_back(p);
	}

}

bool confrontaPerIstanteDiArrivo(processo a, processo b)
{
	return (a.istanteDiArrivo < b.istanteDiArrivo);
}

void ordinamentoProcessiPerIstanteDiArrivo(vector<processo> &processi)
{
	sort(processi.begin(), processi.end(), confrontaPerIstanteDiArrivo);
}


void ordinamentoProcessiPerTempoDiEsecuzione(vector<processo> &processi, int processiLength){
	cout<<"|";
	for(int i=0; i<processiLength; i++){
		cout<<processi[i].id<<"|";
	}
	cout<<"->";
	for(int j=0; j<processiLength; j++){
		for (int i=0; i<processiLength-1; i++){
			if(processi[i].tempoRimanente>processi[i+1].tempoRimanente){
				processo swap = processi[i];
				processi[i] = processi[i + 1];
				processi[i + 1] = swap;
			}
		}
	}
	cout<<"|";
	for(int i=0; i<processiLength; i++){
		cout<<processi[i].id<<"|";
	}
	cout << endl;
}

bool confrontaPerId(processo a, processo b)
{
	return (a.id < b.id);
}

void ordinamentoProcessiPerId(vector<processo> &processi)
{
	sort(processi.begin(), processi.end(), confrontaPerId);
}

void printProcessi(vector<processo> processi)
{
	for (processo p : processi)
	{
		// cout<<"processo "<<processi[i].id<<endl<<"   -istante di arrivo: "<<processi[i].istanteDiArrivo<<endl<<"   -tempo di esecuzione: "<<processi[i].tempoDiEsecuzione<<endl;
		stampaProcesso(p);
	}
	cout << endl;
}

float trovaAttesaMedia(int attesaCoda[], int processiLength)
{
	float attesaMedia = 0;
	for (int i = 1; i < processiLength; i++)
	{
		attesaMedia += attesaCoda[i];
	}
	attesaMedia /= processiLength;
	return attesaMedia;
}

int trovaCompletamento(vector<processo> processi, int attesaCoda[])
{
	int processiLength = processi.size();
	float tempoCompletamento = 0;
	for (int i = 1; i < processiLength; i++)
	{
		tempoCompletamento += attesaCoda[i] + processi[i].tempoDiEsecuzione;
	}
	return tempoCompletamento;
}

float trovaCompletamentoMedia(int completamentoTotale, int processiLength)
{
	float completamentoMedia = (float)completamentoTotale / processiLength;
	return completamentoMedia;
}

int trovaTempoTotale(vector<processo> processi, int numeroDiProcessi)
{
	int tempoTotale = 0;
	for (processo p : processi)
	{
		tempoTotale += p.tempoDiEsecuzione;
	}
	return tempoTotale;
}

void stampaSequenzaTemporale(vector<int> sequenzaTemporale)
{
	for (int idProcesso : sequenzaTemporale)
		cout << "|" << idProcesso << "|";
	cout << endl;
}
// processo *ordinamentoProcessiPerId(vector<processo> processi, int numeroDiProcessi){
//     // Allocazione dinamica della memoria per l'array di processi ordinato
//     processo *processiOrdinId = (processo*) malloc(numeroDiProcessi * sizeof(processo)); //malloc si usa per prendere una porzione di memoria a cui poi si andranno a mettere i valori dell'array, i questo modo quando si ritornano i valori tramite il puntatore questo punta ad una vera cella di memoria perchè quest'ultima non viene svuotata alla fine della funzione!

//     // Copia dei processi dall'array originale all'array ordinato
//     for (int i = 0; i < numeroDiProcessi; i++)
//     {
//         processiOrdinId[i]=processi[i];
//     }

//     // Restituzione del puntatore all'array di processi ordinato
// 	return processiOrdinId;
// }
