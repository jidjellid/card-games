#include "Bataille.hpp"

Bataille::Bataille(): Game("Bataille", 2, 2, SEE_ALL, SEE_COUNT){}

Bataille::~Bataille(){}

void Bataille::start()
{
    vector<Card *> cards = DeckBuilder::generate32();
    this->init(cards, int(cards.size() / players.size()));
}

bool Bataille::canContinue()
{
    return checkForWinners() == nullptr;
}

void Bataille::init(vector<Card *> cards, int distributed)
{
    Game::init(cards, distributed);
}

void Bataille::iterate(vector<int> inputs)
{
    if(turnOf()->getCards().size() > 0)
    {
        deck->addOnBoard(turnOf()->getCards()[0]);
        turnOf()->removeCard(turnOf()->getCards()[0]);
    }

    if(deck->getBoard().size() % 2 == 0)
    {
        int last = deck->getBoard().size() - 1;
        int last1 = last - 1;

        Card *card = deck->getBoard()[last];
        Card *card1 = deck->getBoard()[last1];

        if(card->getValue() == card1->getValue()) return;

        int id = card->getValue() > card1->getValue() ? 1 : 0;
        for(Card *card : deck->getBoard()){
            players[id]->addCard(card);
        }
        players[id]->shuffle();
        deck->clearBoard();
    }
    Game::nextTurn();
}

vector<int> Bataille::automatic()
{
    return {0};
}

Player * Bataille::checkForWinners(){
    for(Player *player : players)
        if(player->getCards().size() == 32)
            return player;
    return nullptr;
}

bool Bataille::isPlayable(Card *)
{
    return true;
}

vector<string> Bataille::messages(int val){
    switch (val)
	{
	case 0:
		return {"Confirmez la pioche : "};
    default:
		return {};
	}
}
//Returns in wich case you are when given the val input, to be used with messages(int) to get good prints
int Bataille::InputMessages(int val, int input,bool * takeInput){
	switch(val)
	{
	case 0:
		*takeInput = true;
		return -1;

	default:
		return -1;
	}
}