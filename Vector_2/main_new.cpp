
#include "Studentas.h"asdasdadsasdasdad
int main()
{
	int k;
	int sk = 0;
	vector <Studentas> Eiles, geri_paz;
	Studentas a;
	cout << "Norite gauti studentu mediana(1) ar Galutini pazymi(2)" << endl;

	while (!(cin >> sk) || (sk != 1 && sk != 2))
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "ERORR: Ivesti galima tik 1 arba 2" << endl;

	}


	for (int i = 0; i < 5; i++) {
		cout << "--------------------------" << endl;
		cout << "kiek norite eiluciu faile?" << endl;
		cin >> k;
		a.KurtiFaila(5, k);
		a.Nuskaitymas(k, sk, Eiles, 5);
		a.rusiavimas(Eiles, geri_paz, k);
		a.isvedimas(Eiles, geri_paz, k);

		Eiles.clear();
		geri_paz.clear();
	}


}
