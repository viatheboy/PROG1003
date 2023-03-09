/**
 *   L¯sningsforslag til oppgave nr 8.
 *
 *   Program som leser inn flere structers-data, legger disse inn i en vector,
 *   skriver vectorens totale innhold, og sletter til slutt alt i vectoren.
 *
 *   @file    OPPG_08.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>                //  cout, cin
#include <string>                  //  string
#include <vector>                  //  vector
#include "LesData2.h"              //  Verkt¯ykasse for lesing av diverse data
using namespace std;


/**
 *  Kamp (med hjemme- og bortelagets navner og deres respektive scorede mÂl).
 */
struct Kamp {
    string hjemmeNavn,
           borteNavn;
    int    hjemmeMaal,
           borteMaal;
};


void kampLesData(Kamp & kamp);
void kampSkrivData(const Kamp* kamp);


vector <Kamp*>  gKampene;          ///<  Alle innlagte/registrerte kamper.


/**
 *  Hovedprogrammet:
 */
int main ()  {
    Kamp* nyKamp;

    do {                              //  Legger inn kamp(er):  
        nyKamp = new Kamp;            //  Lager en ny kamp.
        kampLesData(*nyKamp);         //  Fyller dens datamedlemmer.
        gKampene.push_back(nyKamp);   //  Ny PEKER legges BAKERST i vectoren.
    } while (lesChar("\nFlere kamper (J/n)") != 'N');  //  Flere kamper?


    for (int i = 0; i < gKampene.size(); i++)  //  Skriver HELE vectorens
        kampSkrivData(gKampene[i]);            //    innhold (ALLE kampene):

                            //  EN mÂte (av mange) Â fjerne ALT i vectoren:
    while (!gKampene.empty())  {            //  SÂ lenge PEKERE i vectoren:
        delete gKampene[gKampene.size()-1]; //  Sletter den SISTE TILPEKTE.
        gKampene.pop_back();                //  Sletter/fjerner SELVE PEKEREN.
    }
/*                            //  En annen (og enklere?) mÂte:
    for (int i = 0; i < gKampene.size(); i++)  //  Sletter ALLE kampene:
        delete gKampene[i];
    gKampene.clear();                          //  Fjerner ALT i vectoren.
*/
                                            //  Kontroll om vectorens antall:
    cout << "\nAntall i vectoren nÂ: " << gKampene.size() << "\n\n";

    return 0;
}


/**
 *  Leser og fyller alle en Kamp-struct sine datamedlemmer (vha ref-overf¯r).
 *
 *  @param   kamp  - Structen som fÂr fylt alle sine data (referanseoverf¯rt)
 */
void kampLesData(Kamp & kamp)  {
    cout << "Hjemmelag:  ";       getline(cin, kamp.hjemmeNavn);
    cout << "Bortelag:   ";       getline(cin, kamp.borteNavn);
    kamp.hjemmeMaal = lesInt("Hjemmelagets antall mÂl", 0, 20);
    kamp.borteMaal  = lesInt("Bortelagets antall mÂl ", 0, 20);
}


/**
 *  Skriver ut pÂ skjermen ALLE en struct sine datamedlemmer.
 *
 *  @param   kamp  - Structen som ALLE datamedlemmene skrives ut for
 */
void kampSkrivData(const Kamp* kamp)  {
    cout << '\t' << kamp->hjemmeNavn << " - " << kamp->borteNavn
         << '\t' << kamp->hjemmeMaal << '-'   << kamp->borteMaal << '\n';
}