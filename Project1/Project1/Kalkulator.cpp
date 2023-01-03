//metode klase kalkulator koja racuna vrednost zadatog izraza
//najbolji izraz i njegovu vrednost pamti kao atribut
#include "Kalkulator.h"
#include "Calculator.h"
#include <string>
#include <vector>

using namespace std;

#define vector Vector

//konstruktori
Kalkulator::Kalkulator() : trazeno(0), brojevi{0, 0, 0, 0, 0, 0}, najblize(0), najblizi_izraz(""), trenutni(0){};

Kalkulator::Kalkulator(int broj, int brojevi[6]) {
	this->trazeno = broj;
	this->brojevi[0] = brojevi[0];
	this->brojevi[1] = brojevi[1];
	this->brojevi[2] = brojevi[2];
	this->brojevi[3] = brojevi[3];
	this->brojevi[4] = brojevi[4];
	this->brojevi[5] = brojevi[5];
	this->najblize = 0;
	this->najblizi_izraz = "";
	this->trenutni = 0;
};

//izraz mora biti sacinjen iskljucivo iz brojeva, operanada +, - , * i / i zagrada
//inace se vraca vrednost 999999999 koja oznacava nevalidan izraz
int Kalkulator::izracunaj(string stringic) {

	//izbacujemo prvo izraze koji su predugacki i izraze koji sadrze nesto osim brojeva, operanada i zagrada
	if ((stringic.length() > 20)||(stringic.length() <=0)) {
		return 999999999;
	}
	for (char c : stringic) {
		if (c != '*'&&c != '/'&&c != '+'&&c != '-'&&c != '('&&c != ')'&&c != '0'&&c != '1'&&c != '2'&&c != '3'&&c != '4'&&c != '5'&&c != '6'&&c != '7'&&c != '8'&&c != '9') {
			return 999999999;
		}
	}

	//sada racunamo izraz, za ovo koristim kod kalkulatora sa vezbi
	trenutni = iskalkulisi(stringic, this->brojevi);
	if (abs(trenutni - trazeno) < abs(najblize - trazeno)) {
		najblize = trenutni;
		najblizi_izraz = stringic;
	}
	return trenutni;
	
};