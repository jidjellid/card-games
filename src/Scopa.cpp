#include "Scopa.hpp"

Scopa::Scopa() : Game("Scopa", 2, 4, SEE_ALL, SEE_ALL){}
Scopa::~Scopa(){
	for(Deck *deck : defausse)
		delete deck;
}

bool Scopa::canContinue()
{
    return (checkForWinners() == nullptr && (deck->getDeck().size() != 0 || !areHandsEmpty() || deck->getBoard().size() != 0));
}

void Scopa::start()
{
    this->init(DeckBuilder::generate40(), 3);
}

void Scopa::init(vector<Card *> cards, int distributed)
{
    Game::init(cards, distributed);
	for(size_t i = 0; i < players.size(); i++){
		defausse.push_back(new Deck());
		points.push_back(0);
	}
    
	for(int i = 0; i < 4; i++){
	    deck->addOnBoard(deck->drawCard());
	}
}

void Scopa::iterate(vector<int> inputs){

		if(!isValidTake(inputs)){
			return;
		}

        //Play a card
        if(inputs.size() == 1){
            Card *card = turnOf()->getCards()[inputs[0]];
            deck->addOnBoard(card);
            turnOf()->removeCard(card);
        } else if(inputs.size() >= 2) {

			indexLastTake = turnToPlay;
            //Put the card used to take the others into the defausse
            Card *card = turnOf()->getCards()[inputs[0]];
			Card *takenCard = deck->getBoard()[inputs[1]];
			Card *takenCard2 = nullptr;
			if(inputs.size() == 3){
				takenCard2 = deck->getBoard()[inputs[2]];
			}

            defausse[turnToPlay]->putCard(card);
            turnOf()->removeCard(card);

            //Put the card taken into the defausse
            defausse[turnToPlay]->putCard(takenCard);
            deck->removeOnBoard(takenCard);

			if(takenCard2 != nullptr){
				defausse[turnToPlay]->putCard(takenCard2);
				deck->removeOnBoard(takenCard2);  
        	}         
        } 	

		//If players hands are empty, refill them
		if(areHandsEmpty()){
			if(deck->getDeck().size() != 0){//Game isn't over yet
				for(Player *player : players){
					for(int y = 0; y < 3; y++){//Each player gets 3 more cards
						if(deck->getDeck().size() != 0){
							player->addCard(deck->drawCard());
						}
					}
				}	
			} else {//The game is over
				for(Card * c : deck->getBoard()){
					defausse[indexLastTake]->putCard(c);
					deck->removeOnBoard(c);
				}
			}
		}

        Game::nextTurn();
}

vector<int> Scopa::automatic()
{
    int indexInput = 0;
    int indexCardTaken1 = -1;
    //Searches for possible ways to take cards
    for(size_t y = 0; y < turnOf()->getCards().size();y++){
        for(size_t i = 0; i < deck->getBoard().size(); i++){
            for(size_t z = i+1; z < deck->getBoard().size(); z++){
                if(isValidTake({(int)y,(int)i,(int)z})){
                    return {(int)y,(int)i,(int)z};
                }
            }
			
        	if(isValidTake({(int)y,(int)i})){
				indexCardTaken1 = i;
				indexInput = y;
            }
        }
    }

	if(indexCardTaken1 != -1)
		return {indexInput, indexCardTaken1};

    return {indexInput};
}

bool Scopa::areHandsEmpty(){
	for(Player *player : players){
		if(player->getCards().size() != 0)
			return false;
	}
	return true;
}

bool Scopa::isValidTake(vector<int> inputs){
	if(inputs.size() == 1 && inputs[0] < (int)turnOf()->getCards().size()){
		return true;
	} else if(inputs.size() == 2){
		if(inputs[0] < (int)turnOf()->getCards().size() && inputs[1] < (int)deck->getBoard().size() && turnOf()->getCards()[inputs[0]]->getValue() == deck->getBoard()[inputs[1]]->getValue()){
			return true;
		}
	} else if(inputs.size() == 3){
		if(inputs[0] < (int)turnOf()->getCards().size() && inputs[1] < (int)deck->getBoard().size() && inputs[2] < (int)deck->getBoard().size()){
			for(size_t i = 0; i < deck->getBoard().size(); i++){//Check if any single card can be taken 
				if(turnOf()->getCards()[inputs[0]]->getValue() == deck->getBoard()[i]->getValue()){
					return false;
				}
			}

			//If not, check if the two cards to be taken are the sum of the taking card
			if(turnOf()->getCards()[inputs[0]]->getValue() == getValue(deck->getBoard()[inputs[1]]) + getValue(deck->getBoard()[inputs[2]])){
				return true;
			}
		}
	}
	return false;
}

//Returns the index of the greatest value in tab
int Scopa::indexBiggestInTab(vector<int> tab){
	int indexBiggest = -1;
	int currentBiggest = -1;
	for(size_t i = 0; i < players.size(); i++){
		if(tab[i] > currentBiggest){
			indexBiggest = i;
			currentBiggest = tab[i];
		} else if(tab[i] == currentBiggest){
			indexBiggest = -1;
		}
	}
	return indexBiggest;
}

int Scopa::getValue(Card * c){
	switch (c->getValue()) {
		case As: return 1;
		case Valet: return 150;//Big values to make sure they can't be taken in a pair
		case Dame: return 200;
		case Roi: return 250;
		default: return c->getValue();
	}
}

//Returns index of the biggest deck or -1 if equality
int Scopa::indexBiggestDeck(){

	vector<int> count(players.size(),0);
	for(size_t i = 0; i < players.size(); i++){
		count[i] = defausse[i]->getDeck().size();
	}

	return indexBiggestInTab(count);
}

int Scopa::indexBiggestTrefles(){
	//Counts the number of Trefles in each players deck
	vector<int> count(players.size(),0);
	for(size_t i = 0; i < players.size(); i++){
		for(size_t y = 0; y < defausse[i]->getDeck().size(); y++){
			//Count for trefles
			if(defausse[i]->getDeck()[y]->getColor() == CLOVER){
				count[i]++;
			}
		}
	}

	return indexBiggestInTab(count);
}

int Scopa::index7ofTrefles(){
	for(size_t i = 0; i < players.size(); i++){
		for(size_t y = 0; y < defausse[i]->getDeck().size(); y++){
			if(defausse[i]->getDeck()[y]->getColor() == CLOVER && defausse[i]->getDeck()[y]->getValue() == 7){
				//cout << i << " has the trefle" << endl;
				return i;
			}
		}
	}
	throw "Impossible case";
}

//
int Scopa::indexPrimiera(){
	int primieraCount[players.size()][4];
	vector<int> finalValues(players.size(),0);

	for(size_t i = 0; i < players.size(); i++){
		for(int y = 0; y < 4; y++){
			primieraCount[i][y] = 0;
		}
	}

	//Get score from defausse of each player
	for(size_t i = 0; i < players.size(); i++){
		for(size_t y = 0; y < defausse[i]->getDeck().size(); y++){
		   if(defausse[i]->getDeck()[y]->getValue() > primieraCount[i][defausse[i]->getDeck()[y]->getColor()]){
				primieraCount[i][defausse[i]->getDeck()[y]->getColor()] = defausse[i]->getDeck()[y]->getValue();
			}
		}

		for(int y = 0; y < 4; y++)
			finalValues[i] += primieraCount[i][y];
	}

	return indexBiggestInTab(finalValues);
}

Player * Scopa::checkForWinners(){
	if(deck->getDeck().size() == 0 && areHandsEmpty()){//If the game is over, count the points
		points[indexBiggestDeck()]++;
		points[indexBiggestTrefles()]++;
		points[index7ofTrefles()]++;
		points[indexPrimiera()]++;

		int indexWinner = indexBiggestInTab(points);
		if(indexWinner != -1){
			return players[indexWinner];
		}
	}
	return nullptr;
}

bool Scopa::isPlayable(Card *)
{
    return true;
}

vector<string> Scopa::messages(int val){
	switch (val)
	{
	case 0:
		return {"Selectionner une carte"};
	case 1:
		return {"1 - Placer la carte","2 - Prendre des cartes"};
	case 2:
		return {"1 - Prendre une carte","2 - Prendre deux cartes"};
	case 3:
		return {"Quelle carte voulez-vous prendre ?"};
	case 4:
		return {"Quelle carte voulez-vous prendre ?"};
	default:
		return {};
	}
}

//Returns in wich case you are when given the val input, to be used with messages(int) to get good prints
int Scopa::InputMessages(int val, int input,bool * takeInput){
	switch(val)
	{
	//Take initial input
	case 0:{
		if(input < (int)turnOf()->getCards().size()){
			*takeInput = true;
			return 1;//Input += carte initiale
		}
		return 0;}
		
	//Print selection
	case 1:{
		if(input == 0){
			return -1;//Placer une carte
		} else if(input == 1){
			return 2;//Prendre des cartes
		}
		return 1;}
		
	//Print selection
	case 2:{
		if(input == 0){
			return 4;//Prendre une carte
		} else if(input == 1){
			return 3;//Prendre des cartes
		}
		return 2;}

	//Take one card then next step
	case 3: 
		*takeInput = true;
		return 4;//Input += une carte
	case 4: 
		*takeInput = true;
		return -1;//Input += une carte

	default:
		return -1;
	}
}