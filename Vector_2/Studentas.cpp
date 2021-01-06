

#include "Studentas.h"
#include <iostream>

void Studentas::KurtiFaila(int nd, int studentai) {

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

void Studentas::Nuskaitymas(int studentai, int sk, vector<Studentas>& Eiles, int n)
{
	auto start = high_resolution_clock::now();
	ifstream file;
	vector <int> ndf;

	string vard, pav;
	int nd, egz;
	string  ss = to_string(studentai);
	string fileName = "file" + ss;

	ndf.reserve(1);

	file.open(fileName + ".txt");

	Studentas laik;

	while (file >> vard >> pav)
	{
		laik.setVardas(vard);
		laik.setPav(pav);
		laik.setGp(0);
		float GP = 0;

		for (int i = 0; i < n; i++) {
			file >> nd;
			GP = nd + GP;
		}
		file >> egz;
		laik.setEgz(egz);
		
		if (sk == 2) {
			if (n == 0)
				laik.setGp(0); //jei n=0 tai kad nedalintu is 0
			else {
				GP = GP / (float)n;
				GP = 0.4 * GP + 0.6 * (float)egz; //GP skaiciavumas
				laik.setGp(GP);
			}
		}
		else {
			laik.setGp(0);
			ndf.reserve(n + 1); // rezervuoju daugiau vietos nes kaip paskutini elementa pridedu egz

			ndf[ndf.size() - 1] = laik.getEgz();

			sort(ndf.begin(), ndf.end());

			if (ndf.size() % 2 != 0) {
				GP = (float)ndf[(ndf.size()) / 2];
				laik.setGp(GP);
			}

			GP = (float)(ndf[ndf.size() / 2] + ndf[(ndf.size() + 1) / 2]) / (float)2.0;
			laik.setGp(GP);
		}
		Eiles.push_back(laik);

	}

	duration<double> elapsed_seconds = high_resolution_clock::now() - start;
	cout << "Skaitymas nuo failo uztruko: " << elapsed_seconds.count() << "s." << endl;
}
void Studentas::isvedimas(vector<Studentas>& Eiles, vector<Studentas>& geri_paz, int studentai) {
	auto start = high_resolution_clock::now();
	ofstream blogas, geras;
	blogas.open("blogas_paz.txt");
	for (auto tt : geri_paz) { //isvedu du naujus vektorius i failus
		blogas << tt.getVardas() << " " << tt.getPav() << " " << fixed << setprecision(2) << tt.getGp();
		blogas << '\n';
	}
	blogas.close();

	geras.open("geras_paz.txt");
	for (auto tt : Eiles) { //isvedu du naujus vektorius i failus
		geras << tt.getVardas() << " " << tt.getPav() << " " << fixed << setprecision(2) << tt.getGp();
		geras << '\n';
	}
	geras.close();
	duration<double> elapsed_seconds = high_resolution_clock::now() - start;
	cout << "Isvedimas i failus uztruko: " << elapsed_seconds.count() << "s" << endl;

}
void Studentas::rusiavimas(vector<Studentas>& Eiles, vector<Studentas>& geri_paz, int studentai)
{
	auto start = high_resolution_clock::now();

	sort(Eiles.begin(), Eiles.end(), compareByGalut);

	auto result = std::remove_if(Eiles.begin(), Eiles.end(), [](Studentas& p)
		{
			return p.getGp() < 5;
		});

	geri_paz.insert(geri_paz.begin(), result, Eiles.end());

	Eiles.erase(result, Eiles.end());


	duration<double> elapsed_seconds = high_resolution_clock::now() - start;
	cout << "Rusiavimas i 2 vektorius uztruko: " << elapsed_seconds.count() << "s." << endl;
}
bool compareByGalut(Studentas& pirmas, Studentas& antras) {
	return (pirmas.getGp() > antras.getGp());
}
