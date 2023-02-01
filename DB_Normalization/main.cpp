#include "baza.hpp"

int main()
{
	int odabir;
	int normalizacija;
	baza b;
	string fileName = "Primjeri.txt";
	b.readFromFile("Primjeri.txt");

	cout << "ZADATCI: " << endl;
	b.printZadatci();
	cout << endl << endl;
	cout << "Koju tablicu zelite odabrati: " << endl;
	cin >> odabir;

	if ((odabir > b.counter) || (isalpha(odabir)) || (odabir == 0))
	{
		cout << "Pogresan unos!" << endl;
		exit(-1);
	}
	system("cls");
	b.odabirZadatka(odabir);
	cout << "R = " << b.R << endl;
	cout << "F = { " << b.F << " }" << endl << endl;

	cout << "Unesite: " << endl << "1 - Normalizacija u 3.NF" << endl << "2 - Normalizacija u BCNF" << endl;
	cin >> normalizacija;
	b.odabirNormalizacije(normalizacija);
}