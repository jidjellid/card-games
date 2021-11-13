#ifndef BATAILLE_HPP
#define BATAILLE_HPP

#include "Game.hpp"
#include "Enums.hpp"
#include <iostream>
using namespace std;

class Bataille : virtual public Game
{
public:
    Bataille();
    ~Bataille();

    /* Inherit methods */
    void init(vector<Card *>, int);

    void start();
    void iterate(vector<int>);
    vector<int> automatic();
    Player *checkForWinners();
    bool canContinue();
    bool isPlayable(Card *);

    vector<string> messages(int);
	int InputMessages(int, int, bool *);
};

#endif
