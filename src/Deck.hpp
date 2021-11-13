#ifndef DECK_HPP
#define DECK_HPP

#include "Card.hpp"	
#include <vector>
#include <random>	
#include <algorithm>
#include <time.h>
#include <iostream>

class Player;
class Deck
{
private:
	vector<Card *> deck;
	vector<Card *> board;
public:
	Deck();
	~Deck();
	void putCard(Card *);
	Card * getLast();
	void shuffle();
	void setDeck(vector<Card *>);
	vector<Card *> getDeck() const;
	Card * drawCard();
	vector<Card *> getBoard() const;
    void addOnBoard(Card *);
    void removeOnBoard(Card *);
	Card * getLastOnBoard();
	void fromBoardToDeck();
	void clearBoard();
};



#endif