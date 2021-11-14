#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>

#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TF1.h>
#include <TMath.h>
#include <TStyle.h>
#include <TH1F.h>

using namespace std;

// Minimo e massimo dell'intervallo di frequenze in cui cercare quella campionata
const double MIN_FREQ = 1.;    // [Hz]
const double MAX_FREQ = 200.; // [Hz]

/*
    Effettua fit sinusoidali sui dati contenuti nel file specificato.
    Legge le frequenze rilevate al parametro p1, ignorando quelle il cui fit non converge.
    Attenzione: il fit converge solo per valori iniziali molto precisi del parametro frequenza;
    se nessun fit converge, provare a cambiare MIN_FREQ da 1. a 1.125 Hz o viceversa.
    Comando da terminale:
    root -l
    .x nyquist.cpp+("nome_del_file.txt")

    Authors: Ernesto Migliore, Michele Risino
    Dipartimento di Fisica - Universita` di Torino
    Created: 2021.06.15
*/
void nyquist(const char *nomeFile, bool verbose=true)
{
    // Lettura dei dati dal file di testo in due std::vector<double>
    string valore;
    vector<double> tempi, codici; // [s], [cnt]
    char delim = ',';
    try
    {
        ifstream file(nomeFile);
        while (getline(file, valore, delim))
        {
            if (delim == ',')
            {
                tempi.push_back(atof(valore.c_str()));
                delim = '\n';
            }
            else
            {
                codici.push_back(atof(valore.c_str()));
                delim = ',';
            }
        }
        file.close();
    }
    catch (...)
    {
        cout << "File non trovato o formato del file non supportato" << endl;
        return;
    }
    cout<<tempi.size();

    // Creazione degli array delle incertezze sulle misure
    double err_codici[370], err_tempi[370], zeri[370];
    for (unsigned int i = 0; i < 370; i++)
    {
        err_codici[i] = 0.5;     // [cnt] => +- 0.5 LSB
        err_tempi[i] = 0.000010; // [s] => 10 us (educated guess...)
        zeri[i] = 0.;
    }

/*int k;  
  cout<<"Enter an integer value";  
  cin>>k;  
  stringstream ss;  
  ss<<k;  
  string s;  
  ss>>s;  
  cout<<"\n"<<"An integer value is : "<<k<<"\n";  
  cout<<"String representation of an integer value is : "<<s;   
*/
    // Grafico e fit dei dati, assumendo errori nulli sui tempi
    TGraphErrors *g0 = new TGraphErrors(370, &tempi[0], &codici[0], zeri, &err_codici[0]);
    const char *func = "[0]*TMath::Sin(TMath::TwoPi()*[1]*x+[2])+[3]";
    TF1 *fit = new TF1("fit", func, 0., TMath::MaxElement(370, &tempi[0]) + 1);
    fit->SetNpx(10 * 370); // Miglioramento risoluzione del grafico
    double codiceMinimo = TMath::MinElement(codici.size(), &codici[0]);
    double codiceMassimo = TMath::MaxElement(codici.size(), &codici[0]);
    double ampiezza = (codiceMassimo - codiceMinimo) * 0.5;

    double offset = (codiceMassimo + codiceMinimo) * 0.5, frequenza = MIN_FREQ;
    vector<double> frequenzeMigliori;
    TCanvas *c0 = new TCanvas("g0", "g0", 200, 10, 600, 400);
    while (frequenza <= MAX_FREQ) // Prova frequenze tra MIN_FREQ e MAX_FREQ a step di 0.25 Hz
    {
        fit->SetParameters(ampiezza, frequenza, 0., offset);
        //fit->SetParLimits(0,1,2);
        g0->Fit("fit", "RQ");
        if (verbose) cout << "Frequenza [Hz]:" << frequenza << "; Chi^2 fit: " << fit->GetChisquare() << "\n";
        if (fit->GetProb() >= 0.95) frequenzeMigliori.push_back(frequenza);
    //    if (fit->GetProb() >= 0.95) cout << "BEST FIT" << endl << "Frequenza [Hz]:" << fit->GetParameter(1) << endl << "Chi^2:" <<fit->GetChisquare()<< endl << "Ndf: " << fit->GetNDF() << "     p-value: " << fit->GetProb() << endl;
    //    if (fit->GetProb() >= 0.95) {g0->Draw("AP"); getline();}
        frequenza += 0.25; // [Hz]
    }
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(1);
    gStyle->SetFitFormat("4.2f");
    gStyle->SetStatW(0.08); gStyle->SetStatH(0.08);

    // Grafici e fit con frequenze migliori, con aggiunta di errori sui tempi
    string nomeCanvas = string(nomeFile) + "_" + "0";
    TCanvas *c_all = new TCanvas(nomeCanvas.c_str(), nomeCanvas.c_str(), 200, 10, 600, 400);
    TMultiGraph *mg = new TMultiGraph();
    EColor color_list[4] = {kRed, kBlue, kMagenta, kGreen};

    for (unsigned int i = 0; i < frequenzeMigliori.size(); i++)
    {
        stringstream ss;     
        ss<<i+1;  
        string s;  
        ss>>s;
        string nomeCanvas = string(nomeFile) + "_" + s;
        TCanvas *c = new TCanvas(nomeCanvas.c_str(), nomeCanvas.c_str(), 200, 10, 600, 400);
        TGraphErrors *g = new TGraphErrors(370, &tempi[0], &codici[0], zeri, &err_codici[0]);
        fit->SetParName(0,"A_{pp} [cnt]");
        fit->SetParName(1,"freq [Hz]");
        fit->SetParName(2,"#phi [rad]");
        fit->SetParName(3,"offset [cnt]");
        fit->SetParameters(ampiezza, frequenzeMigliori[i],0, offset);
        fit->SetLineColor(color_list[i%4]);
        fit->SetLineWidth(1);
        g->Fit("fit", "RQ");
        g->SetMarkerStyle(kFullCircle); // Punto di media dimensione
        g->SetMarkerSize(0.6);
        g->SetTitle("");
        g->Draw("AP");
        g->GetHistogram()->GetXaxis()->SetTitle("[s]");
        g->GetHistogram()->GetYaxis()->SetTitle("[cnt]");
        cout << "BEST FIT" << endl << "Frequenza [Hz]:" << fit->GetParameter(1) << endl << "Chi^2:" <<fit->GetChisquare()<< endl << "Ndf: " << fit->GetNDF() << "     p-value: " << fit->GetProb() << endl;
        mg->Add(g);
    }

    c_all->cd();
    //gStyle->SetOptFit(0);
    mg->Draw("AP");
    //mg->GetHistogram()->GetXaxis()->SetTitle("[s]");
    //mg->GetHistogram()->GetYaxis()->SetTitle("[cnt]");
        cout<<tempi.size();
    cout<<endl<<codiceMassimo<<endl<<codiceMinimo<<endl<<ampiezza;
}
 
