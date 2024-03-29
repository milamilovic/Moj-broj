//Autor: Mila Milovic SV22-2021
//Datum poslednje izmene: 09.01.2023.
//definicije metoda klase kalkulator koja salje string na racunanje
//najbolji izraz i njegovu vrednost pamti kao atribut
//takodje pamti ponudjene brojeve
//template klasa tako da radi sa bilo kojim tipom podataka
#include "Kalkulator.h"
#include "Calculator.h"
#include <string>
#include <vector>

using namespace std;

#define vector Vector

template<typename T>
Kalkulator<T>::Kalkulator() : trazeno(T()), brojevi{ T(), T(), T(), T(), T(), T() }, najblize(T()), najblizi_izraz(""), trenutni(T()), da_li_su_intovi(true) { };

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
	da_li_su_intovi = true;
	for (int i = 0; i < 6; i++) {
		string stringic = to_string(brojici[i]);
		for (char c : stringic) {
			if (c == '.') {
				da_li_su_intovi = false;
			}
		}
	}
};

//izraz 'stringic' mora biti sacinjen iskljucivo iz brojeva, operanada +, - , * i /, zagrada i eventualno tacke kod decimalnih brojeva
//inace se vraca vrednost 999999999 koja oznacava nevalidan izraz
template<typename T>
T Kalkulator<T>::izracunaj_k(string stringic) {

	//izbacujemo izraze koji sadrze nesto osim brojeva, operanada i zagrada
	for (char c : stringic) {
		if (c!='*' && c!='/' && c!='+' && c!='-' && c!='(' && c!=')' && c!='0' && c!='1' && c!='2' && c!='3' && c!='4' && c!='5' && c!='6' && c!='7' && c!='8' && c!='9' && c!='.') {
			return 999999999;
		}
	}

	//sada racunamo izraz, za ovo koristim kod kalkulatora sa vezbi
	double brojici[6] = { 0,0,0,0,0,0 };
	for (int i = 0; i < 6; i++) {
		brojici[i] = double(brojevi[i]);
	}
	trenutni = iskalkulisi(stringic, brojici, da_li_su_intovi);
	if (abs(trenutni - trazeno) < abs(najblize - trazeno)) {
		najblize = trenutni;
		najblizi_izraz = stringic;
	}
	return trenutni;
};