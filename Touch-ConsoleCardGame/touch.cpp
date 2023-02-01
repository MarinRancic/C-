#include "touch.hpp"

void game::openPack()
{
	int k = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 1; j < 14; ++j)
		{
			allCards.push_back(j);
		}
	}
}

void game::shuffle()
{
	random_shuffle(allCards.begin(), allCards.end());
}

void player::setDeck(int card)
{
	deck.push_back(card);
}

void player::setPile(int card)
{
	pile.push_back(card);
}

void game::deal()
{
	for (int i = 0; i < 52; ++i)
	{
		if (i >= 26)
		{
			players[1].setDeck(allCards[i]);
		}

		else
		{
			players[0].setDeck(allCards[i]);
		}
	}
}

vector<int> player::getDeck()
{
	return deck;
}

vector<int> player::getPile()
{
	return pile;
}

void game::mainMenu()
{
	int inputBeginning;

	cout << "Dobrodosli u igru Touch!" << endl;

	while (1) 
	{
		system("cls");

		cout << "Odaberite:" << endl << endl;
		cout << "0 - Izlazak iz igre" << endl;
		cout << "1 - Udite u igru" << endl;
		cout << "2 - Pravila igre" << endl;
		
		cin >> inputBeginning;

		if (inputBeginning == 0)
		{
			exit(1);
		}
		else if (inputBeginning == 1)
		{
			inGame();
		}

		else if (inputBeginning == 2)
		{
			cout << "Svakom igracu je podijeljeno 26 karata." << endl;
			cout << "Igraci naizmjenicno uzimaju kartu sa vrha svoga spila i stavljaju je na svoju hrpu, protivnicku hrpu ili na zajednicku hrpu." << endl;
			cout << "Takoder, igraci mogu staviti kartu sa vrha svoje hrpe, na drugu hrpu." << endl;
			cout << "Ako to naprave, mogu nastaviti to raditi sve dok ne stave kartu sa svoga spila u svoju hrpu." << endl;
			cout << "Igraci mogu stavljati svoje karte u protivnicke hrpe samo ako ima karata u zajednickoj hrpi, odnosno ako bar prva karta (as) stavljena na zajednicku hrpu." << endl;
			cout << "Da bi se karta stavila na zajednicku ili protivnicku hrpu, ta karta mora biti za 1 veca od karte na vrhu zajednicke ili protivnicke hrpe (zog karte nije bitan)" << endl;
			cout << "Prioritet stavljanja karata ima zajednicka hrpa (npr. imate 3, a i na zajednickoj hrpi i na protivnickoj hrpi je 2, 3 se mora staviti na zajednicku hrpu." << endl;
			cout << "Ako protivnik ne vidi da je mogao staviti kartu na neku od drugih hrpa umjesto svoje ili je stavio kartu na pogresnu hrpu, zove se tac" << endl;
			cout << "Tac - igrac koji je napravio gresku dobija kartu sa dna protivnickog spila i stavlja je na dno svoga spila" << endl;
			cout << "Pobjednik je igrac koji ostane bez karata" << endl << endl;
			system("pause");
		}
	}
}

void game::inGame()
{
	int input1;
	int input2;
	openPack();
	cout << "Opening cards..." << endl;
	Sleep(1500);
	shuffle();
	cout << "Shuffling cards..." << endl;
	Sleep(2000);
	deal();
	cout << "Dealing cards..." << endl << endl;
	Sleep(2000);

	cout << "-----------------------------------------------------------" << endl;
	cout << "| Kontrole:                                                |" << endl;
	cout << "| 1 - Stavite sljedecu kartu na svoju hrpu.                |" << endl;
	cout << "| 2 - Stavite sljedecu kartu na zajednicku hrpu.           |" << endl;
	cout << "| 3 - Stavite sljedecu kartu na protivnicku hrpu.          |" << endl;
	cout << "| 4 - Stavite kartu iz vlastite hrpe na zajednicku hrpu.   |" << endl;
	cout << "| 5 - Stavite kartu iz vlastite hrpe na protivnicku hrpu.  |" << endl;
	cout << "-----------------------------------------------------------" << endl << endl;
	system("pause");

	while (1)
	{
		input1 = 0;

		while (input1 != 1)
		{
			system("cls");
			input1 = 0;
			cout << "-------------------------" << endl;
			cout << "|    Igrac 1 na redu    |" << endl;
			cout << "-------------------------" << endl << endl;

			if (players[0].getDeck().size() != 0)
			{
				cout << "Sljedeca karta: " << players[0].getDeck()[0] << endl << endl;
				printBoard();
			}
			else
			{
				checkWinner();
				players[0].checkSize();
				cout << "Sljedeca karta: " << players[0].getDeck()[0] << endl << endl;
				printBoard();
			}

			cin >> input1;

			if (input1 == 1)
			{
				if ((((players[0].getDeck()[0]) == 1) && (commonPile.size() == 0)))
				{
					touch(players[1], players[0]);
					break;
				}

				else if ((players[0].getPile().size() != 0) && (players[1].getPile().size() != 0) && (commonPile.size() != 0))
				{
					if (((players[0].getPile()[players[0].getPile().size() - 1]) == ((commonPile[commonPile.size() - 1]) + 1)) ||
						((players[0].getPile()[players[0].getPile().size() - 1]) == ((players[1].getPile()[players[1].getPile().size() - 1]) + 1)) ||
						((players[0].getDeck()[0]) == ((commonPile[commonPile.size() - 1]) + 1)) ||
						((players[0].getDeck()[0]) == ((players[1].getPile()[players[1].getPile().size() - 1]) + 1)) ||

						(((players[0].getPile()[players[0].getPile().size() - 1]) == 1) && ((commonPile[commonPile.size() - 1]) == 13)) ||
						(((players[0].getPile()[players[0].getPile().size() - 1]) == 1) && ((players[1].getPile()[players[1].getPile().size() - 1]) == 13)) ||
						(((players[0].getDeck()[0]) == 1) && ((commonPile[commonPile.size() - 1]) == 13)) ||
						(((players[0].getDeck()[0]) == 1) && ((players[1].getPile()[players[1].getPile().size() - 1]) == 13)))
					{
						touch(players[1], players[0]);
						break;
					}
					else
					{
						players[0].setPile(players[0].getDeck()[0]);
						players[0].eraseFirstDeck();
					}
				}
				else
				{
					players[0].setPile(players[0].getDeck()[0]);
					players[0].eraseFirstDeck();
				}

			}

			else if (input1 == 2)
			{
				if (commonPile.size() == 0)
				{
					if ((players[0].getDeck()[0] == 1) && (commonPile.size() == 0))
					{
						commonPile.push_back(players[0].getDeck()[0]);
						players[0].eraseFirstDeck();
					}

					else
					{
						touch(players[1], players[0]);
						break;
					}
				}

				else
				{
					if (players[0].getPile().size() != 0)
					{
						if ((players[0].getPile()[players[0].getPile().size() - 1]) == ((commonPile[commonPile.size() - 1]) + 1))
						{
							touch(players[1], players[0]);
							break;
						}
					}
					
					if (((players[0].getDeck()[0]) == ((commonPile[commonPile.size() - 1]) + 1)) ||
						((players[0].getDeck()[0] == 1) && (commonPile[commonPile.size() - 1] == 13)))
					{
						commonPile.push_back(players[0].getDeck()[0]);
						players[0].eraseFirstDeck();
					}
					else
					{
						touch(players[1], players[0]);
						break;
					}
				}
			}

			else if (input1 == 3)
			{
				if ((players[1].getPile().size() == 0) || (commonPile.size() == 0))
				{
					touch(players[1], players[0]);
					break;
				}
				else
				{
					if (players[0].getPile().size() != 0)
					{
						if (((players[0].getPile()[players[0].getPile().size() - 1]) == ((commonPile[commonPile.size() - 1]) + 1)) ||
							((players[0].getPile()[players[0].getPile().size() - 1]) == ((players[1].getPile()[players[1].getPile().size() - 1]) + 1)) ||
							((commonPile[commonPile.size() - 1]) == (players[1].getPile()[players[1].getPile().size() - 1] + 1)))
						{
							touch(players[1], players[0]);
							break;
						}
					}
					
					if (((players[0].getDeck()[0]) == ((players[1].getPile()[players[1].getPile().size() - 1]) + 1)) ||
						((players[0].getDeck()[0] == 1) && ((players[1].getPile()[players[1].getPile().size() - 1]) == 13)))
					{
						players[1].setPile(players[0].getDeck()[0]);
						players[0].eraseFirstDeck();
					}
					else
					{
						touch(players[1], players[0]);
						break;
					}
				}
			}

			else if (input1 == 4)
			{
				if (players[0].getPile().size() == 0)
				{
					cout << endl << "Hrpa prazna! Pokusajte drugi potez." << endl;
				}

				else
				{
					if (commonPile.size() == 0)
					{
						touch(players[1], players[0]);
						break;
					}
					else
					{
						if (((players[0].getPile()[players[0].getPile().size() - 1]) == (commonPile[commonPile.size() - 1] + 1)) ||
							((players[0].getPile()[players[0].getPile().size() - 1] == 1) && (commonPile[commonPile.size() - 1] == 13)))
						{
							commonPile.push_back(players[0].getPile()[players[0].getPile().size() - 1]);
							players[0].eraseLastPile();
						}
						else
						{
							touch(players[1], players[0]);
							break;
						}
					}
				}
			}

			else if (input1 == 5)
			{
				if (players[0].getPile().size() == 0)
				{
					cout << endl << "Hrpa prazna! Pokusajte drugi potez." << endl;
				}

				else
				{
					if ((players[1].getPile().size() == 0) || (commonPile.size() == 0))
					{
						touch(players[1], players[0]);
						break;
					}
					else
					{
						if ((players[0].getPile()[players[0].getPile().size() - 1]) == ((commonPile[commonPile.size() - 1]) + 1))
						{
							touch(players[1], players[0]);
							break;
						}
						else if (((players[0].getPile()[players[0].getPile().size() - 1]) == ((players[1].getPile()[players[1].getPile().size() - 1]) + 1)) ||
							((players[0].getPile()[players[0].getPile().size() - 1] == 1) && ((players[1].getPile()[players[1].getPile().size() - 1]) == 13)))
						{
							players[1].setPile(players[0].getPile()[players[0].getPile().size() -1 ]);
							players[0].eraseLastPile();
						}
						else
						{
							touch(players[1], players[0]);
							break;
						}
					}
				}
			}
		}


		input2 = 0;

		while (input2 != 1)
		{
			system("cls");
			cout << "-------------------------" << endl;
			cout << "|    Igrac 2 na redu    |" << endl;
			cout << "-------------------------" << endl << endl;

			if (players[1].getDeck().size() != 0)
			{
				cout << "Sljedeca karta: " << players[1].getDeck()[0] << endl << endl;
				printBoard();
			}
			else
			{
				checkWinner();
				players[1].checkSize();
				cout << "Sljedeca karta: " << players[1].getDeck()[0] << endl << endl;
				printBoard();
			}

			cin >> input2;

			if (input2 == 1)
			{
				if ((((players[1].getDeck()[0]) == 1) && (commonPile.size() == 0)))
				{
					touch(players[0], players[1]);
					break;
				}

				else if ((players[1].getPile().size() != 0) && (players[0].getPile().size() != 0) && (commonPile.size() != 0))
				{
					if (((players[1].getPile()[players[1].getPile().size() - 1]) == ((commonPile[commonPile.size() - 1]) + 1)) ||
						((players[1].getPile()[players[1].getPile().size() - 1]) == ((players[0].getPile()[players[0].getPile().size() - 1]) + 1)) ||
						((players[1].getDeck()[0]) == ((commonPile[commonPile.size() - 1]) + 1)) ||
						((players[1].getDeck()[0]) == ((players[0].getPile()[players[0].getPile().size() - 1]) + 1)) ||

						(((players[1].getPile()[players[1].getPile().size() - 1]) == 1) && ((commonPile[commonPile.size() - 1]) == 13)) ||
						(((players[1].getPile()[players[1].getPile().size() - 1]) == 1) && ((players[0].getPile()[players[0].getPile().size() - 1]) == 13)) ||
						(((players[1].getDeck()[0]) == 1) && ((commonPile[commonPile.size() - 1]) == 13)) ||
						(((players[1].getDeck()[0]) == 1) && ((players[0].getPile()[players[0].getPile().size() - 1]) == 13)))
					{
						touch(players[0], players[1]);
						break;
					}
					else
					{
						players[1].setPile(players[1].getDeck()[0]);
						players[1].eraseFirstDeck();
					}
				}
				else
				{
					players[1].setPile(players[1].getDeck()[0]);
					players[1].eraseFirstDeck();
				}

			}

			else if (input2 == 2)
			{
				if (commonPile.size() == 0)
				{
					if ((players[1].getDeck()[0] == 1) && (commonPile.size() == 0))
					{
						commonPile.push_back(players[1].getDeck()[0]);
						players[1].eraseFirstDeck();
					}

					else
					{
						touch(players[0], players[1]);
						break;
					}
				}

				else
				{
					if (players[1].getPile().size() != 0)
					{
						if ((players[1].getPile()[players[1].getPile().size() - 1]) == ((commonPile[commonPile.size() - 1]) + 1))
						{
							touch(players[0], players[1]);
							break;
						}
					}

					if (((players[1].getDeck()[0]) == ((commonPile[commonPile.size() - 1]) + 1)) ||
						((players[1].getDeck()[0] == 1) && (commonPile[commonPile.size() - 1] == 13)))
					{
						commonPile.push_back(players[1].getDeck()[0]);
						players[1].eraseFirstDeck();
					}
					else
					{
						touch(players[0], players[1]);
						break;
					}

				}
			}

			else if (input2 == 3)
			{
				if ((players[0].getPile().size() == 0) || (commonPile.size() == 0))
				{
					touch(players[0], players[1]);
					break;
				}
				else
				{
					if (players[1].getPile().size() != 0)
					{
						if (((players[1].getPile()[players[1].getPile().size() - 1]) == ((commonPile[commonPile.size() - 1]) + 1)) ||
							((players[1].getPile()[players[1].getPile().size() - 1]) == ((players[0].getPile()[players[0].getPile().size() - 1]) + 1)) ||
							((commonPile[commonPile.size() - 1]) == (players[0].getPile()[players[0].getPile().size() - 1] + 1)))
						{
							touch(players[0], players[1]);
							break;
						}
					}
					
					if (((players[1].getDeck()[0]) == ((players[0].getPile()[players[0].getPile().size() - 1]) + 1)) ||
						((players[1].getDeck()[0] == 1) && ((players[0].getPile()[players[0].getPile().size() - 1]) == 13)))
					{
						players[0].setPile(players[1].getDeck()[0]);
						players[1].eraseFirstDeck();
					}
					else
					{
						touch(players[0], players[1]);
						break;
					}
				}
			}

			else if (input2 == 4)
			{
				if (players[1].getPile().size() == 0)
				{
					cout << endl << "Hrpa prazna! Pokusajte drugi potez." << endl;
				}

				else
				{
					if (commonPile.size() == 0)
					{
						touch(players[0], players[1]);
						break;
					}
					else
					{
						if (((players[1].getPile()[players[1].getPile().size() - 1]) == (commonPile[commonPile.size() - 1] + 1)) ||
							((players[1].getPile()[players[1].getPile().size() - 1] == 1) && (commonPile[commonPile.size() - 1] == 13)))
						{
							commonPile.push_back(players[1].getPile()[players[1].getPile().size() - 1]);
							players[1].eraseLastPile();
						}
						else
						{
							touch(players[0], players[1]);
							break;
						}
					}
				}
			}

			else if (input2 == 5)
			{
				if (players[1].getPile().size() == 0)
				{
					cout << endl << "Hrpa prazna! Pokusajte drugi potez." << endl;
				}

				else
				{
					if ((players[0].getPile().size() == 0) || (commonPile.size() == 0))
					{
						touch(players[0], players[1]);
						break;
					}
					else
					{
						if ((players[1].getPile()[players[1].getPile().size() - 1]) == ((commonPile[commonPile.size() - 1]) + 1))
						{
							touch(players[0], players[1]);
							break;
						}
						else if (((players[1].getPile()[players[1].getPile().size() - 1]) == ((players[0].getPile()[players[0].getPile().size() - 1]) + 1)) ||
							((players[1].getPile()[players[1].getPile().size() - 1] == 1) && ((players[0].getPile()[players[0].getPile().size() - 1]) == 13)))
						{
							players[0].setPile(players[1].getPile()[players[1].getPile().size()-1]);
							players[1].eraseLastPile();
						}
						else
						{
							touch(players[0], players[1]);
							break;
						}
					}
				}
			}
		}
	}
}

void player::eraseFirstDeck()
{
	deck.erase(deck.begin());
}

void player::eraseLastPile()
{
	pile.erase(pile.begin() + pile.size() -1);
}

void player::swapPiles()
{
	deck = pile;
	pile.clear();
}

void game::printBoard()
{
	cout << "Velicina spila 1. Igraca: " << players[0].getDeck().size() << endl;
	cout << "----------------------" << endl;
	if (players[0].getPile().size() == 0)
	{
		cout << "Hrpa 1. Igraca: prazna " << "(" << players[0].getPile().size() << ")" << endl;
	}
	else
	{
		cout << "Hrpa 1. Igraca: " << players[0].getPile()[players[0].getPile().size() -1] << " (" << players[0].getPile().size() << ")" << endl;
	}

	if (commonPile.size() == 0)
	{
		cout << "Zajednicka hrpa: prazna" << endl;
	}
	else
	{
		cout << "Zajednicka hrpa: " << commonPile[commonPile.size() -1] << endl;
	}

	if (players[1].getPile().size() == 0)
	{
		cout << "Hrpa 2. Igraca: prazna " << "(" << players[1].getPile().size() << ")" << endl;
	}
	else
	{
		cout << "Hrpa 2. Igraca: " << players[1].getPile()[players[1].getPile().size() -1] << " (" << players[1].getPile().size() << ")" << endl;
	}
	cout << "----------------------" << endl;
	cout << "Velicina spila 2. Igraca: " << players[1].getDeck().size() << endl;
	cout << endl;
}

void game::checkWinner()
{
	if ((players[0].getDeck().size() == 0) && (players[0].getPile().size() == 0))
	{
		cout << "Pobijedio je 1. Igrac!!!" << endl;
		exit(1);
	}
	else if ((players[1].getDeck().size() == 0) && (players[1].getPile().size() == 0))
	{
		cout << "Pobijedio je 2. Igrac!!!" << endl;
		exit(2);
	}
}

void game::touch(player& p0, player& p1)
{
	cout << endl << "TOUCH!!!" << endl;
	if (p0.getDeck().size() != 0)
	{
		p1.setDeck((p0.getDeck()[p0.getDeck().size()-1]));
		p0.deleteLastDeck();
	}
	else
	{
		p1.setDeck(p0.getPile()[p0.getPile().size() -1]);
		p0.eraseLastPile();
	}
	system("pause");
}

void player::checkSize()
{
	if (deck.size() == 0)
	{
		swapPiles();
	}
}

void player::deleteLastDeck()
{
	deck.pop_back();
}