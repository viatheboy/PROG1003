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

    map <int, string> gMappen;

    for (int i = 0; i < 20; i++) {
        gMappen[i] = "Heya";
    }

    for (const auto & val : gMappen) {
        cout << val.first+1 << "\n";
    }


    return 0;

}
