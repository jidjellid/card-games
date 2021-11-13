#ifndef Player_HPP
#define Player_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include "Card.hpp"
using namespace std;

class Game;
class Player
{
private:
	int id;
	bool robot = false;
	string name;
	vector<Card *> cards;
public:
	Player(string);
	~Player();
	string getName();
	void addCard(Card *);
	void removeCard(Card *);
	void setRobot(bool);
	bool isRobot();
	vector<Card *> getCards();
    void shuffle();
};

#endif