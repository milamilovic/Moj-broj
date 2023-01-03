//ovaj program sluzi za igranje igre ,,Moj broj" u paru
//autor Mila Milovic SV22/2021

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Kalkulator.h"
#include <list>
#include <cstdlib>
#include "std_lib_facilities.h"

using namespace std;

//pomocna funkcija koja nam splituje string na delove po razmaku
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


	//stringstream ss(s);
	//vector<string> words;
	//for (string w; ss >> w; ) words.push_back(w);
	return words;
}

//funkcija koja
string izracunaj_sve(vector<int> dostupni_brojevi) {
	for (int i = 0; i < dostupni_brojevi.size(); i++) {
		cout << dostupni_brojevi[i] << " ";
	}
	cout << endl;
	return "";
}

int main() {
	//upuststva za igrace
	cout << "Dobro dosli u igru moj broj!" << endl;
	cout << "Igra se igra u nekoliko rundi, u prvoj je prvi igrac igrac A, u drugoj igrac B i tako naizmenicno" << endl;
	cout << "Potrebno je sastaviti izraz sa vrednoscu tacno tj sto blize trazenom broju i sto je blize to vise poena nosi." << endl;
	cout << "Tacan broj nosi 20 pona, +-5 nosi 10 poena, a +-5-10 bodova vredi 5 poena" << endl;
	cout << "Na kraju svake runde ce kompjuter prikazati (jedno) tacno resenje ili najblize moguce resenje." << endl;
	cout << "Pobednik je igrac koji na kraju igre ima najvise poena." << endl;
	cout << "Ukoliko oba igraca dodju do sitog resenja pobednik je onaj igrac koji je prvi igrao u toj rundi." << endl;
	cout << "Igra sada pocinje, srecno!" << endl << endl;

	//ucitavamo podatke tj otvaramo fajl
	string ime_fajla = "";
	ifstream in_stream;
	while (true)
	{
		if (ime_fajla != "") {
			cerr << "GRESKA: pogresno ime ulaznog fajla! ";
		}
		cout << "Unesite ime ulaznog fajla: " << endl;
		cin >> ime_fajla;
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
	int broj_pobedaA = 0;
	int broj_pobedaB = 0;

	//svaka iteracija ove while petlje u stvari predstavlja jednu rundu igre
	while (!in_stream.eof())
	{
		//ispisujemo podatke u konzolu
		string red;
		getline(in_stream, red);
		vector<string> reci = split(red);
		int ponudjeni_brojevi[6];
		cout << "Brojevi koji se koriste:" << endl;
		string dostupni_brojevi = "";
		for (int i = 0; i < reci.size() - 1; i++) {
			cout << reci.at(i) << '\n';
			dostupni_brojevi += reci.at(i);
			dostupni_brojevi += " ";
			ponudjeni_brojevi[i] = stoi(reci.at(i));
		}
		string trazeni_broj = reci.at(reci.size() - 1);
		cout << "Trazeni broj: " << trazeni_broj << endl << endl;

		//napravimo kalkulator za ovu rundu
		Kalkulator kalkulator = Kalkulator(stoi(trazeni_broj));

		//igraci unose svoje izraze i oni se odmah racunaju
		int vrednostA;
		int vrednostB;
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
				}
				//racunamo vrednost izraza
				vrednostA = kalkulator.izracunaj(unos_igracA, ponudjeni_brojevi);
				if (vrednostA != 999999999) {
					break;
				}
				else {
					cout << "Vas izraz nije validan. Pokusajte opet! " << endl;
				}
			}
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
				}
				//racunamo vrednost izraza
				vrednostB = kalkulator.izracunaj(unos_igracB, ponudjeni_brojevi);
				if (vrednostB != 999999999) {
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
				}
				//racunamo vrednost izraza
				vrednostB = kalkulator.izracunaj(unos_igracB, ponudjeni_brojevi);
				if (vrednostB != 999999999) {
					break;
				}
				else {
					cout << "Vas izraz nije validan. Pokusajte opet! " << endl;
				}
			}
			while (true)
			{
				cout << "Igrac A je na redu, unesite vase resenje: " << endl;
				cin >> unos_igracA_0;
				unos_igracA = "";
				//izbacujemo razmake
				for (char c : unos_igracA_0) {
					if (c == '*' || c == '/' || c == '+' || c == '-' || c == '(' || c == ')' || c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9') {
						unos_igracA += c;
					}
				}
				//racunamo vrednost izraza
				vrednostA = kalkulator.izracunaj(unos_igracA, ponudjeni_brojevi);
				if (vrednostA != 999999999) {
					break;
				}
				else {
					cout << "Vas izraz nije validan. Pokusajte opet! " << endl;
				}
			}
		}

		//pronalazak tacnog(najblizeg) resenja
		//ako je nekood igraca nasao tacno resenje nece ni traziti vec uzima to
		string resenje = "";
		if (vrednostA == stoi(trazeni_broj)) {
			resenje += unos_igracA;
		}
		else if (vrednostB == stoi(trazeni_broj)) {
			resenje += unos_igracB;
		}
		else {
			vector<int>dostupni_brojevi_vektor;
			for (int i : ponudjeni_brojevi) {
				dostupni_brojevi_vektor.push_back(i);
			}
			//proverimo kombinacije sa 6 brojeva
			//ova funkcija ispituje sve moguce permutacije ovih brojeva (ispituje i sve varijante operanada)
			string izraz = izracunaj_sve(dostupni_brojevi_vektor);
			if (kalkulator.izracunaj(izraz, ponudjeni_brojevi) == stoi(trazeni_broj)) {
				resenje += izraz;
				break;
			}
			//ako resenje ne postoji proveravamo da li ima resenje sa manje brojeva tj 5
			int eliminisani_broj5 = 9999;
			for (int i = 0; i < 6; i++) {
				//proverimo da li smo u prethodnoj iteraciji nasli resenje
				if (resenje != "") {
					break;
				}
				if (eliminisani_broj5 != 9999) {
					dostupni_brojevi_vektor.insert(dostupni_brojevi_vektor.begin() + i - 1, eliminisani_broj5);
				}
				//ovde proverimo da li je jedan od ponudjenih brojeva ujedno i resenje
				if (ponudjeni_brojevi[i] == stoi(trazeni_broj)) {
					resenje += to_string(ponudjeni_brojevi[i]);
					break;
				}
				eliminisani_broj5 = dostupni_brojevi_vektor[i];
				dostupni_brojevi_vektor.erase(dostupni_brojevi_vektor.begin() + i);
				//dakle sad ispitamo kombinacije sa 5 brojeva
				string izraz = izracunaj_sve(dostupni_brojevi_vektor);
				int eliminisani_broj4 = 9999;
				if (kalkulator.izracunaj(izraz, ponudjeni_brojevi) == stoi(trazeni_broj)) {
					resenje += izraz;
					break;
				}
				//ako ne postoji probamo da uklonimo jos dakle sa 4 broja
				else {
					for (int j = 0; j < 5; j++) {
						//proverimo da li smo u prethodnoj iteraciji nasli resenje
						if (resenje != "") {
							break;
						}
						if (eliminisani_broj4 != 9999) {
							dostupni_brojevi_vektor.insert(dostupni_brojevi_vektor.begin() + j - 1, eliminisani_broj4);
						}
						eliminisani_broj4 = dostupni_brojevi_vektor[j];
						dostupni_brojevi_vektor.erase(dostupni_brojevi_vektor.begin() + j);
						//dakle kombinacije sa 4 broja
						string izraz = izracunaj_sve(dostupni_brojevi_vektor);
						int eliminisani_broj3 = 9999;
						if (kalkulator.izracunaj(izraz, ponudjeni_brojevi) == stoi(trazeni_broj)) {
							resenje += izraz;
							break;
						}
						else {
							for (int k = 0; k < 4; k++) {
								//proverimo da li smo u prethodnoj iteraciji nasli resenje
								if (resenje != "") {
									break;
								}
								if (eliminisani_broj3 != 9999) {
									dostupni_brojevi_vektor.insert(dostupni_brojevi_vektor.begin() + k - 1, eliminisani_broj3);
								}
								eliminisani_broj3 = dostupni_brojevi_vektor[k];
								dostupni_brojevi_vektor.erase(dostupni_brojevi_vektor.begin() + k);
								//dakle kombinacije sa 3 broja
								string izraz = izracunaj_sve(dostupni_brojevi_vektor);
								int eliminisani_broj2 = 9999;
								if (kalkulator.izracunaj(izraz, ponudjeni_brojevi) == stoi(trazeni_broj)) {
									resenje += izraz;
									break;
								}
								else {
									for (int l = 0; l < 3; l++) {
										//proverimo da li smo u prethodnoj iteraciji nasli resenje
										if (resenje != "") {
											break;
										}
										if (eliminisani_broj2 != 9999) {
											dostupni_brojevi_vektor.insert(dostupni_brojevi_vektor.begin() + l - 1, eliminisani_broj2);
										}
										eliminisani_broj2 = dostupni_brojevi_vektor[l];
										dostupni_brojevi_vektor.erase(dostupni_brojevi_vektor.begin() + l);
										//dakle kombinacije sa 2 broja
										string izraz = izracunaj_sve(dostupni_brojevi_vektor);
										if (kalkulator.izracunaj(izraz, ponudjeni_brojevi) == stoi(trazeni_broj)) {
											resenje += izraz;
											break;
										}
									}
									dostupni_brojevi_vektor.insert(dostupni_brojevi_vektor.end(), eliminisani_broj2);
								}
							}
							dostupni_brojevi_vektor.insert(dostupni_brojevi_vektor.end(), eliminisani_broj3);
						}
					}
					dostupni_brojevi_vektor.insert(dostupni_brojevi_vektor.end(), eliminisani_broj4);
				}
			}
			dostupni_brojevi_vektor.insert(dostupni_brojevi_vektor.end(), eliminisani_broj5);
		}
		int vrednostK = kalkulator.izracunaj(resenje, ponudjeni_brojevi);

		//provera ko je blizi i upisivanje u fajl
		string pobednik = "";
		if (abs(stoi(trazeni_broj) - vrednostA) < abs(stoi(trazeni_broj) - vrednostB)) {
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
		string upis = "Broj runde: " + to_string(broj_runde) + "\nDostupni podaci: " + dostupni_brojevi;
		upis += "\nTrazeni broj: " + trazeni_broj;
		upis += "\nIgrac A je dobio vrednost " + to_string(vrednostA) + " koja odsutpa od trazenog za " + to_string(abs(stoi(trazeni_broj) - vrednostA));
		upis += "\nIgrac B je dobio vrednost " + to_string(vrednostB) + " koja odsutpa od trazenog za " + to_string(abs(stoi(trazeni_broj) - vrednostB));
		upis += "\nIzraz igraca A je " + unos_igracA;
		upis += "\nIzraz igraca B je " + unos_igracB;
		upis += "\nRundu je dobio " + pobednik;
		upis += "\nIzraz koji je kompjuter dobio je " + resenje;
		upis += "\nVrednost resenja koje je dobio kompjuter je " + to_string(vrednostK) + "\n\n\n";
		fajl_rezultati << upis;

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
	fajl_rezultati << upis;
	fajl_rezultati.close();

	keep_window_open();
}