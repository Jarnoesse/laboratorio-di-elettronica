#include <iostream>
#include <cmath>
#include<TGraphErrors.h>
#include<TAxis.h>
#include<TCanvas.h>
#include<TF1.h>
#include<iomanip>
#include<fstream>
#include<TGraphErrors.h>


/*void ReadData(double Vout[], double Vout_div[], double Vin[], double Vin_div[], double freq[], double freq_div[])
{
    int i = 0;
    std::ifstream infile("noinv.txt");

    while(infile >> Vout[i] >> Vout_div[i] >> Vin[i] >> Vin_div[i])
    {
        i++;
    }


}
*/

double FindMin(double array[], int lunghezza_array = 1)
{
    double min = array[0];

    for (int i=1;i<lunghezza_array;i++) if(array[i] < min) min = array[i];

    return min;
}
double FindMax(double array[], int lunghezza_array = 1)
{
    double max = array[0];

    for (int i=1;i<lunghezza_array;i++) if(array[i] > max) max = array[i];

    return max;
}

class misura // classe per gestire le misure
{
public:
    double valore;
    double errore;

    void CalcolaErroriDivisione(double valore_temporary, double valore_divisone, bool isfreq = false)
    {
        if(isfreq ==  false)
        {
            valore = valore_temporary;
            errore = valore_divisone/5;
        }
        else
        {

            errore = valore_divisone/5;
            valore = valore_temporary;
            errore = pow(valore,2)*errore*pow(10,-6);
        }

    }


};

class Operazionale      // dichiaro una classe per gestire il circuito invertente
{

public:

    int    Nmisure = 19;
    misura frequenza[20]; // frequenza in kHz
    misura guadagno[20];  // il 20 messo se no root non compila :) tanto non abbiamo più di 19 misure se i miei calcoli sono corretti.

    TCanvas *canvas = new TCanvas("Titolo","Titolo",200,10,600,400); // l'idea è che il canvas persista una volta chiusi i metodi...



    void Assegna(double Vin_valore[],double Vin_div[],double Vout_valore[],double Vout_div[], double frequenza_valore[],double frequenza_div[])
    {
        misura Vout, Vin, frequenza_temp;

        for(int i = 0; i < Nmisure; i ++)
        {
            Vout.CalcolaErroriDivisione(Vout_valore[i],Vout_div[i]);
            Vin.CalcolaErroriDivisione(Vin_valore[i],Vin_div[i]);
            frequenza_temp.CalcolaErroriDivisione(frequenza_valore[i],frequenza_div[i], true);

            guadagno[i].valore  = Vout.valore/Vin.valore;
            guadagno[i].errore  = sqrt( pow ( Vout.valore / pow ( Vin.valore , 2 ) , 2 ) * pow ( Vin.errore,2 ) + pow( 1 / Vin.valore , 2 ) * pow( Vout.errore , 2 ) );
            frequenza[i].valore = frequenza_temp.valore;
            frequenza[i].errore = frequenza_temp.errore;
        }

    }

    void Grafico()
    {
        double guadagno_valore_temp[Nmisure];
        double guadagno_errore_temp[Nmisure];
        double frequenza_valore_temp[Nmisure];
        double frequenza_errore_temp[Nmisure];

        std::cout << "Calcolo del guadagno" << endl;
        std::cout << "Guadagno           Frequenza" << endl << endl;

        for(int i=0;i<Nmisure;i++) // il for si poteva evitare ma overall organizzare i dati nella classe misura mi sembrava relativamente più comodo
        {
            guadagno_valore_temp[i]  = guadagno[i].valore;
            guadagno_errore_temp[i]  = guadagno[i].errore;
            frequenza_valore_temp[i] = frequenza[i].valore;
            frequenza_errore_temp[i] = frequenza[i].errore;

            std::cout << guadagno[i].valore << "+-" << guadagno[i].errore << "     " << frequenza[i].valore << "+-" << frequenza[i].errore << endl;
        }

        TGraphErrors *grafico = new TGraphErrors(Nmisure,frequenza_valore_temp,guadagno_valore_temp,frequenza_errore_temp,guadagno_errore_temp); // dichiaro il grafico
        std::cout << "findmin  " << FindMin(frequenza_valore_temp,Nmisure) << "  findmax  " << FindMax(frequenza_valore_temp,Nmisure) <<endl;
        TF1 *funzione = new TF1("funz1","[1]*sqrt([0]/(pow(x,2)+[0]))",FindMin(frequenza_valore_temp,Nmisure),FindMax(frequenza_valore_temp,Nmisure));

        funzione->SetParameter(0,1000);
        funzione->SetParameter(1,10);
        funzione->SetParName(0, "frequenza taglio al quadrato");
        funzione->SetParName(1, "guadagno massimo");

        canvas->SetFillColor(0); // setto un po' di cose
        canvas->cd();
        canvas->SetLogx();
        grafico->Draw("AP");
        grafico->Fit(funzione,"RM+");




    }



};
void Computa(int N_misure, double Vin[], double Vin_divisione[], double Vout[], double Vout_divisone[], double frequenza[], double div_frequenza[], int guadagno_teorico = 1 )
{

    Operazionale operazionale;

    operazionale.Nmisure = N_misure;
    operazionale.Assegna(Vin,Vin_divisione,Vout,Vout_divisone,frequenza,div_frequenza);
    operazionale.Grafico();




}


void Operazionali()
{
    // invertente 1
    int Nmisure          = 17;
    double Vin[]         = {624,640,640,656,624,624,632,632,648,648,648,648,648,648,648,648,642};    // mV
    double Vin_div[]     = {200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,100};    //mV/div
    double Vout[]        = {640,640,632,624,600,592,596,544,432,340,280,251,196,172,142,94 ,488};    //mV
    double Vout_div[]    = {200,200,200,200,200,200,200,200,200,100,100,100,50 ,50 ,50 ,50, 100};    //mV/div
    double frequenza[]   = {0.001,0.05,1,50,50,100,150,300,500,600,950,1000,1300,1500,2000,4000,400};//kHz
    double secondi_div[] = {100000000,2500000,100000,2500,2500,1000,1000,500,250,250,250,250,100,100,100,50,500}; // sec


    Computa(Nmisure, Vin, Vin_div, Vout, Vout_div, frequenza, secondi_div);

}
