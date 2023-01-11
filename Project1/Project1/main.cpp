//ovaj program sluzi za igranje igre ,,Moj broj" u paru
//Autor: Mila Milovic SV22-2021
//Datum poslednje izmene: 11.01.2023.
//u ovom fajlu se nalazi pomocna funkcija za splitovanje reda koji se procita iz fajla
//i main koji izvrsava igru
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <cstdlib>
#include "std_lib_facilities.h"
#include "funkcije.h"
#include "Kalkulator.h"
#include "Kalkulator.cpp"

using namespace std;

//pomocna funkcija koja nam splituje string na delove po razmaku
//ulazni argument je string koji se deli na delove po razmaku
//povratna vrednost je vektor stringova koji su dobijeni deljenjem
vector<string> split(string s)
{
	int start = 0;
	string deli = " ";
	vector<string> words;
	int end = s.find(deli);
	while (end != -1) {
		words.push_back(s.substr(start, end - start));
		start = end + deli.size();
		end = s.find(deli, start);
	}
	words.push_back(s.substr(start, end - start));
	return words;
}

//main funkcija, ostvaruje komunikaciju sa igracima i poziva funkcije za izracunavanje
//argument komandne linije je naziv fajla koji se otvara
//ovo se moze promeniti sa desnim klikom na projekat, pa properties Conf. prop./Debugging --> Command arguments
int main(int argc, char *argv[]) {
	//upuststva za igrace
	cout << "Dobro dosli u igru moj broj!" << endl;
	cout << "Igra se igra u nekoliko rundi, u prvoj je prvi igrac igrac A, u drugoj igrac B i tako naizmenicno" << endl;
	cout << "Potrebno je sastaviti izraz sa vrednoscu tacno tj sto blize trazenom broju." << endl;
	cout << "Pobednik runde je igrac koji ima izraz blize vrednost trazenoj." << endl;
	cout << "Ukoliko oba igraca dodju do istog resenja pobednik je onaj igrac koji je prvi igrao u toj rundi." << endl;
	cout << "Pobednik je igrac koji pobedi u vise rundi." << endl;
	cout << "Igra sada pocinje, srecno!" << endl << endl;

	//ucitavamo podatke tj otvaramo fajl
	//ovo dole ispod treba otkomentarisati ako korisnik zeli da unese ime ulaznog unutar programa
	//string ime_fajla = "";
	string ime_fajla = argv[1];
	ifstream in_stream;
	while (true)
	{
		/*if (ime_fajla != "") {
			cerr << "GRESKA: pogresno ime ulaznog fajla! ";
		}
		cout << "Unesite ime ulaznog fajla: " << endl;
		cin >> ime_fajla;*/
		in_stream.open(ime_fajla);
		if (in_stream.fail()) {
			continue;
		}
		break;
	}

	bool igracA = true;
	string unos_igracA_0 = "";
	string unos_igracB_0 = "";
	string unos_igracA = "";
	string unos_igracB = "";
	int broj_runde = 1;
	ofstream fajl_rezultati("Rezultati.txt");
	fajl_rezultati.close();
	int broj_pobedaA = 0;
	int broj_pobedaB = 0;
	bool int_vrednosti = true;

	//svaka iteracija ove while petlje u stvari predstavlja jednu rundu igre
	while (!in_stream.eof())
	{
		//ispisujemo podatke u konzolu
		string red;
		getline(in_stream, red);
		vector<string> reci = split(red);
		double ponudjeni_brojevi_d[6];
		int ponudjeni_brojevi[6];
		cout << "Brojevi koji se koriste:" << endl;
		string dostupni_brojevi = "";
		for (int i = 0; i < reci.size() - 1; i++) {
			cout << reci.at(i) << '\n';
			dostupni_brojevi += reci.at(i);
			dostupni_brojevi += " ";
			//ako postoji tacka rec je o double vrednostima
			for (char c : reci.at(i)) {
				if (c == '.') {
					int_vrednosti = false;
				}
			}
		}
		for (int i = 0; i < reci.size() - 1; i++) {
			if (int_vrednosti) {
				ponudjeni_brojevi[i] = stoi(reci.at(i));
			}
			else {
				ponudjeni_brojevi_d[i] = stod(reci.at(i));
			}
		}
		string trazeni_broj = reci.at(reci.size() - 1);
		cout << "Trazeni broj: " << trazeni_broj << endl << endl;

		//napravimo kalkulator za ovu rundu
		Kalkulator<int> kalkulator;
		Kalkulator<double> kalkulator_d;
		if (int_vrednosti) {
			kalkulator = Kalkulator<int>(stoi(trazeni_broj), ponudjeni_brojevi);
		}
		else {
			kalkulator_d = Kalkulator<double>(stod(trazeni_broj), ponudjeni_brojevi_d);
		}

		//igraci unose svoje izraze i oni se odmah racunaju
		int vrednostA = 0;
		int vrednostB = 0;
		double vrednostAd = 0;
		double vrednostBd = 0;
		if (igracA) {
			while (true)
			{
				cout << "Igrac A je na redu, unesite vase resenje: " << endl;
				cin >> unos_igracA_0;
				//izbacujemo razmake
				unos_igracA = "";
				for (char c : unos_igracA_0) {
					if (c == '*' || c == '/' || c == '+' || c == '-' || c == '(' || c == ')' || c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9') {
						unos_igracA += c;
					}
					if (!int_vrednosti && c == '.') {
						unos_igracA += c;
					}
				}
				//racunamo vrednost izraza
				if (int_vrednosti) {
					vrednostA = kalkulator.izracunaj_k(unos_igracA);
				}
				else {
					vrednostAd = kalkulator_d.izracunaj_k(unos_igracA);
				}
				if (int_vrednosti && vrednostA != 999999999) {
					break;
				}
				if (!int_vrednosti && vrednostAd != 999999999) {
					break;
				}
				else {
					cout << "Vas izraz nije validan. Pokusajte opet! " << endl;
				}
			}
			while (true)
			{
				//ako je prvi igrac uneo nevalidan unos igrac b automatski dobija bodove
				if (vrednostA == 5555555) {
					if (int_vrednosti) {
						vrednostB = stoi(trazeni_broj);
					}
					break;
				}
				cout << "Igrac B je na redu, unesite vase resenje: " << endl;
				cin >> unos_igracB_0;
				unos_igracB = "";
				//izbacujemo razmake
				for (char c : unos_igracB_0) {
					if (c == '*' || c == '/' || c == '+' || c == '-' || c == '(' || c == ')' || c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9') {
						unos_igracB += c;
					}
					if (!int_vrednosti && c == '.') {
						unos_igracB += c;
					}
				}
				//racunamo vrednost izraza
				if (int_vrednosti) {
					vrednostB = kalkulator.izracunaj_k(unos_igracB);
				}
				else {
					vrednostBd = kalkulator_d.izracunaj_k(unos_igracB);
				}
				if (int_vrednosti && vrednostB != 999999999) {
					break;
				}
				if (!int_vrednosti && vrednostBd != 999999999) {
					break;
				}
				else {
					cout << "Vas izraz nije validan. Pokusajte opet! " << endl;
				}
			}
		}
		else {
			while (true)
			{
				cout << "Igrac B je na redu, unesite vase resenje: " << endl;
				cin >> unos_igracB_0;
				unos_igracB = "";
				//izbacujemo razmake
				for (char c : unos_igracB_0) {
					if (c == '*' || c == '/' || c == '+' || c == '-' || c == '(' || c == ')' || c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9') {
						unos_igracB += c;
					}
					if (!int_vrednosti && c == '.') {
						unos_igracB += c;
					}
				}
				//racunamo vrednost izraza
				if (int_vrednosti) {
					vrednostB = kalkulator.izracunaj_k(unos_igracB);
				}
				else {
					vrednostBd = kalkulator_d.izracunaj_k(unos_igracB);
				}
				if (int_vrednosti && vrednostB != 999999999) {
					break;
				}
				if (!int_vrednosti && vrednostBd != 999999999) {
					break;
				}
				else {
					cout << "Vas izraz nije validan. Pokusajte opet! " << endl;
				}
			}
			while (true)
			{
				if (vrednostB == 5555555) {
					if (int_vrednosti) {
						vrednostA = stoi(trazeni_broj);
					}
					break;
				}
				cout << "Igrac A je na redu, unesite vase resenje: " << endl;
				cin >> unos_igracA_0;
				unos_igracA = "";
				//izbacujemo razmake
				for (char c : unos_igracA_0) {
					if (c == '*' || c == '/' || c == '+' || c == '-' || c == '(' || c == ')' || c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9') {
						unos_igracA += c;
					}
					if (!int_vrednosti && c == '.') {
						unos_igracA += c;
					}
				}
				//racunamo vrednost izraza
				if (int_vrednosti) {
					vrednostA = kalkulator.izracunaj_k(unos_igracA);
				}
				else {
					vrednostAd = kalkulator_d.izracunaj_k(unos_igracA);
				}
				if (int_vrednosti && vrednostA != 999999999) {
					break;
				}
				if (!int_vrednosti && vrednostAd != 999999999) {
					break;
				}
				else {
					cout << "Vas izraz nije validan. Pokusajte opet! " << endl;
				}
			}
		}

		//pronalazak tacnog(najblizeg) resenja
		//ako je nekood igraca nasao tacno resenje nece ni traziti vec uzima to
		cout << endl << "Kompjuter racuna..." << endl << endl;
		string resenje = "";
		string vrednostK = "";
		if (int_vrednosti) {
			if (vrednostA == stoi(trazeni_broj) && vrednostB != 5555555) {
				resenje += unos_igracA;
			}
			else if (vrednostB == stoi(trazeni_broj) && vrednostA != 5555555) {
				resenje += unos_igracB;
			}
			else {
				resenje = izracunaj(ponudjeni_brojevi, trazeni_broj, kalkulator);
			}
			if (resenje != "") {
				vrednostK = to_string(kalkulator.izracunaj_k(resenje));
			}
			else {
				vrednostK = to_string(kalkulator.najblize);
			}
		}
		else {
			if (vrednostAd == stod(trazeni_broj)) {
				resenje += unos_igracA;
			}
			else if (vrednostBd == stod(trazeni_broj)) {
				resenje += unos_igracB;
			}
			else {
				resenje = izracunaj_d(ponudjeni_brojevi_d, trazeni_broj, kalkulator_d);
			}
			if (resenje != "") {
				vrednostK = to_string(kalkulator_d.izracunaj_k(resenje));
			}
			else {
				vrednostK = to_string(kalkulator_d.najblize);
			}
		}
		if (int_vrednosti) {
			cout << "Izraz koji je kompjuter pronasao je: " << kalkulator.najblizi_izraz << endl;
		}
		else {

			cout << "Izraz koji je kompjuter pronasao je: " << kalkulator_d.najblizi_izraz << endl;
		}
		cout << "Vrednost ovog izraza je " << vrednostK << endl;

		//provera ko je blizi i upisivanje u fajl
		string pobednik = "";
		if (int_vrednosti) {
			if (vrednostA == 5555555) {
				pobednik += "igrac B";
				broj_pobedaB++;
				vrednostA = 0;
			}
			else if (vrednostB == 5555555) {
				pobednik += "igrac A";
				broj_pobedaA++;
				vrednostB = 0;
			}
			else if (abs(stoi(trazeni_broj) - vrednostA) < abs(stoi(trazeni_broj) - vrednostB)) {
				pobednik += "igrac A";
				broj_pobedaA++;
			}
			else if (abs(stoi(trazeni_broj) - vrednostA) > abs(stoi(trazeni_broj) - vrednostB)) {
				pobednik += "igrac B";
				broj_pobedaB++;
			}
			else if (igracA) {
				pobednik += "igrac A";
				broj_pobedaA++;
			}
			else {
				pobednik += "igrac B";
				broj_pobedaB++;
			}
		}
		else {
			if (vrednostAd == 5555555) {
				pobednik += "igrac B";
				broj_pobedaB++;
				vrednostAd = 0;
			}
			else if (vrednostBd == 5555555) {
				pobednik += "igrac A";
				broj_pobedaA++;
				vrednostBd = 0;
			}
			else if (abs(stod(trazeni_broj) - vrednostAd) < abs(stod(trazeni_broj) - vrednostBd)) {
				pobednik += "igrac A";
				broj_pobedaA++;
			}
			else if (abs(stod(trazeni_broj) - vrednostAd) > abs(stod(trazeni_broj) - vrednostBd)) {
				pobednik += "igrac B";
				broj_pobedaB++;
			}
			else if (igracA) {
				pobednik += "igrac A";
				broj_pobedaA++;
			}
			else {
				pobednik += "igrac B";
				broj_pobedaB++;
			}
		}
		ofstream fajl_rezultati("Rezultati.txt", ios::app);
		cout << "Pobednik ove runde je " << pobednik << endl << endl << endl;
		string upis = "Broj runde: " + to_string(broj_runde) + "\nDostupni podaci: " + dostupni_brojevi;
		upis += "\nTrazeni broj: " + trazeni_broj;
		if (int_vrednosti) {
			upis += "\nIgrac A je dobio vrednost " + to_string(vrednostA) + " koja odsutpa od trazenog za " + to_string(abs(stoi(trazeni_broj) - vrednostA));
			upis += "\nIgrac B je dobio vrednost " + to_string(vrednostB) + " koja odsutpa od trazenog za " + to_string(abs(stoi(trazeni_broj) - vrednostB));
		}
		else {
			upis += "\nIgrac A je dobio vrednost " + to_string(vrednostAd) + " koja odsutpa od trazenog za " + to_string(abs(stod(trazeni_broj) - vrednostAd));
			upis += "\nIgrac B je dobio vrednost " + to_string(vrednostBd) + " koja odsutpa od trazenog za " + to_string(abs(stod(trazeni_broj) - vrednostBd));
		}
		upis += "\nIzraz igraca A je " + unos_igracA;
		upis += "\nIzraz igraca B je " + unos_igracB;
		upis += "\nRundu je dobio " + pobednik;
		upis += "\nIzraz koji je kompjuter dobio je " + resenje;
		upis += "\nVrednost resenja koje je dobio kompjuter je " + vrednostK + "\n\n\n";
		fajl_rezultati << upis;
		fajl_rezultati.close();
		//podesavanje promenljivih za sledecu rundu
		if (igracA) {
			igracA = false;
		}
		else {
			igracA = true;
		}
		broj_runde++;
	};

	//upis finalnih podataka u fajl
	string upis = "Broj pobeda igraca A je " + to_string(broj_pobedaA);
	upis += "\nBroj pobeda igraca B je " + to_string(broj_pobedaB);
	if (broj_pobedaA > broj_pobedaB) {
		upis += "\nPOBEDNIK CELE IGRE JE IGRAC A!";
		cout << "\nPOBEDNIK CELE IGRE JE IGRAC A!" << endl;
	}
	else if (broj_pobedaA < broj_pobedaB) {
		upis += "\nPOBEDNIK CELE IGRE JE IGRAC B!";
		cout << "\nPOBEDNIK CELE IGRE JE IGRAC B!" << endl;
	}
	else {
		upis += "/nIGRA JE IZJEDNACENA!";
	}
	ofstream fajl_rezultati1("Rezultati.txt", ios::app);
	fajl_rezultati1 << upis;
	fajl_rezultati1.close();

	//keep_window_open();
	//ovo iznad ne bih da obrisem jer nekad ov sysem("pause") samo odluci da ne radi 10 min pa tad koristim keep window open
	system("pause");
	exit(0);
}