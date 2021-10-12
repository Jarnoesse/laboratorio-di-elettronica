#include <cmath> 
#include <iostream>           
#include <TGraphErrors.h>     
#include <TAxis.h>            
#include <TCanvas.h>          
#include <TF1.h>              
#include <iomanip> 

using namespace std;

void ampl_inv_1()
{
	const int nmisure = 17;
	
	float f[] = {0.001,0.05,1,50,50,100,150,300,500,600,950,1000,1300,1500,2000,4000,400};
	float G[] = {1.025641026,1,0.9875,0.951219512,0.961538462,0.948717949,0.943037975,0.860759494,0.666666667,0.524691358,0.432098765,0.387345679,0.302469136,0.265432099,0.219135802,0.145061728,0.760124611};

	float sG[] = {0.1298,0.1250,0.1242,0.1190,0.1257,0.1249,0.1230,0.1178,0.1029,0.0633,0.0575,0.0548,0.0341,0.0318,0.0290,0.0244,0.0548};
	float sf[]={0.00002,0.00125,0.02,1.25,1.25,2,4.5,9,12.5,18,45.125,50,33.8,45,80,160,16};
	
	
TCanvas *cG = new TCanvas("cG","G(f)",200,10,600,400);
  cG->SetFillColor(0);
  cG->cd();
  cG->SetLogx(1);
  cG->SetLogy(1);
  TGraphErrors *gG = new TGraphErrors(nmisure,f,G,sf,sG);
  gG->SetMarkerSize(0.6);
  gG->SetMarkerStyle(21);
  gG->SetTitle("Guadagno OPA invertente");
  gG->GetXaxis()->SetTitle("f [kHz]");
  gG->GetYaxis()->SetTitle("G");
  gG->Draw("AP"); 
  
  cout << "\n\n --- funzione G --- \n" <<endl;
  TF1 *funz1 = new TF1("funz1","[1]*sqrt(1/(pow(x/[0],2)+1))",0.004,200000);
  // Le tre seguenti linee servono per inizializzare i parametri della funzione.
  funz1->SetParameter(0,100); 
  funz1->SetParameter(1,10);
  funz1->SetParName(0, "frequenza di taglio");
  funz1->SetParName(1, "guadagno massimo");
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
