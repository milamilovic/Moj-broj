//metode klase kalkulator koja racuna vrednost zadatog izraza
//najbolji izraz i njegovu vrednost pamti kao atribut
#include "Kalkulator.h"
#include "Calculator.h"
#include <string>
#include <vector>

using namespace std;

#define vector Vector

template<typename T>
Kalkulator<T>::Kalkulator() : trazeno(T()), brojevi{ T(), T(), T(), T(), T(), T() }, najblize(T()), najblizi_izraz(""), trenutni(T()) { };

template<typename T>
Kalkulator<T>::Kalkulator(T broj, T brojici[6])
{
	trazeno = broj;
	this->brojevi[0] = brojici[0];
	this->brojevi[1] = brojici[1];
	this->brojevi[2] = brojici[2];
	this->brojevi[3] = brojici[3];
	this->brojevi[4] = brojici[4];
	this->brojevi[5] = brojici[5];
	najblize = T();
	najblizi_izraz = "";
	trenutni = T();
};

//izraz mora biti sacinjen iskljucivo iz brojeva, operanada +, - , * i / i zagrada
//inace se vraca vrednost 999999999 koja oznacava nevalidan izraz
template<typename T>
T Kalkulator<T>::izracunaj_k(string stringic) {

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
	trenutni = iskalkulisi(stringic, brojevi);
	if (abs(trenutni - trazeno) < abs(najblize - trazeno)) {
		najblize = trenutni;
		najblizi_izraz = stringic;
	}
	return trenutni;
};