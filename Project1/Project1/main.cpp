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
	return words;
}

template<class _Tnumber, class _Titerator >
bool next_variation
(
	_Titerator const& _First
	, _Titerator const& _Last
	, _Tnumber const& _Upper
	, _Tnumber const& _Start = 0
	, _Tnumber const& _Step = 1
)
{
	_Titerator _Next = _First;
	while (_Next != _Last)
	{
		*_Next += _Step;
		if (*_Next < _Upper)
		{
			return true;
		}
		(*_Next) = _Start;
		++_Next;
	}
	return false;
}

string operacije_zagrade = "+-*/()";
string stringic = "";
int visak_zagrada = 0;
int dobijeni_broj;
bool sadrzi_zagrade;
bool racunaj = false;
//funkcija koja od vektora sa brojevima koji se koriste proverava sve permutacije
//i sve varijante operanada medju njima
string izracunaj_sve_zagrade(vector<int> dostupni_brojevi, Kalkulator& k) {
	int broj_operacija = dostupni_brojevi.size() + 1;
	int min = 0;
	int max = 3;
	int range = max - min + 1;
	int num;
	sort(dostupni_brojevi.begin(), dostupni_brojevi.end());
	//za svaku permutaciju brojeva
	do {
		//za svaku varijaciju operacija
		string indexi = "";
		for (int i = 0; i < dostupni_brojevi.size() + 1; i++) {
			indexi += "0";
		}
		do {
			sadrzi_zagrade = false;
			racunaj = true;
			visak_zagrada = 0;
			stringic = "";
			//proverimo da li su zagrade smisleno dodate tj da li sve imaju para
			for (int i = 0; i < dostupni_brojevi.size() + 1; i++) {
				if (indexi[i] == '4') {
					if (!sadrzi_zagrade) {
						sadrzi_zagrade = true;
					}
					visak_zagrada--;
				}
				else if (indexi[i] == '5') {
					//ovo znaci da se prvo pojavila ')' pa tek posle '('
					if (!sadrzi_zagrade) {
						racunaj = false;
					}
					visak_zagrada++;
					//ovo znaci da je samo jedan broj u zagradi, ne znaci nam nista
					if (i > 0 && indexi[i - 1] == '4') {
						racunaj = false;
					}
					//ovo znaci da se u zagradi nalazi mnozenje ili deljenje koje svakako ima prioritet
					if (i > 1) {
						if ((indexi[i - 2] == '4'&&indexi[i - 1] == '2') || (indexi[i - 2] == '4'&&indexi[i - 1] == '3')) {
							racunaj = false;
						}
					}
				}
			}
			//ako zagrade nemaju parove ili nema zagrade ne racunamo
			if (visak_zagrada != 0 || !sadrzi_zagrade) {
				racunaj = false;
			}
			if (racunaj) {
				//konstruisemo izraz
				for (int i = 0; i < dostupni_brojevi.size(); i++) {
					//ako se ispred prvog broja nalazi ( dodajemo je ostale operacije ne
					if (i == 0 && (int(indexi[i]) - 48) == 4) {
						stringic += operacije_zagrade[int(indexi[i]) - 48];
						visak_zagrada -= 1;
					}
					stringic += to_string(dostupni_brojevi[i]);
					//ako smo na poslednjem broju
					if (i == dostupni_brojevi.size() - 1) {
						//dodajemo operaciju iza samo ako je ')'
						if (int(indexi[i + 1]) - 48 == 5) {
							stringic += operacije_zagrade[int(indexi[i + 1]) - 48];
							visak_zagrada += 1;
						}
					}
					//inace sve dodajemo
					else {
						stringic += operacije_zagrade[int(indexi[i + 1]) - 48];
						if (int(indexi[i + 1]) - 48 == 5) {
							visak_zagrada += 1;
						}
						if (int(indexi[i + 1]) - 48 == 4) {
							visak_zagrada -= 1;
						}
					}
				}
				dobijeni_broj = k.izracunaj(stringic);
				if (dobijeni_broj == k.trazeno) {
					return stringic;
				}
			}
		} while (next_variation<double>(indexi.begin(), indexi.end(), '6', '0'));
	} while (next_permutation(dostupni_brojevi.begin(), dostupni_brojevi.end()));
	return "";
}

string operacije = "+-*/";
string zagrade = "()";
//funkcija koja od vektora sa brojevima koji se koriste proverava sve permutacije
//i sve varijante operanada medju njima
string izracunaj_sve(vector<int> dostupni_brojevi, Kalkulator& k) {
	int broj_operacija = dostupni_brojevi.size() - 1;
	int min = 0;
	int max = 3;
	int range = max - min + 1;
	int num;
	int dobijeni_broj;
	sort(dostupni_brojevi.begin(), dostupni_brojevi.end());
	//za svaku permutaciju brojeva
	do {
		//za svaku varijaciju operacija
		string indexi = "";
		for (int i = 0; i < dostupni_brojevi.size() - 1; i++) {
			indexi += "0";
		}
		do {
			stringic = "";
			for (int i = 0; i < dostupni_brojevi.size(); i++) {
				stringic += to_string(dostupni_brojevi[i]);
				if (i != dostupni_brojevi.size() - 1) {
					stringic += operacije[int(indexi[i]) - 48];
				}
			}
			dobijeni_broj = k.izracunaj(stringic);
			if (dobijeni_broj == k.trazeno) {
				return stringic;
			}
		} while (next_variation<double>(indexi.begin(), indexi.end(), '4', '0'));
	} while (next_permutation(dostupni_brojevi.begin(), dostupni_brojevi.end()));
	return "";
}

string izracunaj(int ponudjeni_brojevi[6], string trazeni_broj, Kalkulator& kalkulator) {
	string resenje = "";
	vector<int>dostupni_brojevi_vektor;
	for (int i = 0; i < 6; i++) {
		dostupni_brojevi_vektor.push_back(ponudjeni_brojevi[i]);
	}
	//proveravamo resenja sa 5 i manje brojeva u sebi
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
		//ova funkcija ispituje sve moguce permutacije ovih brojeva (ispituje i sve varijante operanada)
		string izraz = izracunaj_sve(dostupni_brojevi_vektor, kalkulator);
		int eliminisani_broj4 = 9999;
		if (kalkulator.izracunaj(izraz) == stoi(trazeni_broj)) {
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
				string izraz = izracunaj_sve(dostupni_brojevi_vektor, kalkulator);
				int eliminisani_broj3 = 9999;
				if (kalkulator.izracunaj(izraz) == stoi(trazeni_broj)) {
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
						string izraz = izracunaj_sve(dostupni_brojevi_vektor, kalkulator);
						int eliminisani_broj2 = 9999;
						if (kalkulator.izracunaj(izraz) == stoi(trazeni_broj)) {
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
								string izraz = izracunaj_sve(dostupni_brojevi_vektor, kalkulator);
								if (kalkulator.izracunaj(izraz) == stoi(trazeni_broj)) {
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
	//proverimo kombinacije sa 6 brojeva
	if (resenje == "") {
		string izraz = izracunaj_sve(dostupni_brojevi_vektor, kalkulator);
		if (kalkulator.izracunaj(izraz) == stoi(trazeni_broj)) {
			resenje += izraz;
		}
	}
	if (resenje == "") {
		//proveravamo resenja sa 5 i manje brojeva u sebi
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
			//ova funkcija ispituje sve moguce permutacije ovih brojeva (ispituje i sve varijante operanada)
			string izraz = izracunaj_sve_zagrade(dostupni_brojevi_vektor, kalkulator);
			int eliminisani_broj4 = 9999;
			if (kalkulator.izracunaj(izraz) == stoi(trazeni_broj)) {
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
					string izraz = izracunaj_sve_zagrade(dostupni_brojevi_vektor, kalkulator);
					int eliminisani_broj3 = 9999;
					if (kalkulator.izracunaj(izraz) == stoi(trazeni_broj)) {
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
							string izraz = izracunaj_sve_zagrade(dostupni_brojevi_vektor, kalkulator);
							int eliminisani_broj2 = 9999;
							if (kalkulator.izracunaj(izraz) == stoi(trazeni_broj)) {
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
									string izraz = izracunaj_sve_zagrade(dostupni_brojevi_vektor, kalkulator);
									if (kalkulator.izracunaj(izraz) == stoi(trazeni_broj)) {
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
		//proverimo kombinacije sa 6 brojeva
		if (resenje == "") {
			string izraz = izracunaj_sve_zagrade(dostupni_brojevi_vektor, kalkulator);
			if (kalkulator.izracunaj(izraz) == stoi(trazeni_broj)) {
				resenje += izraz;
			}
		}
	}
	return resenje;
}

int main() {
	//upuststva za igrace
	cout << "Dobro dosli u igru moj broj!" << endl;
	cout << "Igra se igra u nekoliko rundi, u prvoj je prvi igrac igrac A, u drugoj igrac B i tako naizmenicno" << endl;
	cout << "Potrebno je sastaviti izraz sa vrednoscu tacno tj sto blize trazenom broju." << endl;
	cout << "Pobednik runde je igrac koji ima izraz blize vrednost trazenoj." << endl;
	cout << "Ukoliko oba igraca dodju do istog resenja pobednik je onaj igrac koji je prvi igrao u toj rundi." << endl;
	cout << "Pobednik je igrac koji pobedi u vise rundi." << endl;
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
	fajl_rezultati.close();
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
		Kalkulator kalkulator = Kalkulator(stoi(trazeni_broj), ponudjeni_brojevi);

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
				vrednostA = kalkulator.izracunaj(unos_igracA);
				if (vrednostA != 999999999) {
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
					vrednostB = stoi(trazeni_broj);
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
				}
				//racunamo vrednost izraza
				vrednostB = kalkulator.izracunaj(unos_igracB);
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
				vrednostB = kalkulator.izracunaj(unos_igracB);
				if (vrednostB != 999999999) {
					break;
				}
				else {
					cout << "Vas izraz nije validan. Pokusajte opet! " << endl;
				}
			}
			while (true)
			{
				if (vrednostB == 5555555) {
					vrednostA = stoi(trazeni_broj);
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
				}
				//racunamo vrednost izraza
				vrednostA = kalkulator.izracunaj(unos_igracA);
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
		if (vrednostA == stoi(trazeni_broj) && vrednostB != 5555555) {
			resenje += unos_igracA;
		}
		else if (vrednostB == stoi(trazeni_broj) && vrednostA != 5555555) {
			resenje += unos_igracB;
		}
		else {
			resenje = izracunaj(ponudjeni_brojevi, trazeni_broj, kalkulator);
		}
		int vrednostK;
		if (resenje != "") {
			vrednostK = kalkulator.izracunaj(resenje);
		}
		else {
			vrednostK = kalkulator.najblize;
		}
		cout << "Izraz koji je kompjuter pronasao je: " << kalkulator.najblizi_izraz << endl;
		cout << "Vrednost ovog izraza je " << vrednostK << endl;

		//provera ko je blizi i upisivanje u fajl
		string pobednik = "";
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
		ofstream fajl_rezultati("Rezultati.txt", ios::app);
		cout << "Pobednik ove runde je " << pobednik << endl << endl << endl;
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
	fajl_rezultati << upis;
	fajl_rezultati.close();

	//keep_window_open();
	//ovo iznad ne bih da obrisem jer nekad ov sysem("pause") samo odluci da ne radi 10 min pa tad koristim keep window open
	system("pause");
	exit(0);
}