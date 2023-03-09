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
#include "LesData2.h"
using namespace std;

bool returnTrue(int antPass) {
    return (antPass);
}

int main() {

    int antPassasjerer = 10;

    cout << (!returnTrue(antPassasjerer)) << endl;


    return 0;

}
