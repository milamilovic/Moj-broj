#pragma once
#include <string>
#include <vector>
#include "Kalkulator.h"
#include <algorithm>

using namespace std;

//funkcija koja od vektora sa brojevima koji se koriste proverava sve permutacije
//i sve varijante operanada medju njima
string izracunaj_sve_zagrade(vector<int> dostupni_brojevi, Kalkulator& k);
//funkcija koja od vektora sa brojevima koji se koriste proverava sve permutacije
//i sve varijante operanada medju njima
string izracunaj_sve(vector<int> dostupni_brojevi, Kalkulator& k);
string izracunaj(int ponudjeni_brojevi[6], string trazeni_broj, Kalkulator& kalkulator);