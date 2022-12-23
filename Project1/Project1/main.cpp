#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//funkcija koja nam splituje string na delove po razmaku
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

	//ucitavamo podatke
	string ime_fajla = "";
	ifstream in(ime_fajla);
	while (!in)
	{
		cout << "Unesite ime ulaznog fajla: " << endl;
		cin >> ime_fajla;
		if (ime_fajla != "") {
			cerr << "GRESKA: pogresno ime ulaznog fajla!";
		}
	}
	
	bool igracA = true;
	string unos_igracA = "";
	string unos_igracB = "";
	int broj_runde = 1;

	//svaka iteracija ove while petlje u stvari predstavlja jednu rundu igre
	while (!in.eof())
	{
		//ispisujemo podatke u konzolu
		string red;
		getline(in, red);
		vector<string> reci = split(red);
		cout << "Brojevi koji se koriste:" << endl;
		for (int i = 0; i < reci.size() - 1; i++) {
			cout << reci.at(i) << '\n';
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

		//podesavanje promenljivih za sledecu rundu
		if (igracA) {
			igracA = false;
		}
		else {
			igracA = true;
		}
		broj_runde++;
	};
}