#ifndef CRAZYEIGHTS_HPP
#define CRAZYEIGHTS_HPP

#include "Game.hpp"
#include "Score.hpp"

class CrazyEights: virtual public Game, virtual public Score
{
public:
    CrazyEights();
    ~CrazyEights();

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
