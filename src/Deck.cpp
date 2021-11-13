#include "Deck.hpp"

Deck::Deck(){}

Deck::~Deck(){
	for(Card *card : board) delete card;

	for(Card *card : deck) delete card;
}

void Deck::setDeck(vector<Card *> cards)
{
	this->deck = cards;
}

vector<Card *> Deck::getDeck() const
{
	return this->deck;
}

void Deck::fromBoardToDeck()
{
	if(deck.size() < 5)
	{
		deck.insert(deck.end(), board.begin(), board.end());
		board.clear();
		addOnBoard(drawCard());
	}
}

void Deck::clearBoard(){
    board.clear();
}

void Deck::shuffle()
{
    srand(unsigned(time(NULL)));
    random_shuffle(begin(deck), end(deck));
}

Card * Deck::getLast()
{
	return deck.back();
}

void Deck::putCard(Card *card)
{
	deck.push_back(card);
}

Card * Deck::drawCard()
{
	if(deck.size() == 0){
		cout << "No more cards!" << endl;
	}
	Card *card = deck.back();
	deck.pop_back();
	return card;
}

vector<Card *> Deck::getBoard() const
{
	return this->board;
}

void Deck::addOnBoard(Card *card)
{
	board.push_back(card);
}

void Deck::removeOnBoard(Card *card)
{
    for (size_t i = 0; i < board.size(); i++)
    {
        if(board[i]->getId() == card->getId())
        {
            board.erase(board.begin() + i);
        }
    }
}

Card * Deck::getLastOnBoard()
{
	return board.back();
}
