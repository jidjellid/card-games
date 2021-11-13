#ifndef BRISCOLA_HPP
#define BRISCOLA_HPP

#include "Game.hpp"
#include "Score.hpp"

class Briscola : virtual public Game, virtual public Score
{
private:
	Card * briscola;
public:
    Briscola();
    ~Briscola();

    /* Inherit methods */
    void init(vector<Card *>, int);

    void start();
    void iterate(vector<int>);
    vector<int> automatic();
    Player *checkForWinners();
    bool canContinue();
    bool isPlayable(Card *);
    int isBetter(Card *,Card *);

    void countPoints();
	int getScore(Card *);

    vector<string> messages(int);
	int InputMessages(int, int, bool *);
};

#endif