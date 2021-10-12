#include <cmath>
#include <iostream>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TF1.h>
#include <iomanip>
using namespace std;
void noinv()
{
    //apro il file
  Char_t dati[200];
   sprintf(dati,"noinv.txt");
   FILE *indata = fopen(dati, "r" ); // apre il file denominato "filnamres"

  float f [14];
  float G [14];
  float sf [14];
   float sG [14];
  float nf = 0;
  float nG = 0;
  float nsf = 0;
   float nsG = 0;
  int npoints = 0;



  // verifico che esista il file
  if(!indata) { // file couldn't be opened
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }
  // leggo il contenuto del file
  while(!feof(indata)) { // keep reading until end-of-file
    fscanf(indata,"%f %f %f %f\n",&nG,&nf,&nsf,&nsG);

  	// riempio i vettori con i dati nel file
  	f[npoints]=nf;
  	G[npoints]=nG;
  	sf[npoints]=nsf;
    sG[npoints]=nsG;


    ++npoints;
  }

  cout << "End-of-file reached.." << endl;
  fclose(indata); //chiudo il file
TCanvas *cG = new TCanvas("cG","G(f)",200,10,600,400);
  cG->SetFillColor(0);
  cG->cd();
  cG->SetLogx(1);
  cG->SetLogy(1);
  TGraphErrors *gG = new TGraphErrors(npoints,f,G,sf,sG);
  gG->SetMarkerSize(0.6);
  gG->SetMarkerStyle(21);
  gG->SetTitle("Guadagno OPA non invertente");
 gG->GetXaxis()->SetTitle("f [Hz]");
  gG->GetYaxis()->SetTitle("G");
  gG->Draw("AP");

  cout << "\n\n --- funzione G --- \n" <<endl;
  TF1 *funz1 = new TF1("funz1","[1]*sqrt(1/(pow(x/[0],2)+1))",0.004,200000);
  // Le tre seguenti linee servono per inizializzare i parametri della funzione.
  funz1->SetParameter(0,252);
  funz1->SetParameter(1,2);
  funz1->SetParName(0, "frequenza di taglio");
  funz1->SetParName(1, "guadagno massimo");
  // Talvolta è necessario imporre che un determinato parametro sia in un intervallo di validità definito. Usare
  // questa funzione solo se con SetParameter il fit non converge o se il fit converge per un valore del parametro che esce dall'intervallo
  // con significato fisico (e.g., una temperatura assoluta < 0 K).
  // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
  funz1->SetLineColor(2); // Blu
  // Istruzione per fare il fit ai dati usando la funzione funz1 sopra definita
  // + significa che voglio aggiungere la funzione funz1 alla lista delle funzioni già disegnate sul canvas
  // R significa che voglio fare il fit solo in un determinato range, definito quando ho creato funz1. Quindi in questo caso (0-130) Ohm
  // In questo caso, mettere o non mettere l'opzione R è equivalente, visto che 0-130 copre tutto il range delle misure.
  // M dice di usare Hesse che fa una stima più accurata delle incertezze sui parametri. Nel caso di problemi rimuovere l'opzione.
  gG->Fit(funz1,"RM+");
  gStyle->SetOptFit(1111); //print the information on fit parameters results in the statistics box directly on the TGraph

  cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;


}
