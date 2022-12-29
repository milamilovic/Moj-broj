//ovaj program sluzi za igranje igre ,,Moj broj" u paru
//autor Mila Milovic SV22/2021

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//pomocna funkcija koja nam splituje string na delove po razmaku
vector<string> split(const string& s)
{
	stringstream ss(s);
	vector<string> words;
	for (string w; ss >> w; ) words.push_back(w);
	return words;
}

int main() {
	//upuststva za igrace
	cout << "Dobro dosli u igru moj broj!" << endl;
	cout << "Igra se igra u nekoliko rundi, u prvoj je prvi igrac igrac A, u drugoj igrac B i tako naizmenicno" << endl;
	cout << "Potrebno je sastaviti izraz sa vrednoscu tacno tj sto blize trazenom broju i sto je blize to vise poena nosi." << endl;
	cout << "Tacan broj nosi 20 pona, +-5 nosi 10 poena, a +-5-10 bodova vredi 5 poena" << endl;
	cout << "Na kraju svake runde ce kompjuter prikazati (jedno) tacno resenje ili najblize moguce resenje." << endl;
	cout << "Pobednik je igrac koji na kraju igre ima najvise poena." << endl;
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
		cout << "Brojevi koji se koriste:" << endl;
		string dostupni_brojevi = "";
		for (int i = 0; i < reci.size() - 1; i++) {
			cout << reci.at(i) << '\n';
			dostupni_brojevi += reci.at(i);
			dostupni_brojevi += " ";
		}
		cout << "Trazeni broj: " << reci.at(reci.size() - 1) << endl << endl;

		//igraci unose svoja resenja
		if (igracA) {
			cout << "Igrac A je na redu, unesite vase resenje: " << endl;
			cin >> unos_igracA;
			cout << "Igrac B je na redu, unesite vase resenje: " << endl;
			cin >> unos_igracB;
		} 
		else {
			cout << "Igrac B je na redu, unesite vase resenje: " << endl;
			cin >> unos_igracB;
			cout << "Igrac A je na redu, unesite vase resenje: " << endl;
			cin >> unos_igracA;
		}

		//evaluacija unosa
		//to i split mozda treba u poseban cpp i h
		int vrednostA = 1;
		int vrednostB = 2;

		//pronalazak tacnog(najblizeg) resenja
		string resenje = red;
		int vrednostK = 3;

		//provera ko je blizi i upisivanje u fajl
		string pobednik = "";
		if (abs(stoi(reci.at(reci.size() - 1)) - vrednostA) < abs(stoi(reci.at(reci.size() - 1)) - vrednostB)) {
			pobednik += "igrac A";
			broj_pobedaA++;
		}
		else {
			 pobednik += "igrac B";
			 broj_pobedaB++;
		}
		string upis = "Broj runde: " + to_string(broj_runde) + "\nDostupni podaci: " + dostupni_brojevi;
		upis += "\nTrazeni broj: " + reci.at(reci.size() - 1);
		upis += "\nIgrac A je dobio vrednost " + to_string(vrednostA) + " koja odsutpa od trazenog za " + to_string(abs(stoi(reci.at(reci.size() - 1)) - vrednostA));
		upis += "\nIgrac B je dobio vrednost " + to_string(vrednostB) + " koja odsutpa od trazenog za " + to_string(abs(stoi(reci.at(reci.size() - 1)) - vrednostB));
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

	system("pause");
	exit(0);
}