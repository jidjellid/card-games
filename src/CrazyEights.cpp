#include "CrazyEights.hpp"

CrazyEights::CrazyEights(): Game("Crazy Eights", 2, 5, SEE_LAST, SEE_ALL){}

CrazyEights::~CrazyEights(){}

void CrazyEights::start()
{
    this->init(DeckBuilder::generate52(true), 7);
}

bool CrazyEights::canContinue()
{
    return checkForWinners() == nullptr;
}

void CrazyEights::init(vector<Card *> cards, int distributed)
{
    Game::init(cards, distributed);

    for(size_t i = 0; i < players.size(); i++)
        points.push_back(0);

    deck->addOnBoard(deck->drawCard());
}

void CrazyEights::iterate(vector<int> inputs)
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

vector<int> CrazyEights::automatic()
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

Player * CrazyEights::checkForWinners()
{
    for(Player *player : players)
        if(player->getCards().size() == 0)
            return player;
    return nullptr;
}

bool CrazyEights::isPlayable(Card * card)
{
    Card *onBoard = deck->getLastOnBoard();

    return card->getValue() == 8
        || card->getValue() == Joker
        || (card->getColor() == onBoard->getColor() && onBoard->getHint() == -1)
        || card->getValue() == onBoard->getValue()
        || (card->getColor() == onBoard->getHint() && (onBoard->getValue() == Joker || onBoard->getValue() == 8));
}

void CrazyEights::applyEffects(Card * card, vector<int> inputs)
{
    int value = card->getValue();

   if (value == Valet){
        turnToPlay += direction ? 1 : -1;
    } else if (value == As){
        direction = !direction;
    } else if (value == Joker || value == 2){
        int take = value == 2 ? 2 : 4;
        for (int i = 0; i < take; ++i)
            nextPlayer()->addCard(deck->drawCard());
    }

    if(value == Joker || value == 8){
        int hint = -1;
        if(inputs[1] == 0){
            hint = CLOVER;
        }else if (inputs[1] == 1){
            hint = HEART;
        }else if (inputs[1] == 2){
            hint = SPADE;
        }else if (inputs[1] == 3){
            hint = DIAMOND;
        }
        card->setHint(hint);
    }
}

int CrazyEights::getScore(Card *card){
    switch (card->getValue()) {
        case Roi:
        case Dame: return 10;
        case Valet:
        case As:
        case 2: return 20;
        case 8:
        case Joker: return 50;
        default: return card->getValue();
    }
}

vector<string> CrazyEights::messages(int val){
    switch (val)
	{
	case 0:
		return {"Selectionnez  une carte : "};
	case 1:
		return {"1 - TREFLES", "2 - COEUR", "3 - PIQUE", "4 - CARREAU"};
    default:
		return {};
	}
}

//Returns in wich case you are when given the val input, to be used with messages(int) to get good prints
int CrazyEights::InputMessages(int val, int input, bool * takeInput){
	switch(val)
	{
	case 0:{
		*takeInput = true;
        int cardValue = turnOf()->getCards()[input]->getValue();
        if(cardValue == Joker|| cardValue == 8){
            return 1;
        }		
        return -1;}

    case 1:{//If the card is a Joker or a 8
        *takeInput = true;
        return -1;}

	default:
		return -1;
	}
}