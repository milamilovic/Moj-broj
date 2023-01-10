#include "..\Project1\Calculator.cpp"

using namespace std;

int main() {
	cout << "------------------------------TESTOVI------------------------------" << endl << endl;
	//testiranje modula za sracunavanje
	//treba da damo izraz kao ulaz i vidimo da li daje ocekivano resenje
	cout << "          -------TESTIRANJE MODULA ZA SRACUNAVANJE-------          " << endl << endl;
	int broj_prodjenih_testova = 0;
	int ukupan_broj_testova = 0;
	//prvo testiramo koriscenje integer vrednosti
	vector<string> izrazi;
	izrazi.push_back("3+2+9+7+16+88");
	izrazi.push_back("18/9+7");
	izrazi.push_back("(3+2)*5/5");
	izrazi.push_back("32/6");
	izrazi.push_back("9*25+7");
	izrazi.push_back("42/6*7");
	izrazi.push_back("1");
	izrazi.push_back("121");
	izrazi.push_back("6*7");
	double ponudjeni_brojevi[9][6] = { { 3, 2, 9, 7, 16, 88 },
									{ 9, 7, 5, 3, 18, 55 },
									{ 2, 3, 5, 5, 67, 88 },
									{ 2, 4, 6, 8, 32, 44 },
									{ 3, 5, 7, 9, 25, 50 },
									{ 6, 7, 8, 9, 42, 42 },
									{ 1, 2, 1, 2, 12, 21 },
									{ 1, 2, 1, 2, 12, 21 },
									{ 1, 2, 3, 4, 12, 22 } };
	vector<string> ocekivana_resenja;
	ocekivana_resenja.push_back("125");
	ocekivana_resenja.push_back("9");
	ocekivana_resenja.push_back("5");
	ocekivana_resenja.push_back("5555555");
	ocekivana_resenja.push_back("232");
	ocekivana_resenja.push_back("49");
	ocekivana_resenja.push_back("1");
	ocekivana_resenja.push_back("999999999");
	ocekivana_resenja.push_back("999999999");
	cout << "Testiranje celobrojnih vrednosti: " << endl;
	for (int i = 1; i <= int(izrazi.size()); i++) {
		ukupan_broj_testova++;
		cout << "TEST 1." << i << endl;
		cout << "Izraz: " << izrazi.at(i - 1) << endl;
		cout << "Ocekivana vrednost: " << ocekivana_resenja.at(i - 1) << endl;
		int resenje = iskalkulisi(izrazi.at(i-1), ponudjeni_brojevi[i-1], true);
		cout << "Dobijeno resenje: " << resenje << endl;
		if (stoi(ocekivana_resenja.at(i - 1)) == resenje) {
			cout << "Test " << i << " je uspesan." << endl << endl;
			broj_prodjenih_testova++;
		}
		else {
			cout << "Test " << i << " nije uspesan." << endl << endl;
		}
	}

	//testiranje double  vrednosti
	izrazi.clear();
	izrazi.push_back("9.2/2.5");
	izrazi.push_back("6.1*8.4");
	izrazi.push_back("17.0/(3.1+5.4)");
	double ponudjeni_brojevi_d[3][6] = {{ 9.2, 2.5, 9.1, 7.6, 16.0, 88.2 },
									{ 6.1, 8.4, 5.5, 3.0, 18.3, 55.2 },
									{ 2.1, 3.1, 5.4, 5.0, 17.0, 88 }};
	ocekivana_resenja.clear();
	ocekivana_resenja.push_back("3.68");
	ocekivana_resenja.push_back("51.24");
	ocekivana_resenja.push_back("2");
	cout << endl << "Testiranje double vrednosti: " << endl;

	for (int i = 1; i <= int(izrazi.size()); i++) {
		ukupan_broj_testova++;
		cout << "TEST 2." << i << endl;
		cout << "Izraz: " << izrazi.at(i - 1) << endl;
		cout << "Ocekivana vrednost: " << ocekivana_resenja.at(i - 1) << endl;
		double resenje = iskalkulisi(izrazi.at(i - 1), ponudjeni_brojevi_d[i - 1], false);
		cout << "Dobijeno resenje: " << resenje << endl;
		//postoji mala tolerancija zbog fizickih ogranicenja racunara
		if (abs(stod(ocekivana_resenja.at(i - 1)) - resenje)<0.01) {
			cout << "Test " << i << " je uspesan." << endl << endl;
			broj_prodjenih_testova++;
		}
		else {
			cout << "Test " << i << " nije uspesan." << endl << endl;
		}
	}
	cout << endl << "Od ukupno " << ukupan_broj_testova << " testova uspesno je proslo " << broj_prodjenih_testova << endl << endl;
	
	
	//testiranje modula za pronalazenje resenja
	//podrazumeva da sracunavanje radi
	//treba da damo ulazne brojeve a on treba da nadje zeljeno resenje
	cout << "          ---TESTIRANJE MODULA ZA PRONALAZENJE RESENJA---          " << endl << endl;
	system("pause");
	exit(0);
}