#include "Uno.hpp"

Uno::Uno() : Game("Uno", 2, 6, SEE_LAST, SEE_ALL){}
Uno::~Uno(){}

bool Uno::canContinue()
{
    return checkForWinners() == nullptr;
}

void Uno::start()
{
    this->init(DeckBuilder::generateUno(), 7);
}

void Uno::init(vector<Card *> cards, int distributed)
{
    Game::init(cards, distributed);

    for(size_t i = 0; i < players.size(); i++)
        points.push_back(0);

    deck->addOnBoard(deck->drawCard());
}

void Uno::iterate(vector<int> inputs)
{
    int index = inputs[0];
    if(index > (int)turnOf()->getCards().size())
		return;
        
    deck->addOnBoard(turnOf()->getCards()[index]);
    turnOf()->removeCard(turnOf()->getCards()[index]);
    applyEffects(deck->getLastOnBoard(), inputs);
    deck->fromBoardToDeck();

    int i = 0;
    for(Player *player : players){
        points[i] = 0;
        for(Card *card : player->getCards())
            points[i] += getScore(card);
        i++;
    }

    Game::nextTurn();
}

bool Uno::isPlayable(Card *card)
{
    Card *onBoard = deck->getLastOnBoard();

    return card->getValue() == PlusQuatre
           || card->getValue() == Joker
           || (card->getColor() == onBoard->getColor() && onBoard->getHint() == -1)
           || card->getValue() == onBoard->getValue()
           || (card->getColor() == onBoard->getHint() && (onBoard->getValue() == Joker || onBoard->getValue() == PlusQuatre));
}

void Uno::applyEffects(Card * card, vector<int> inputs)
{
    int value = card->getValue();

    if (value == PlusDeux || value == PlusQuatre){
        int take = value == PlusDeux ? 2 : 4;
        for (int i = 0; i < take; ++i) {
            nextPlayer()->addCard(deck->drawCard());
        }
    } else if (value == PasseTonTour){
        Game::nextTurn();
    } else if (value == InversementDeSens){
        direction = !direction;
    }

    if(value == Joker || value == PlusQuatre){
        int hint = -1;
        if(inputs[1] == 0){
            hint = Bleu;
        }else if (inputs[1] == 1){
            hint = Rouge;
        }else if (inputs[1] == 2){
            hint = Jaune;
        }else if (inputs[1] == 3){
            hint = Vert;
        }
        card->setHint(hint);
    }
}

vector<int> Uno::automatic()
{
    for (unsigned i = 0; i < turnOf()->getCards().size(); i++)
    {
        if(isPlayable(turnOf()->getCards()[i]))
        {
            return {int(i), int(rand() % messages(1).size())};
        }
    }
    return {0,0};
}

Player * Uno::checkForWinners(){
	for(Player * player : players)
		if(player->getCards().size() == 0)
			return player;
	return nullptr;
}

vector<string> Uno::messages(int val){
    switch (val)
	{
	case 0:
		return {"Selectionnez une carte : "};
	case 1:
		return {"1 - BLUE", "2 - RED", "3 - YELLOW", "4 - GREEN"};
    default:
		return {};
	}
}

//Returns in wich case you are when given the val input, to be used with messages(int) to get good prints
int Uno::InputMessages(int val, int input,bool * takeInput){
	switch(val)
	{
	case 0:{//Select a card
		*takeInput = true;
        int cardValue = turnOf()->getCards()[input]->getValue();
        if(cardValue == Joker|| cardValue == PlusQuatre){
            return 1;
        }
        return -1;}
    case 1:{//If the card is a Joker or a +4
        *takeInput = true;
        return -1;}
	default:
		return -1;
	}
}

int Uno::getScore(Card *card){
    switch (card->getValue()) {
        case PlusDeux:
        case PasseTonTour:
        case InversementDeSens: return 20;
        case PlusQuatre:
        case Joker: return 50;
        default: return card->getValue();
    }
}