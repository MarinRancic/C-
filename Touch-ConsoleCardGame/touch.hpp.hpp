#ifndef H_TOUCH
#define H_TOUCH

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

using namespace std;

class player
{
	vector<int> deck;
	vector<int> pile;
	
public:
	void setDeck(int);
	vector<int> getDeck();
	vector<int> getPile();
	void setPile(int);
	void eraseFirstDeck();
	void eraseLastPile();
	void swapPiles();
	void checkSize();
	void deleteLastDeck();
};

class game
{
	vector<int> allCards;
	vector<int> commonPile;
	player players[2];

public:
	void openPack();
	void shuffle();
	void deal();
	void mainMenu();
	void inGame();
	void checkWinner();
	void printBoard();
	void touch(player&, player&);
};

#endif