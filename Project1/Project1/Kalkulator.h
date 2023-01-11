//Autor: Mila Milovic SV22-2021
//Datum poslednje izmene: 09.01.2023.
//definicije metoda klase kalkulator koja salje string na racunanje
//najbolji izraz i njegovu vrednost pamti kao atribut
//takodje pamti ponudjene brojeve
//template klasa tako da radi sa bilo kojim tipom podataka
#pragma once

#ifndef _KALKULATOR_H_
#define _KALKULATOR_H_

#include <string>
#include <vector>

using namespace std;

template <typename T>
class Kalkulator {
private:
	T brojevi[6];
	T trenutni;
	bool da_li_su_intovi;
public:
	Kalkulator();
	Kalkulator(T broj, T brojevi[6]);
	T trazeno;
	T najblize;
	string najblizi_izraz;
	T izracunaj_k(string stringic);
};
#endif