/**
 *  Starten på oblig nr 3 - Hotellrombookinger.
 *
 *  Programmet:
 *    - skriver ut på skjermen:
 *          - alle hotellets bookede rom
 *          - status/fakturaen for ett gitt rom
 *    - sjekker en gjest inn/ut
 *    - leser/skriver hele datastrukturen fra/til fil
 *
 *  @file OBLIG3.CPP
 *  @author  av den innledende/startende koden: 
 *           Malin Foss,  Markus Olsvik,  Øystein Qvigstad  &  FrodeH, NTNU
 */


#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "LesData2.h"
using namespace std;


const int MAXDOGN              =   14,    ///<  Max.antall døgn mulig å booke.
          LAVESTEROMNR         =  100,    ///<  Hotellets laveste romnummer.
          HOYESTEROMNR         =  999,    ///<  Hotellets høyeste romnummer.
          PRISENKELTROM        = 1000,    ///<  Døgnpris for enkeltrom.
          PRISDOBBELTROM       = 1500,    ///<  Døgnpris for dobbeltrom.
          PRISALLINCLUSIVE     = 1200,    ///<  Døgnpris for 2 stk all inclus.
          PRISFILMPAKKE        =   50,    ///<  Døgnpris for filmpakke.
          PRISFROKOST          =  170,    ///<  Frokostpris - KUN enkeltrom.
          STUDENTRABATTPROSENT =   40;    ///<  Studentrabatt i prosent
                                          //        (gjelder KUN enkeltrom).

/**
 *  Operasjonene som utføres på et rom (ser kundataene eller sjekker ut).
 */
enum romOperasjon  {  seData,  sjekkUt  };


/**
 *  Baseklassen 'Hotellrom' (med gjestens navn og antall bookede døgn).
 */
class Hotellrom {
    protected:
        string navn;                           //  Bookers/gjestens navn.
        int antallDager;                       //  Oppholdets varighet.

    public:
        Hotellrom() {  }
        Hotellrom(ifstream & inn);
        virtual ~Hotellrom()  {  }
        string hentNavn() const  {  return navn;  }
        virtual void lesData();
        virtual void skrivData() const = 0;  // Pure virtual - dvs. subklasser
        virtual void skrivHoveddata() const = 0; // MÅ lage disse funksjonene.
        virtual void skrivTilFil(ofstream & ut) const;
};


/**
 *  Avledet klasse 'Enkeltrom' (med om har frokost og evt studentrabatt).
 */
class Enkeltrom : public Hotellrom {
    private:
        bool frokost,                    //  Bare enkeltrom har studentrabatt!
             studentRabatt;              //  Bare enkeltrom har frokost!

    public:
        Enkeltrom()  {  }
        Enkeltrom(ifstream & inn);
        virtual ~Enkeltrom()  {  }
        virtual void lesData();
        virtual void skrivData() const;
        virtual void skrivHoveddata() const;
        virtual void skrivTilFil(ofstream & ut) const;
};


/**
 *  Avledet klasse 'Dobbeltrom' (med om har All Inclusive og/eller filmpakke).
 */
class Dobbeltrom : public Hotellrom {
    private:
        bool allInclusive,            //  Bare dobbeltrom har 'All inclusive'!
             filmpakke;               //  Bare dobbeltrom har filmpakke!

    public:
        Dobbeltrom()  {  }
        Dobbeltrom(ifstream & inn);
        virtual ~Dobbeltrom()  {  }
        virtual void lesData();
        virtual void skrivData() const;
        virtual void skrivHoveddata() const;
        virtual void skrivTilFil(ofstream & ut) const;
};


void bookRom();
void lesFraFil();
void rom(const romOperasjon sDsU);
void skrivAlleRommene();
void skrivBookedeRomnumre();
void skrivMeny();
void skrivTilFil();


map <int, Hotellrom*> gHotellRommene;      ///<  Alle hotellrommene.


/**
 *  Hovedprogram.
 */
int main() {
    char menyvalg;

    lesFraFil();

    skrivMeny();
    menyvalg = lesChar("\nMenyvalg");

    while (menyvalg != 'Q')  {
        switch (menyvalg) {
            case 'S':  skrivAlleRommene(); break;
            case 'B':  bookRom();          break;
            case 'F':  rom(seData);        break;
            case 'U':  rom(sjekkUt);       break;
            default:   skrivMeny();        break;
        }
        menyvalg = lesChar("\nMenyvalg");
    }

   skrivTilFil();

   return 0;
}


/**
 * Leser inn alle baseklassens datamedlemmer fra fil.
 * 
 * @param   inn - Filobjektet data leses inn fra
 */
Hotellrom::Hotellrom(ifstream & inn) {
    getline(inn, navn);
    inn >> antallDager;
}


/**
 * Funksjon som skriver alle klassens datamedlemmer til fil.
 * 
 * @param   ut - Filobjektet datamedlemmene skrives til.
 */
void Hotellrom::skrivTilFil(ofstream & ut) const {
    ut << navn << " " << antallDager << "\n"; 
}


/**
 *  Leser inn alle subklassens og baseklassens datamedlemmer.
 * 
 * @param   inn - Filobjektet datamedlemmene leses fra. 
 */
Enkeltrom::Enkeltrom(ifstream & inn) : Hotellrom(inn) {
    inn >> frokost >> studentRabatt;
    inn.ignore(2);
}


/**
 * Funksjon som sjekker om frokost og studentrabatt gjelder for et rom, skriver så ut 
 * det om det er true. 
 */
void Enkeltrom::skrivHoveddata() const {
    cout << "Enkeltrom\n";
    if (frokost) {
        cout << "Frokost\n";
    }
    if (studentRabatt) {
        cout << "Studentrabatt\n";
    }
}


/**
 * Funksjon som skriver alle baseklassen og klassens datamedlemmer til fil.
 * 
 * @param   ut - Filobjektet datamedlemmene skrives til.
 * @see     Hotellrom::skrivTilFil(...)
 */
void Enkeltrom::skrivTilFil(ofstream & ut) const {
    ut << 'E';                                      // Subklasse av typen 'E'
    Hotellrom::skrivTilFil(ut);
    ut << frokost << " " << studentRabatt << "\n";
}


/**
 * Leser inn alle subklassens og baseklassens datamedlemmer.
 * 
 * @param   inn - Filobjektet datamedlemmene leses fra.
 */
Dobbeltrom::Dobbeltrom(ifstream & inn) : Dobbeltrom(inn) {
    inn >> allInclusive >> filmpakke;
    inn.ignore(2);
}


/**
 * Funksjon som sjekker om et rom inneholder all inclusive og filmpakke,
 * skriver ut dette om det er true.
 */
void Dobbeltrom::skrivHoveddata() const {
    cout << "Dobbeltrom\n";
    if (allInclusive) {
        cout << "All Inclusive\n";
    }
    if (filmpakke) {
        cout << "Filmpakke\n";
    }
}


/**
 * Funksjon som skriver alle baseklassen og klassens datamedlemmer til fil.
 * 
 * @param   ut - Filobjektet datamedlemmene skrives til.
 * @see     Hotellrom::skrivTilFil(...)
 */
void Dobbeltrom::skrivTilFil(ofstream & ut) const {
    ut << "D";                                      // Subklasse av typen 'D'
    Hotellrom::skrivTilFil(ut);
    ut << allInclusive << " " << filmpakke << "\n";
}


/**
 * Funksjon som leser inn alle hotellrom fra fil og legger de inn i hotelromlisten. 
 */
void lesFraFil() {
    ifstream innfil("HOTEL.txt");  // .txt format pga MacOS
    char romType;
    int romNr;

    if (innfil) {
        cout << "Leser inn fra 'HOTEL.txt'\n";
        innfil >> romType >> romNr;
        while (!innfil.eof()) {
            innfil.ignore(2);
            switch(romType) {
                case 'E': gHotellRommene[romNr] = new Enkeltrom(innfil);    break;
                case 'D': gHotellRommene[romNr] = new Dobbeltrom(innfil);   break;
                default: cout << "Finner ikke romtypen.\n";
            }
            innfil >> romType >> romNr;
        }
        innfil.close();
    } else {
        cout << "Finner ikke filen 'HOTEL.txt'\n";
    }
}


/**
 * Skriver et roms datamedlemmer til en gitt fil.
 * 
 * @see     virtual Hotellrom::skrivTilFil(...)
 */
void skrivTilFil() {
    ofstream utfil("HOTEL.txt");     // .txt grunnet MacOS
    cout << "Skriver til filen 'HOTEL.txt'.\n";
    for (const auto & val : gHotellRommene) {
        val.second->skrivTilFil(utfil);
    }
    utfil.close();
}


/**
 * Funksjon som skriver ut menyen til brukeren.
 */
void skrivMeny() {
    cout << "Vennligst velg et alternativ: \n"
         << "S - Skriv alle rommene\n"
         << "B - Book et rom"
         << "F - Se data om et rom"
         << "U - Sjekk ut"
         << ": ";
}


/**
 * Funksjon som skriver ut romnumrene til bookede rom.
 */
void skrivBookedeRomnumre() {
    cout << "Alle bookede hotellrom: \n";
    if (gHotellRommene.size() > 0) {
        for (const auto & val : gHotellRommene) {
            cout << val.first << "\n";
        }
    } else {
        cout << "Finnes ingen bookede hotellrom.\n";
    }
}


/**
 * Funksjon som skriver ut alle rom som er booket. Skriver ut navnet på romgjesten, 
 * samt om det er enkeltrom/dobbeltrom, og hvilke tjenester/fordeler som knyttes til rommet.
 * 
 * @see     Hotellrom::hentNavn()
 * @see     Enkeltrom::skrivHoveddata()
 * @see     Dobbeltrom::skrivHoveddata()
 */
void skrivAlleRommene() {
    if (gHotellRommene.size() > 0) {
        for (const auto & val : gHotellRommene) {
            cout << "Navn: " << val.second->hentNavn() << "\n";
            val.second->skrivHoveddata();
        }
    } else {
        cout << "Finnes ingen bookede rom.\n";
    }
}