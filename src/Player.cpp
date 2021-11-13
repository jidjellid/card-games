#include "Player.hpp"

Player::Player(string name)
{
	static int iterator = 0;
	this->id = iterator++;
	setRobot(name.compare("robot") == 0);
	this->name = isRobot() ? name + to_string(id) : name;
}

Player::~Player(){
	for(Card *card : cards)
		delete card;
}

string Player::getName()
{
	return name;
}

void Player::addCard(Card *card)
{
	cards.push_back(card);
}

void Player::removeCard(Card * card)
{
	for (size_t i = 0; i < cards.size(); i++)
	{
		if(cards[i]->getId() == card->getId())
		{
			cards.erase(cards.begin() + i);
		}
	}
}

void Player::setRobot(bool isRobot)
{
	this->robot = isRobot;
}

bool Player::isRobot()
{
	return this->robot;
}

vector<Card *> Player::getCards()
{
    return this->cards;
}

void Player::shuffle()
{
    srand(unsigned(time(NULL)));
    random_shuffle(begin(cards), end(cards));
}