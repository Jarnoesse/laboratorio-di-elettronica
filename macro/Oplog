#include <iostream>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TF1.h>
#include <iomanip>
#include <cmath>
#include<TH1F.h>
using namespace std;
void Oplog()
{
    //apro il file
  Char_t dati[200];
   sprintf(dati,"log.txt");
   FILE *indata = fopen(dati, "r" ); // apre il file denominato "filnamres"

  float vi [17];
  float svi [17];
  float vo [17];
   float svo [17];
   float i [17];
   float si [17];
  float nvi = 0;
  float nsvi = 0;
  float nvo = 0;
   float nsvo = 0;
    float ni = 0;
   float nsi = 0;
  int npoints = 0;



  // verifico che esista il file
  if(!indata) { // file couldn't be opened
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }
  float r=987;
  // leggo il contenuto del file
  while(!feof(indata)) { // keep reading until end-of-file
    fscanf(indata,"%f %f %f %f %f %f\n",&nvi,&nsvi,&nvo,&nsvo,&ni,&nsi);

  	// riempio i vettori con i dati nel file
  	vi[npoints]=nvi;
  	svi[npoints]=nsvi;
  	vo[npoints]=nvo;
    svo[npoints]=nsvo;
     i[npoints]=ni;
    si[npoints]=nsi;

    ++npoints;
  }

  cout << "End-of-file reached.." << endl;
  fclose(indata); //chiudo il file
TCanvas *cG = new TCanvas("cG","Vo(Vs)",200,10,600,400);
  cG->SetFillColor(0);
  cG->cd();
  //cG->SetLogx(1);
  //cG->SetLogy(1);
  TGraphErrors *gG = new TGraphErrors(npoints,vi,vo,svi,svo);
  gG->SetMarkerSize(0.6);
  gG->SetMarkerStyle(21);
  gG->SetTitle("OPA logaritmico");
 gG->GetXaxis()->SetTitle("Vs [V]");
  gG->GetYaxis()->SetTitle("Vo [V]");
  gG->Draw("AP");

  cout << "\n\n --- LOG --- \n" <<endl;
  TF1 *funz1 = new TF1("funz1","[1]*log(x/[0])",0.1,16.0);
  // Le tre seguenti linee servono per inizializzare i parametri della funzione.
  //funz1->SetParameter(0,100);
  funz1->SetParameter(1,-0.05);
  funz1->SetParName(0, "Io*R");
  funz1->SetParName(1, "-2Vt");
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
