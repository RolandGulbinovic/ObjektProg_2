﻿#include "mybib.h"

void KurtiFaila(int, int);
void nuskaitymas(int, int, vector<studentas>&, int);
void isvedimas(vector<studentas>&, vector<studentas>&,  int);
void rusiavimas(vector<studentas>&, vector<studentas>&, int);
bool compareByGalut(const studentas& pirmas, const studentas& antras);

void KurtiFaila(int nd, int studentai) {

	auto start = high_resolution_clock::now();
	string  ss = to_string(studentai);
	string fileName = "file" + ss;

	ofstream file;
	file.open(fileName + ".txt");
	for (int i = 0; i < studentai; i++) {
		file << "Vardas" + to_string(i) << " " << "Pavarde" + to_string(i);
		for (int i = 0; i < nd; i++)
			file << " " << rand() % 11;
		file << " " << rand() % 11;
		file << "\n";
	}
	file.close();
	duration<double> elapsed_seconds = high_resolution_clock::now() - start;
	cout << "Failo sukurimas uztruko: " << elapsed_seconds.count() << "s" << endl;
}


void nuskaitymas(int studentai, int sk, vector<studentas>& Eiles, int n)
{
	auto start = high_resolution_clock::now();
	ifstream file;
	vector <int> ndf;

	string  ss = to_string(studentai);
	string fileName = "file" + ss;

	ndf.reserve(1);

	file.open("C:/Users/rolan/Desktop/0.4.1/" + fileName + ".txt");

	studentas laik;

	while (file >> laik.Vardas >> laik.Pav)
	{
		laik.GP = 0;
		laik.Med = 0;
		for (int i = 0; i < n; i++) {
			file >> laik.nd;
			laik.GP = laik.nd + laik.GP;
		}
		file >> laik.egz;

		if (sk == 2) {
			if (n == 0)
				laik.GP = 0; //jei n=0 tai kad nedalintu is 0
			else {
				laik.GP = laik.GP / (float)n;
				laik.GP = 0.4 * laik.GP + 0.6 * (float)laik.egz; //GP skaiciavumas
			}
		}
		else {
			laik.GP = 0;
			ndf.reserve(n + 1); // rezervuoju daugiau vietos nes kaip paskutini elementa pridedu egz

			ndf[ndf.size() - 1] = laik.egz;

			sort(ndf.begin(), ndf.end());

			if (ndf.size() % 2 != 0)
				laik.Med = (float)ndf[(ndf.size()) / 2];

			laik.GP = (float)(ndf[ndf.size() / 2] + ndf[(ndf.size() + 1) / 2]) / (float)2.0;
		}
		Eiles.push_back(laik);
	}

	duration<double> elapsed_seconds = high_resolution_clock::now() - start;
	cout << "Skaitymas nuo failo uztruko: " << elapsed_seconds.count() << "s." << endl;
}

void rusiavimas(vector<studentas>& Eiles, vector<studentas>& geri_paz, int studentai)
{
	auto start = high_resolution_clock::now();

	sort(Eiles.begin(), Eiles.end(), compareByGalut);


	auto result = std::remove_if(Eiles.begin(), Eiles.end(), [](const studentas& p)
		{
			return p.GP < 5;
		});

	geri_paz.insert(geri_paz.begin(), result, Eiles.end());

	Eiles.erase(result, Eiles.end());


	duration<double> elapsed_seconds = high_resolution_clock::now() - start;
	cout << "Rusiavimas i 2 vektorius uztruko: " << elapsed_seconds.count() << "s." << endl;
}

void isvedimas(vector<studentas>& Eiles, vector<studentas>& geri_paz,  int studentai) {
	auto start = high_resolution_clock::now();
	ofstream blogas,geras;
	blogas.open("blogas_paz.txt");
	for (auto tt : geri_paz) { //isvedu du naujus vektorius i failus
		blogas << tt.Vardas << " " << tt.Pav << " " << fixed << setprecision(2) << tt.GP;
		blogas << '\n';
	}
	blogas.close();

	geras.open("geras_paz.txt");
	for (auto tt : Eiles) { //isvedu du naujus vektorius i failus
		geras << tt.Vardas << " " << tt.Pav << " " << fixed << setprecision(2) << tt.GP;
		geras << '\n';
	}
	geras.close();
	duration<double> elapsed_seconds = high_resolution_clock::now() - start;
	cout << "Isvedimas i failus uztruko: " << elapsed_seconds.count() << "s" << endl;

}

bool compareByGalut(const studentas& pirmas, const studentas& antras) {
	return pirmas.GP > antras.GP;
}

bool compareByGalut(const studentas& pirmas, const studentas& antras) {
	return pirmas.GP > antras.GP;
}