#include "baza.hpp"

void baza::readFromFile(string name)
{
	ifstream file(name);
	if (!file.is_open())
	{
		cout << "File kojeg pokusajete otvoriti ne postoji!";
		exit(-1);
	}

	while (file >> bufferTablice >> bufferRelacije)
	{
		tablice.push_back(bufferTablice);
		relacije.push_back(bufferRelacije);
		counter++;
	}
}

void baza::printZadatci()
{
	for (int i = 0; i < tablice.size() || i < relacije.size(); ++i)
	{
		cout << i + 1 << ". " << tablice[i] << endl;
		cout << relacije[i] << endl << endl;
	}
}

void baza::odabirZadatka(int n)
{
	R = tablice[n - 1];
	F = relacije[n - 1];
}

void baza::odabirNormalizacije(int n)
{
	if (n == 1)
	{
		trecaNormalnaForma();
	}
	else if (n == 2)
	{
		"BCNF";
	}
	else
	{
		cout << "Pogresan unos!";
		exit(-1);
	}
}

void baza::trecaNormalnaForma()
{
	pronalazakKljuca();
	int brojac = 0;
	int i = 0;
	int j = 0;
	string buffer;

	while (i < F.length())
	{
		while ((F[i] != ',') && (F[i] != '\0'))
		{
			if (isalpha(F[i]))
			{
				buffer.push_back(F[i]);
			}

			i++;
		}

		sort(buffer.begin(), buffer.end());
		
		if (ro.empty())
		{
			ro.push_back(buffer);
		}
		else
		{
			for (int k = 0; k < ro.size(); ++k)
			{
				if (ro[k].compare(0, buffer.length(), buffer)) // ako su isti nece uc u if
				{
					brojac++;
				}
			}
		}

		if (ro.size() == brojac)
		{
			ro.push_back(buffer);
		}

		brojac = 0;
		buffer = "";
		i++;

	}

	for (int i = 0; i < ro.size(); ++i)
	{
		if (ro[i].compare(0, K.size(), K))
		{
			brojac++;
		}
	}

	if (ro.size() == brojac)
	{
		ro.push_back(K);
	}

	cout << "ro = { ";
	for (int k = 0; k < ro.size(); ++k)
	{
		cout << ro[k];
		if (k != ro.size() - 1)
		{
			cout << ", ";
		}
	}
	cout << " }" << endl;
}

void baza::pronalazakKljuca()
{
	for (int i = 0; i < F.size(); ++i)
	{
		if (F[i] != '-')
		{
			if (F[i] != ' ')
			{
				ograda.push_back(F[i]);
			}
		}
		else
		{
			while (F[i] != ',' && i != F.size() - 1)
			{
				i++;
			}
		}
	}

	sort(ograda.begin(), ograda.end());
	ograda.erase(unique(ograda.begin(), ograda.end()), ograda.end());

	cout << "Ograda: ";
	for (int i = 0; i < ograda.size();++i)
	{
		cout << ograda[i];
	}
	cout << endl;

	pronalazakSigurnogKljuca();
	tablicaBezSigurnogKljuca();
	ogradaConvert();
	//pronalazakSvihKombinacija(ogradaNova, -1, "");
	lijevaDesna();
	kandidatiZaKljuc();
}

void baza::pronalazakSigurnogKljuca()
{
	pronalazakSvihAtributa();
	int brojac = 0;
	for (int i = 0; i < R.size(); ++i)
	{
		for (int j = 0; j < sviAtributi.size(); ++j)
		{
			if (R[i] == sviAtributi[j])
			{
				brojac++;
			}
		}
		if (brojac == 0)
		{
			sigurniKljuc.push_back(R[i]);
		}
		brojac = 0;
	}

	for (int i = 0; i < sigurniKljuc.size(); ++i)
	{
		cout << sigurniKljuc[i];
	}
	cout << endl;
}

void baza::pronalazakSvihAtributa()
{
	for (int i = 0; i < R.size(); ++i)
	{
		if (isalpha(R[i]))
		{
			sviAtributi.push_back(R[i]);
		}
	}
}

void baza::tablicaBezSigurnogKljuca()
{
	if (sigurniKljuc.size() == 0)
	{
		noviR = R;
	}

	else
	{
		int brojac = 0;
		for (int i = 0; i < R.size(); ++i)
		{
			for (int j = 0; j < sigurniKljuc.size(); ++j)
			{
				if (R[i] == sigurniKljuc[j])
				{
					brojac++;
				}
			}
			if (brojac == 0)
			{
				noviR.push_back(R[i]);
			}
			brojac = 0;
		}
	}

	cout << "Tablica bez sigurnog kljuca: ";
	for (int i = 0; i < noviR.size(); ++i)
	{
		cout << noviR[i];
	}
	cout << endl;
}

void baza::pronalazakSvihKombinacija(string str, int index = -1, string curr = "")
{
	
	int n = str.length();
	//cout << n << "\t" << index << endl;
	//cout << sveKombinacije.size();
	//cout << endl;
	if (index == n)
	{
		return ;
	}
	sveKombinacije.push_back(curr);


	for (int i = index + 1; i < n; i++) 
	{
		curr += str[i];
		pronalazakSvihKombinacija(str, i, curr);
		curr.erase(curr.size() - 1);
	}
	return ;
}

void baza::lijevaDesna()
{
	string container;
	int i = 0;
	while (i < F.length())
	{
		while (F[i] != '-')
		{
			if (F[i] == ' ')
			{
				i++;
			}
			container.push_back(F[i]);
			i++;
		}
		Rlijeva.push_back(container);
		container = "";
		i += 2;

		while (F[i] != ',')
		{
			if (i == F.length())
			{
				break;
			}
			if (F[i] == ' ')
			{
				i++;
			}
			container.push_back(F[i]);
			i++;
		}
		Rdesna.push_back(container);
		container = "";
		i++;
	}
}

void baza::ogradaConvert()
{
	for (int i = 0; i < ograda.size(); ++i)
	{
		ogradaNova.push_back(ograda[i]);
	}
}

void baza::kandidatiZaKljuc()
{
	int Lbrojac = 0;
	int	Dbrojac = 0;
	vector<string> temp;

	for (int i = 0; i < sveKombinacije.size(); ++i)
	{
		temp.push_back(sveKombinacije[i]);
		for (int j = 0; j < Rlijeva.size(); ++j)
		{
			for (int k = 0; k < Rlijeva[j].length(); ++k)
			{
				for (int l = 0; l < temp[i].length(); ++l)
				{
					if (Rlijeva[j][k] == temp[i][l])
					{
						Lbrojac++;
					}

					for (int m = 0; m < Rdesna[j].size(); ++m)
					{
						if (Rdesna[j][m] == temp[i][l])
						{
							Dbrojac++;
						}
					}
				}
			}
			if ((Lbrojac == Rlijeva[j].length()) && (Dbrojac != Rdesna.size()))
			{
				temp[i].append(Rdesna[j]);
				j = 0;
			}
			Lbrojac = 0;
			Dbrojac = 0;
		}
	}

	for (int i = 0; i < temp.size(); ++i)
	{
		sort(temp[i].begin(), temp[i].end());
		temp[i].erase(unique(temp[i].begin(), temp[i].end()), temp[i].end());
		//cout << temp[i] << "\t";
	}

	for (int i = 0; i < sveKombinacije.size(); ++i)
	{
		if (noviR == temp[i])
		{
			kandidatiKljuca.push_back(sveKombinacije[i]);
		}
	}
	cout << endl << "Kandidati za kljuc: ";
	for (int i = 0; i < kandidatiKljuca.size(); ++i)
	{
		cout << kandidatiKljuca[i] << "\t";
	}
	cout << endl;
}