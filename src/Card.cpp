#include "Card.hpp"

Card::Card(int value, int color, int type): value(value), color(color), type(type){
	static int iterator = 0;
	this->id = iterator++;
}

Card::~Card(){}

int Card::getId() const
{
	return this->id;
}

int Card::getValue() const
{
	return this->value;
}

int Card::getColor() const
{
	return this->color;
}

int Card::getType() const
{
    return this->type;
}

int Card::getHint() const
{
	return this->hint;
}

void Card::setHint(int hint)
{
	this->hint = hint;
}
