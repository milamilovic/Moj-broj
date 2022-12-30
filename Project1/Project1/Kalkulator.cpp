//metode klase kalkulator koja racuna vrednost zadatog izraza
//najbolji izraz i njegovu vrednost pamti kao atribut
#include "Kalkulator.h"
#include "Calculator.h"
#include <string>
#include <vector>

using namespace std;

#define vector Vector

//konstruktori
Kalkulator::Kalkulator(){
	this->trazeno = 0;
};
Kalkulator::Kalkulator(int broj) {
	this->trazeno = broj;
};

//izraz mora biti sacinjen iskljucivo iz brojeva, operanada +, - , * i / i zagrada
//inace se vraca vrednost 999999999 koja oznacava nevalidan izraz
int Kalkulator::izracunaj(string stringic, int brojevi[6]) {

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
	return iskalkulisi(stringic, brojevi);
	
};