#pragma once
#include <string>
#include <vector>

using namespace std;

class Kalkulator {
private:
	int trazeno;
public:
	Kalkulator();
	Kalkulator(int broj);
	int izracunaj(string stringic, int brojevi[6]);
};
