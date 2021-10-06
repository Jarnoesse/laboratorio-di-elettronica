#include <cmath> 
#include <iostream>           
#include <TGraphErrors.h>     
#include <TAxis.h>            
#include <TCanvas.h>          
#include <TF1.h>              
#include <iomanip> 

using namespace std;


void invertenti()
{
const int nmisure1 = 17;
	
	float f1[] = {0.001,0.05,1,50,50,100,150,300,500,600,950,1000,1300,1500,2000,4000,400};
	float G1[] = {1.025641026,1,0.9875,0.951219512,0.961538462,0.948717949,0.943037975,0.860759494,0.666666667,0.524691358,0.432098765,0.387345679,0.302469136,0.265432099,0.219135802,0.145061728,0.760124611};

	float sG1[] = {0.1298,0.1250,0.1242,0.1190,0.1257,0.1249,0.1230,0.1178,0.1029,0.0633,0.0575,0.0548,0.0341,0.0318,0.0290,0.0244,0.0548};
	float sf1[]={0.00002,0.00125,0.02,1.25,1.25,2,4.5,9,12.5,18,45.125,50,33.8,45,80,160,16};
	
    const int nmisure10 = 19;
	

	float f10[] = {0.001,0.005,0.01,0.05,0.1,0.5,1,5,10,50,75,100,250,150,200,400,500,800,1000};
	float G10[] = {9.4000,9.8000,9.8000,9.8000,9.8000,9.8000,9.8000,9.4231,9.3333,8.1604,7.1028,6.1111,2.9550,4.5455,3.6364,1.9099,1.5135,0.9464,0.7748};

	float sG10[] = {0.9700,0.9900,0.9900,0.9900,0.9900,0.9900,0.9900,0.9338,0.9206,0.8566,0.5188,0.4681,0.3133,0.3884,0.3471,0.1761,0.1132,0.0869,0.0799};
	float sf10[]={0.00002,0.000125,0.0002,0.00125,0.002,0.0125,0.02,0.125,0.2,2.5,5.625,5,12.5,4.5,8,16,25,32,50};

TGraphErrors *gr1 = new TGraphErrors(nmisure10,f10,G10,sf10,sG10);


   TF1 *funz1 = new TF1("funz1","[1]*sqrt([0]/(pow(x,2)+[0]))",0.004,200000);

  funz1->SetParameter(0,1000); 
  funz1->SetParameter(1,10);
  funz1->SetParName(0, "frequenza taglio al quadrato");
  funz1->SetParName(1, "guadagno massimo");

  funz1->SetLineColor(4); 
  gr1->Fit(funz1,"RM+");
  gStyle->SetOptFit(1111);

  cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;
  


TGraphErrors *gr2 = new TGraphErrors(nmisure1,f1,G1,sf1,sG1);

TF1 *funz2 = new TF1("funz2","[1]*sqrt([0]/(pow(x,2)+[0]))",0.004,200000);
  
  funz2->SetParameter(0,1000); 
  funz2->SetParameter(1,10);
  funz2->SetParName(0, "frequenza taglio al quadrato");
  funz2->SetParName(1, "guadagno massimo");

  funz2->SetLineColor(4);
  gr2->Fit(funz2,"RM+");
  gStyle->SetOptFit(1111); 
  cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: " << funz2->GetNDF() << " (Probability: " << funz2->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;
  

   gr2->Fit(funz2,"RM+");
  gStyle->SetOptFit(1111);

TCanvas *cG = new TCanvas("cG","G(f)",200,10,600,400);
  cG->SetFillColor(0);
  cG->cd();
  cG->SetLogx(1);
  cG->SetLogy(1);
  
TMultiGraph *mg = new TMultiGraph();

mg->Add(gr1,"p");
mg->Add(gr2,"p");

mg->Draw("a");


}