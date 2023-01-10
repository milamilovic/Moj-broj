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
public:
	Kalkulator();
	Kalkulator(T broj, T brojevi[6]);
	T trazeno;
	T najblize;
	string najblizi_izraz;
	T izracunaj_k(string stringic);
};
#endif