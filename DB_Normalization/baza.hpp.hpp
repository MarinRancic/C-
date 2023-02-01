#ifndef H_BAZA
#define H_BAZA

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;


class baza
{
public:
	int counter = 0;

	vector <string> tablice;
	vector <string> relacije;
	vector <string> ro;
	vector <char> ograda;
	vector<string> sveKombinacije;
	vector<string> Rlijeva;
	vector<string> Rdesna;
	vector<string> kandidatiKljuca;

	string ogradaNova;
	string bufferTablice;
	string bufferRelacije;
	string sigurniKljuc;
	string sviAtributi;
	string noviR;
	

	string R;
	string F;
	string K;

	void readFromFile(string);
	void printZadatci();
	void odabirZadatka(int);
	void odabirNormalizacije(int);
	void pronalazakKljuca();
	void pronalazakSigurnogKljuca();
	void trecaNormalnaForma();
	void pronalazakSvihAtributa();
	void tablicaBezSigurnogKljuca();
	void ogradaConvert();
	void pronalazakSvihKombinacija(string, int, string);
	void lijevaDesna();
	void kandidatiZaKljuc();
};





#endif