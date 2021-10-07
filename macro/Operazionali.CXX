#include <iostream>
#include <cmath>

struct misura          // struct per contenere i valori della misura ed i rispettivi errori
{
    double valore;     // il valore della misura
    double errore = 0; // rispettivo errore
};

misura CalcolaErroriDivisione(double valore, double valore_divisone) // crea una struct da valore ed grand/div, magari se mi gira meglio fare una Classe (?)
{
    misura risultato;
    risultato.valore = valore;
    risultato.errore = valore_divisone/5;
    return risultato;
}

misura CreatoreStruct(double Valore, double Errore) // crea una struct da valore ed errore, magari si forse meglio fare una classe dopo per gestire tutto questo.
{
    misura risultato;
    risultato.valore = Valore;
    risultato.errore = Errore;
    return risultato;
}

class Operazionale      // dichiaro una classe per gestire il circuito invertente
{

public:

    misura frequenza; // frequenza in kHz
    misura guadagno;

    void Assegna(misura Vin, misura Vout, misura frequenza_temporary)
    {

        guadagno.valore = Vout.valore/Vin.valore;
        guadagno.errore = sqrt( pow ( Vout.valore / pow ( Vin.valore , 2 ) , 2 ) * pow ( Vin.errore,2 ) + pow( 1 / Vin.valore , 2 ) * pow( Vout.errore , 2 ) );
        frequenza.valore = frequenza_temporary.valore;
        frequenza.errore = frequenza_temporary.errore;
    }




};
void Invertente(int Nmisure, double Vin[], double Vin_divisione[], double Vout[], double Vout_divisone[], double frequenza[], double errore_frequenza[], int guadagno_teorico = 1 )
{
    Operazionale operazionale[Nmisure];

    for (int i = 0; i < Nmisure; i++) operazionale[i].Assegna(CalcolaErroriDivisione(Vin[i],Vin_divisione[i]),CalcolaErroriDivisione(Vout[i],Vout_divisone[i]),CreatoreStruct(frequenza[i],errore_frequenza[i]));
}


void Operazionali()
{
 cout << "prova" << endl;
}
