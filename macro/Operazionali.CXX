#include <iostream>
#include <cmath>
#include<TGraphErrors.h>
#include<TAxis.h>
#include<TCanvas.h>
#include<TF1.h>
#include<iomanip>



class misura // classe per gestire le misure
{
public:
    double valore;
    double errore;

    void CalcolaErroriDivisione(double valore_temporary, double valore_divisone)
    {
        valore = valore_temporary;
        errore = valore_divisone/5;
    }
    void CreatoreStruct(double valore_temporary, double errore_temporary)
    {
        valore = valore_temporary;
        errore = errore_temporary;
    }

};

class Operazionale      // dichiaro una classe per gestire il circuito invertente
{

public:

    int Nmisure = 19;
    misura frequenza[20]; // frequenza in kHz
    misura guadagno[20];  // il 20 messo se no root non compila :) tanto non abbiamo più di 19 misure se i miei calcoli sono corretti.
    misura Vin[20];
    misura Vout[20];

    TCanvas *canvas = new TCanvas("Titolo","Titolo",200,10,600,400);



    void Assegna(double Vin_valore[],double Vin_errore[],double Vout_valore[],double Vout_errore[], double frequenza_valore[],double frequenza_errore[])
    {
        for(int i = 0; i < Nmisure; i ++)
        {

            guadagno[i].valore = Vout[i].valore/Vin[i].valore;
            guadagno[i].errore = sqrt( pow ( Vout[i].valore / pow ( Vin[i].valore , 2 ) , 2 ) * pow ( Vin[i].errore,2 ) + pow( 1 / Vin[i].valore , 2 ) * pow( Vout[i].errore , 2 ) );
            frequenza[i].valore = frequenza_valore[i];
            frequenza[i].errore = frequenza_errore[i];
        }

    }

    void Grafico()



};
void Invertente(int Nmisure, double Vin[], double Vin_divisione[], double Vout[], double Vout_divisone[], double frequenza[], double errore_frequenza[], int guadagno_teorico = 1 )
{
  /*  Operazionale operazionale[Nmisure];
    misura misura_Vout,misura_Vin,misura_frequenza;

    for (int i = 0; i < Nmisure; i++) // assegno i valori dove devono essere assegnati
    {
        misura_Vout.CalcolaErroriDivisione(Vout[i],Vout_divisone[i]);
        misura_Vin.CalcolaErroriDivisione(Vin[i],Vin_divisione[i]);
        misura_frequenza.CreatoreStruct(frequenza[i],errore_frequenza[i]);
        operazionale[i].Assegna(misura_Vin,misura_Vout,misura_frequenza);
    }

*/
}

void leggi(double vin[], double vout[], double errvin[], double errvout[], double f[], double errf[], char filename[])
{
    FILE *input = fopen(filename, "r" );                                //filename è il nome del file
    float v_in=0,v_out=0,errv_in=0,errv_out=0, freq=0, errfreq=0;                          
    int conta=0;                                                        
    if(!input) 
    {
        cout << "Error: file could not be opened" << endl;
        exit(1);
    }
    while(!feof(input)) 
    {
        fscanf(input,"%f %f %f %f %f %f\n",&v_in, &errv_in,&v_out, &errv_out, &freq ,&errfreq); 
        vin[conta]=v_in;
        vout[conta]=v_out;
        errvin[conta]=errv_in;
        errvout[conta]=errv_out;
        f[conta]=freq;
        errf[conta]=errfreq;
        ++conta;
    }
    fclose(input);
}


void Operazionali()
{

 cout << "prova" << endl;
}
