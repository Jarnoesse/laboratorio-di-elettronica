#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

#include <TCanvas.h>
#include <TH1.h>

using namespace std;

/*  Produce l'istogramma delle frequenze dei vari codici nel set di dati specificato.
    Comando da terminale:
    root -l
    .x DNLramp.cpp+("nome_del_file.txt")

    Authors: Ernesto Migliore, Michele Risino
    Dipartimento di Fisica - Universita` di Torino
    Created: 2021.06.15
*/
void DNLramp(const char *nomeFile)
{
    // Lettura dei dati dal file di testo in un std::vector, ignorando i tempi
    string valore;
    vector<double> codici;
    try
    {
        ifstream file(nomeFile);
        while (getline(file, valore, ',')) //legge il tempo e lo scarta
        {
            getline(file, valore, '\n');
            codici.push_back(atof(valore.c_str())); //legge il codice e lo aggiunge al vector
        }
    }
    catch (...)
    {
        cout << "File non trovato o formato del file non supportato" << endl;
        return;
    }

    // Istogramma delle frequenze di ciascun codice nel set di dati
    TCanvas *c = new TCanvas(nomeFile, nomeFile, 200, 10, 600, 400);
    TH1 *h = new TH1I(nomeFile, "", 16, -0.5, 15.5);
    h->FillN(codici.size(), &codici[0], 0);
    h->SetStats(false);
    h->GetXaxis()->SetTitle("codici");
    h->GetYaxis()->SetTitle("frequenze assolute");
    h->GetYaxis()->SetRangeUser(0, h->GetMaximum()*1.2);
    h->Draw();
}
