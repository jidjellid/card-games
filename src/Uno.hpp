#ifndef UNO_HPP
#define UNO_HPP

#include "Game.hpp"
#include "Enums.hpp"
#include "View.hpp"
#include <iostream>
using namespace std;

class Uno : virtual public Game, virtual public Score
{

public:
    Uno();
    ~Uno();
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

    int getScore(Card *);
    void applyEffects(Card *, vector<int>);
};

#endif