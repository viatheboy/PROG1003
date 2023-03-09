#include <iostream>
#include <string>
#include "LesData2.h"
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

class Publikasjon {
    private:
        string tittel;
        float pris;
    public: 
        Publikasjon(ifstream & inn) {
            inn >> pris;
            inn.ignore();
            getline(inn, tittel);
        }
        virtual void skrivTilFil(ofstream & ut) {
            ut << fixed << setprecision(2);
            ut << pris << ' ' << tittel << '\n';
        }
};

class Bok : public Publikasjon {
    private: 
        string forfatter;
        int antallSider;
    public: 
        Bok(ifstream & inn) : Publikasjon(inn) {
            inn >> antallSider;
            inn.ignore();
            getline(inn, forfatter);
        }
        virtual void skrivTilFil(ofstream & ut) {
            cout << 'B' << ' ';
            Publikasjon::skrivTilFil(ut);
            ut << fixed << setprecision(2);
            ut << antallSider << " " << forfatter << "\n";
        }

};
class Magasin : public Publikasjon {
    private:
        int aar, volum;
    public: 
        Magasin(ifstream & inn) : Publikasjon(inn) {
            inn >> aar >> volum;
            inn.ignore();
        }
        virtual void skrivTilFil(ofstream & ut) {
            cout << 'M' << ' ';
            Publikasjon::skrivTilFil(ut);
            ut << fixed << setprecision(2);
            ut << aar << " " << volum << "\n";
        }
};

vector <Publikasjon*> gPublikasjonene;

/**
 * Hovedprogram
 * 
 * @return int 
 */
int main() {
    ifstream innfil("oppg_16.dta");
    ofstream utfil("ny_fil_16.DTA");
    char objektType;

    if (innfil) {
        cout << "Leser data fra oppg_16.dta\n";
        innfil >> objektType;

        while (!innfil.eof()) {
            innfil.ignore();
            switch(objektType) {
                case 'B': gPublikasjonene.push_back(new Bok(innfil));       break;
                case 'M': gPublikasjonene.push_back(new Magasin(innfil));   break;
                default: cout << "Finner ikke filtypen\n";
            }
            innfil >> objektType;
        }
        innfil.close();

        cout << "Skriver til oppg_16.DT2\n";
        for (int i = 0; i < gPublikasjonene.size(); i++) {
            gPublikasjonene[i]->skrivTilFil(utfil);
        }

    } else {
        cout << "Finner ikke filen...\n";
    }

    utfil.close();

    return 0;
}