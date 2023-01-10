#include "funkcije.h"
#include "Kalkulator.cpp"


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
string izracunaj_sve_zagrade(vector<int> dostupni_brojevi, Kalkulator<int>& k) {
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
				dobijeni_broj = k.izracunaj_k(stringic);
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
string izracunaj_sve(vector<int> dostupni_brojevi, Kalkulator<int>& k) {
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
			dobijeni_broj = k.izracunaj_k(stringic);
			if (dobijeni_broj == k.trazeno) {
				return stringic;
			}
		} while (next_variation<double>(indexi.begin(), indexi.end(), '4', '0'));
	} while (next_permutation(dostupni_brojevi.begin(), dostupni_brojevi.end()));
	return "";
}

string izracunaj(int ponudjeni_brojevi[6], string trazeni_broj, Kalkulator<int>& kalkulator) {
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
		if (kalkulator.izracunaj_k(izraz) == stoi(trazeni_broj)) {
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
				if (kalkulator.izracunaj_k(izraz) == stoi(trazeni_broj)) {
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
						if (kalkulator.izracunaj_k(izraz) == stoi(trazeni_broj)) {
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
								if (kalkulator.izracunaj_k(izraz) == stoi(trazeni_broj)) {
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
		if (kalkulator.izracunaj_k(izraz) == stoi(trazeni_broj)) {
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
			if (kalkulator.izracunaj_k(izraz) == stoi(trazeni_broj)) {
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
					if (kalkulator.izracunaj_k(izraz) == stoi(trazeni_broj)) {
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
							if (kalkulator.izracunaj_k(izraz) == stoi(trazeni_broj)) {
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
									if (kalkulator.izracunaj_k(izraz) == stoi(trazeni_broj)) {
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
			if (kalkulator.izracunaj_k(izraz) == stoi(trazeni_broj)) {
				resenje += izraz;
			}
		}
	}
	return resenje;
}





//funkcija koja od vektora sa brojevima koji se koriste proverava sve permutacije
//i sve varijante operanada medju njima
//verzija za double
double dobijeni_broj_d = 0;
string izracunaj_sve_zagrade_d(vector<double> dostupni_brojevi, Kalkulator<double>& k) {
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
					//broj svakako dodajemo
					string za_dodati = to_string(dostupni_brojevi[i]);
					if (dostupni_brojevi[i] >= 10) {
						for (int j = 0; j < 4; j++) {
							stringic += za_dodati[j];
						}
					}
					else {
						for (int j = 0; j < 3; j++) {
							stringic += za_dodati[j];
						}
					}
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
				dobijeni_broj_d = k.izracunaj_k(stringic);
				if (dobijeni_broj_d == k.trazeno) {
					return stringic;
				}
			}
		} while (next_variation<double>(indexi.begin(), indexi.end(), '6', '0'));
	} while (next_permutation(dostupni_brojevi.begin(), dostupni_brojevi.end()));
	return "";
}

//funkcija koja od vektora sa brojevima koji se koriste proverava sve permutacije
//i sve varijante operanada medju njima
//verzija za double
string izracunaj_sve_d(vector<double> dostupni_brojevi, Kalkulator<double>& k) {
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
				string za_dodati = to_string(dostupni_brojevi[i]);
				if (dostupni_brojevi[i] >= 10) {
					for (int j = 0; j < 4; j++) {
						stringic += za_dodati[j];
					}
				}
				else {
					for (int j = 0; j < 3; j++) {
						stringic += za_dodati[j];
					}
				}
				if (i != dostupni_brojevi.size() - 1) {
					stringic += operacije[int(indexi[i]) - 48];
				}
			}
			dobijeni_broj_d = k.izracunaj_k(stringic);
			if (dobijeni_broj_d == k.trazeno) {
				return stringic;
			}
		} while (next_variation<double>(indexi.begin(), indexi.end(), '4', '0'));
	} while (next_permutation(dostupni_brojevi.begin(), dostupni_brojevi.end()));
	return "";
}

string izracunaj_d(double ponudjeni_brojevi[6], string trazeni_broj, Kalkulator<double> & kalkulator) {
	string resenje = "";
	vector<double>dostupni_brojevi_vektor;
	for (int i = 0; i < 6; i++) {
		dostupni_brojevi_vektor.push_back(ponudjeni_brojevi[i]);
	}
	//proveravamo resenja sa 5 i manje brojeva u sebi
	double eliminisani_broj5 = 9999;
	for (int i = 0; i < 6; i++) {
		//proverimo da li smo u prethodnoj iteraciji nasli resenje
		if (resenje != "") {
			break;
		}
		if (eliminisani_broj5 != 9999) {
			dostupni_brojevi_vektor.insert(dostupni_brojevi_vektor.begin() + i - 1, eliminisani_broj5);
		}
		//ovde proverimo da li je jedan od ponudjenih brojeva ujedno i resenje
		if (ponudjeni_brojevi[i] == stod(trazeni_broj)) {
			resenje += to_string(ponudjeni_brojevi[i]);
			break;
		}
		eliminisani_broj5 = dostupni_brojevi_vektor[i];
		dostupni_brojevi_vektor.erase(dostupni_brojevi_vektor.begin() + i);
		//dakle sad ispitamo kombinacije sa 5 brojeva
		//ova funkcija ispituje sve moguce permutacije ovih brojeva (ispituje i sve varijante operanada)
		string izraz = izracunaj_sve_d(dostupni_brojevi_vektor, kalkulator);
		double eliminisani_broj4 = 9999;
		if (kalkulator.izracunaj_k(izraz) == stod(trazeni_broj)) {
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
				string izraz = izracunaj_sve_d(dostupni_brojevi_vektor, kalkulator);
				double eliminisani_broj3 = 9999;
				if (kalkulator.izracunaj_k(izraz) == stod(trazeni_broj)) {
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
						string izraz = izracunaj_sve_d(dostupni_brojevi_vektor, kalkulator);
						double eliminisani_broj2 = 9999;
						if (kalkulator.izracunaj_k(izraz) == stod(trazeni_broj)) {
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
								string izraz = izracunaj_sve_d(dostupni_brojevi_vektor, kalkulator);
								if (kalkulator.izracunaj_k(izraz) == stod(trazeni_broj)) {
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
		string izraz = izracunaj_sve_d(dostupni_brojevi_vektor, kalkulator);
		if (kalkulator.izracunaj_k(izraz) == stod(trazeni_broj)) {
			resenje += izraz;
		}
	}
	if (resenje == "") {
		//proveravamo resenja sa 5 i manje brojeva u sebi
		double eliminisani_broj5 = 9999;
		for (int i = 0; i < 6; i++) {
			//proverimo da li smo u prethodnoj iteraciji nasli resenje
			if (resenje != "") {
				break;
			}
			if (eliminisani_broj5 != 9999) {
				dostupni_brojevi_vektor.insert(dostupni_brojevi_vektor.begin() + i - 1, eliminisani_broj5);
			}
			//ovde proverimo da li je jedan od ponudjenih brojeva ujedno i resenje
			if (ponudjeni_brojevi[i] == stod(trazeni_broj)) {
				resenje += to_string(ponudjeni_brojevi[i]);
				break;
			}
			eliminisani_broj5 = dostupni_brojevi_vektor[i];
			dostupni_brojevi_vektor.erase(dostupni_brojevi_vektor.begin() + i);
			//dakle sad ispitamo kombinacije sa 5 brojeva
			//ova funkcija ispituje sve moguce permutacije ovih brojeva (ispituje i sve varijante operanada)
			string izraz = izracunaj_sve_zagrade_d(dostupni_brojevi_vektor, kalkulator);
			double eliminisani_broj4 = 9999;
			if (kalkulator.izracunaj_k(izraz) == stod(trazeni_broj)) {
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
					string izraz = izracunaj_sve_zagrade_d(dostupni_brojevi_vektor, kalkulator);
					double eliminisani_broj3 = 9999;
					if (kalkulator.izracunaj_k(izraz) == stod(trazeni_broj)) {
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
							string izraz = izracunaj_sve_zagrade_d(dostupni_brojevi_vektor, kalkulator);
							double eliminisani_broj2 = 9999;
							if (kalkulator.izracunaj_k(izraz) == stod(trazeni_broj)) {
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
									string izraz = izracunaj_sve_zagrade_d(dostupni_brojevi_vektor, kalkulator);
									if (kalkulator.izracunaj_k(izraz) == stod(trazeni_broj)) {
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
			string izraz = izracunaj_sve_zagrade_d(dostupni_brojevi_vektor, kalkulator);
			if (kalkulator.izracunaj_k(izraz) == stod(trazeni_broj)) {
				resenje += izraz;
			}
		}
	}
	return resenje;
}