/**
 * @file obligkladd.cpp
 * @author Steffen S. Martinsen  (steffema@stud.ntnu.no) 
 * @version 0.1
 * @date 2023-02-01
 * 
 * ***************************************************************************************************
 * ******************************** NB NB NB NB NB NB NB NB NB NB ************************************ 
 * ***** Her lager vi oss en oblig men ingen char-array FORDI DE ER VI SÅ GODT SOM FERDIG MED!!! *****
 * ***************************************************************************************************
 * ***************************************************************************************************
 */
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <iomanip>
#include <typeinfo>
#include <map>
#include "LesData2.h"
using namespace std;

int main() {
    int ønsketTall;
    bool opptatt;
    char romType;
    float sum = 0;
    int antallDager = 10;
    int PRISENKELTROM = 1000;
    bool frokost = true;
    bool studentRabatt = true;
    int STUDENTRABATTPROSENT = 40;
    int PRISFROKOST = 150;
    int PRISDOBBELTROM = 1500;
    int PRISALLINCLUSIVE = 1200;
    int PRISFILMPAKKE = 170;
    bool allInclusive = true;
    bool filmpakke = false;

    cout << "Gjestens navn: " << "Preben" << ".\n"
         << "Dobbeltrom\t- " << antallDager << " dager:\t" 
         << PRISDOBBELTROM * antallDager << ",-\n";
         sum += PRISDOBBELTROM * antallDager;
        if (allInclusive) {
            cout << "All inclusive\t- " << antallDager << " dager:\t" 
                 << PRISALLINCLUSIVE * antallDager << ",-\n";
            sum += allInclusive * antallDager;
        }
        if (filmpakke) {
            cout << "Filmpakke\t- " << antallDager << " dager:\t" 
                 << PRISFILMPAKKE * antallDager << ",-.\n";
            sum += filmpakke * antallDager;   
        }
        cout << "Sum:\t\t\t\t" << fixed << setprecision(2) << sum << ",-\n";

    return 0;

}
