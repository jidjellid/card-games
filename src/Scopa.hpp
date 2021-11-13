#ifndef SCOPA_HPP
#define SCOPA_HPP

#include "Game.hpp"
#include "Score.hpp"

class Scopa : virtual public Game, virtual public Score
{
private:
	vector<Deck *> defausse;//Defausse de chaque joueur
    int indexLastTake;
public:
    Scopa();
    ~Scopa();

    /* Inherit methods */
    void init(vector<Card *>, int);

    void start();
    void iterate(vector<int>);
    vector<int> automatic();
    Player *checkForWinners();
    bool canContinue();
    bool isPlayable(Card *);

    bool isValidTake(vector<int>);
	int indexBiggestDeck();
	int indexBiggestTrefles();
	int index7ofTrefles();
	int indexPrimiera();
	int getScore(Card *);
	int indexBiggestInTab(vector<int>);
    bool areHandsEmpty();
    int getValue(Card *);

    vector<int> getPoints();

    vector<string> messages(int);
	int InputMessages(int, int, bool *);
};

#endif