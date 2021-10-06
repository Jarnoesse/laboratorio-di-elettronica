#include <cmath> 
#include <iostream>           
#include <TGraphErrors.h>     
#include <TAxis.h>            
#include <TCanvas.h>          
#include <TF1.h>              
#include <iomanip> 

using namespace std;

void amplificatore()
{
	const int nmisure = 19;
	
	float Vin[] = {200,200,200,200,200,200,200,208,210,212,214,216,222,220,220,222,222,224,222
};
	float Vout[] = {1.88,1.96,1.96,1.96,1.96,1.96,1.96,1.96,1.96,1.73,1.52,1.32,0.656,1,0.8,0.424,0.336,0.212,0.172};
	float f[] = {0.001,0.005,0.01,0.05,0.1,0.5,1,5,10,50,75,100,250,150,200,400,500,800,1000};
	float G[] = {9.4000,9.8000,9.8000,9.8000,9.8000,9.8000,9.8000,9.4231,9.3333,8.1604,7.1028,6.1111,2.9550,4.5455,3.6364,1.9099,1.5135,0.9464,0.7748};
	
	float sVin[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	float sVout[] = {0.02,0.0004,0.1,0.2,0.4,0.4,0.4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	float sG[] = {0.9700,0.9900,0.9900,0.9900,0.9900,0.9900,0.9900,0.9338,0.9206,0.8566,0.5188,0.4681,0.3133,0.3884,0.3471,0.1761,0.1132,0.0869,0.0799};
	float sf[]={0.00002,0.000125,0.0002,0.00125,0.002,0.0125,0.02,0.125,0.2,2.5,5.625,5,12.5,4.5,8,16,25,32,50};
	
	
TCanvas *cG = new TCanvas("cG","G(f)",200,10,600,400);
  cG->SetFillColor(0);
  cG->cd();
  cG->SetLogx(1);
  cG->SetLogy(1);
  TGraphErrors *gG = new TGraphErrors(nmisure,f,G,sf,sG);
  gG->SetMarkerSize(0.6);
  gG->SetMarkerStyle(21);
  gG->SetTitle("G(f) frequenza taglio");
  gG->GetXaxis()->SetTitle("f [Hz]");
  gG->GetYaxis()->SetTitle("G");
  gG->Draw("AP");
  
  cout << "\n\n --- funzione G --- \n" <<endl;
  TF1 *funz1 = new TF1("funz1","[1]*sqrt([0]/(pow(x,2)+[0]))",0.004,200000);
  // Le tre seguenti linee servono per inizializzare i parametri della funzione.
  funz1->SetParameter(0,1000); 
  funz1->SetParameter(1,10);
  funz1->SetParName(0, "frequenza taglio al quadrato");
  // Talvolta è necessario imporre che un determinato parametro sia in un intervallo di validità definito. Usare
  // questa funzione solo se con SetParameter il fit non converge o se il fit converge per un valore del parametro che esce dall'intervallo
  // con significato fisico (e.g., una temperatura assoluta < 0 K).
  // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
  funz1->SetLineColor(4); // Blu
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
