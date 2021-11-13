#ifndef Card_HPP
#define Card_HPP

#include <ostream>
#include <string>
#include "Enums.hpp"

using namespace std;

class Card
{
private:
	int id; 
	int value;
	int color;
	int type;
	int hint = -1;
public:
	Card(int, int, int = CLASSIC);
	~Card();
	int getId() const;
	int getValue() const;
	int getColor() const;
	int getType() const;
	int getHint() const;
	void setHint(int);
};

#endif