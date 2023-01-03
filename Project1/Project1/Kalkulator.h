#pragma once
#include <string>
#include <vector>

using namespace std;

class Kalkulator {
private:
	int brojevi[6];
	int trenutni;
public:
	int trazeno;
	int najblize;
	string najblizi_izraz;
	Kalkulator();
	Kalkulator(int broj, int brojevi[6]);
	int izracunaj(string stringic);
};
