#pragma once
#include <vector>
#include "struct_processo.h"
#include "general_scheduling.h"

void esecuzioneSJF(vector<processo> processi, int tempoTotale, int *sequenzaTemporale)
{
    int numeroDiProcessi = processi.size();                // TODO: temporaneo
    int prcInArrivo = 0, prcInEsecuzione = processi[0].id; // numeroCoda serve a tenere il conto nella coda
    vector<processo> coda;                                 // creo coda con vector per poter aggiungere all'arrivo
    // processo *processiOrdinId=ordinamentoProcessiPerId(processi, numeroDiProcessi); //ancora da decidere se usare o no malloc
    vector<processo> processiOrdinId = processi;
    ordinamentoProcessiPerId(processiOrdinId);
    for (int i = 0; i < tempoTotale; i++)
    {
        if (processi[prcInArrivo].istanteDiArrivo == i)
        {
            coda.push_back(processi[prcInArrivo]); // quando un processo arriva lo aggiungo alla coda
            prcInArrivo++;                         // aggiungo uno ai prcInArrivo in modo da controllare quando arriva il processo successivo
        }
        if (processiOrdinId[prcInEsecuzione].tempoRimanente == 0)
        {
            coda.erase(coda.begin());                                   // quando un processo finisce lo elimino dalla coda per evitare problemi di ordinamento
            ordinamentoProcessiPerTempoDiEsecuzione(coda, coda.size()); // li riordino
            cout << "esce " << prcInEsecuzione << " a " << i << " ed entra " << coda[0].id << endl;
            prcInEsecuzione = coda[0].id; // il processo in esecuzione diventa il primo della coda
        }
        processiOrdinId[prcInEsecuzione].tempoRimanente--; // il tempo rimanente per il processo in esecuzione diminuisce di uno
        sequenzaTemporale[i] = prcInEsecuzione;            // durante quell'istante c'è quel processo in esecuzione e do quel dato in modo da poterlo stampare dopo
    }
}

void esecuzioneSJFPrentive(vector<processo> processi, vector<int> &sequenzaTemporale)
{
    int numeroDiProcessi = processi.size();                         // TODO transitorio : rimuovere in refactoring
    ordinamentoProcessiPerIstanteDiArrivo(processi);                // ordino i processi per istante di arrivo
    int tempoTotale = trovaTempoTotale(processi, numeroDiProcessi); // tempo totale per il completamento dei processi
    int prcInArrivo = 0, prcInEsecuzione = processi[0].id;          // numeroCoda serve a tenere il conto nella coda
    vector<processo> coda;                                          // creo coda con vector per poter aggiungere all'arrivo
    // processo *processiOrdinId=ordinamentoProcessiPerId(processi, numeroDiProcessi); //ancora da decidere se usare o no malloc
    vector<processo> processiOrdinId = processi; // gustoso no?! invece di for ecc...
    ordinamentoProcessiPerId(processiOrdinId);
    for (int i = 0; i < tempoTotale; i++)
    {
        if (processi[prcInArrivo].istanteDiArrivo == i)
        {
            if (processi[prcInArrivo].tempoRimanente < processiOrdinId[prcInEsecuzione].tempoRimanente)
            {                                                     // se il nuovo processo ha meno cpu burst di quello in esecuzione
                coda.insert(coda.begin(), processi[prcInArrivo]); // lo aggiungo all'inizio della coda
                cout << prcInEsecuzione << "viene prelato e " << coda[0].id << " entra" << endl;
                prcInEsecuzione = coda[0].id; // lo faccio diventare il processo in esecuzione
            }
            else
            {
                coda.push_back(processi[prcInArrivo]); // altrimenti lo aggiungo alla fine della coda
            }
            prcInArrivo++; // aggiungo uno ai prcInArrivo in modo da controllare quando arriva il processo successivo
        }
        if (processiOrdinId[prcInEsecuzione].tempoRimanente == 0)
        {
            coda.erase(coda.begin());                                   // quando un processo finisce lo elimino dalla coda per evitare problemi di ordinamento
            ordinamentoProcessiPerTempoDiEsecuzione(coda, coda.size()); // li riordino
            cout << "esce " << prcInEsecuzione << " a " << i << " ed entra " << coda[0].id << endl;
            prcInEsecuzione = coda[0].id; // il processo in esecuzione diventa il primo della coda
        }
        processiOrdinId[prcInEsecuzione].tempoRimanente--; // il tempo rimanente per il processo in esecuzione diminuisce di uno
        sequenzaTemporale.push_back(prcInEsecuzione);      // durante quell'istante c'è quel processo in esecuzione e do quel dato in modo da poterlo stampare dopo
    }
}
