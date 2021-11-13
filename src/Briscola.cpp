#include "Briscola.hpp"

Briscola::Briscola() : Game("Briscola", 2,2, SEE_ALL, SEE_ALL){}

Briscola::~Briscola(){
    delete briscola;
}

bool Briscola::canContinue()
{
    for(unsigned int i = 0; i < players.size(); i++)
        if(players[i]->getCards().size() != 0 || deck->getDeck().size() != 0)
            return checkForWinners() == nullptr;

    return false;    
} 

void Briscola::start()
{
    this->init(DeckBuilder::generate40(), 3);
}

void Briscola::init(vector<Card *> cards, int distributed)
{
    Game::init(cards, distributed);
    briscola = deck->drawCard();
    for(size_t i = 0; i < players.size(); i++){
        points.push_back(0);
    }
}

void Briscola::iterate(vector<int> inputs)
{
    int index = inputs[0];
    if(index > (int)turnOf()->getCards().size())
		return;
        
    deck->addOnBoard(turnOf()->getCards()[index]);
    turnOf()->removeCard(turnOf()->getCards()[index]);
    Game::nextTurn();

    if(turnToPlay == 0){
        for(Player *player : players){
            if(deck->getDeck().size() != 0){
                player->addCard(deck->drawCard());
            } 
        
            if(player->getCards().size() != 3 && briscola != nullptr){
                player->addCard(briscola);
                briscola = nullptr;
            }
        }
        countPoints();
        deck->clearBoard();
    }
    
}

vector<int> Briscola::automatic()
{
    int indexCard = 0;
    if(turnToPlay == 0){//If the robot is the first to play, play it's best card
        for(unsigned int i = 0; i < turnOf()->getCards().size();i++){
            if(briscola == nullptr
                || ((getScore(turnOf()->getCards()[i]) > getScore(briscola))
                && getScore(turnOf()->getCards()[i]) >= getScore(turnOf()->getCards()[indexCard]))){
                indexCard = i;
            }
        }
    } else {//If the robot isn't the first one to play
        for(unsigned int i = 0; i < turnOf()->getCards().size();i++){
            int currentMaxScore = 0;
            for(unsigned int y = 0; y < deck->getBoard().size();y++){
                if(getScore(deck->getBoard()[y]) > currentMaxScore){
                    currentMaxScore = getScore(deck->getBoard()[y]);
                }
            }

            if(getScore(turnOf()->getCards()[i]) > currentMaxScore
               && getScore(turnOf()->getCards()[i]) >= getScore(turnOf()->getCards()[indexCard])){
             indexCard = i;
            }
        }
    }
    return {indexCard, 0};
}

Player * Briscola::checkForWinners(){
	for(unsigned int i = 0; i < points.size(); i++){
		if(points[i] >= 60)
			return players[i];
    }
	return nullptr;
}

int Briscola::getScore(Card *card){
    switch (card->getValue()) {
        case As: return 11;
        case 3: return 10;
        case Roi: return 4;
        case Dame: return 3;
        case Valet: return 2;
        default: return 0;
    }
}

//Returns 1 if card1 is better than card2, -1 if not or 0 if equals
int Briscola::isBetter(Card *card1, Card *card2){
    if(briscola != nullptr){//Check if one of the two card has the same color has the briscola
        if(card1->getColor() == briscola->getColor() && card2->getColor() != briscola->getColor()){
            return 1;
        } else if(card1->getColor() != briscola->getColor() && card2->getColor() == briscola->getColor()){
            return -1;
        }
    }

    //Determines the best out of the two cards
    if(getScore(card1) > getScore(card2))
        return 1;
    else if(getScore(card1) < getScore(card2))
        return -1;
    else 
        return 0;
}

void Briscola::countPoints(){
    int totalScore = getScore(deck->getBoard()[0]);
    int indexBestCard = 0;
	int indexBestPlayer = 0;

    //Fill indexBest with the index of the player with the best score for this round
	for(unsigned int i = 1; i < deck->getBoard().size(); i++){
        totalScore += getScore(deck->getBoard()[i]);

        int best = isBetter(deck->getBoard()[i],deck->getBoard()[indexBestCard]);
		if(best == 1){//Current card is better than the best
			indexBestCard = i;
			indexBestPlayer = i;
		} else if(best == 0){//Current card and the best are equals
			indexBestPlayer = -1;
		} 
	}

    //If the players currently playing do not have equal scores
	if(indexBestPlayer != -1){
        points[indexBestPlayer] += totalScore;
	}
}

bool Briscola::isPlayable(Card *)
{
    return true;
}

vector<string> Briscola::messages(int val){
	switch (val)
	{
	case 0:
		return {"Selectionnez une carte : "};
    case startOfTurn:{//Start of turn message
        if(briscola != nullptr){
            string s = "L'atout actuel est ";
            if(briscola->getColor() == SPADE)
                return {s + "\xE2\x99\xA0"};
            if(briscola->getColor() == HEART)
                return {s + "\xE2\x99\xA5"};
            if(briscola->getColor() == DIAMOND)
                return {s + "\xE2\x99\xA6"};
            if(briscola->getColor() == CLOVER)
                return {s + "\xE2\x99\xA3"};

            return {" \xE2\x99\xA3"};
        }
        return {"Il n'y a plus d'atout !"};
        
    }
    case endOfTurn:{//End of turn message
        string s = "Score : ";
        for(int i : points){
            s += to_string(i) + ", ";
        }
        return {s};
    }
    default:
        return {};
    }
}

//Returns in wich case you are when given the val input, to be used with messages(int) to get good prints
int Briscola::InputMessages(int val, int input,bool * takeInput){
	switch(val)
	{
	//Take initial input
	case 0:
		*takeInput = true;
		return -1;//Input += carte initiale

	default:
		return -1;
	}
}