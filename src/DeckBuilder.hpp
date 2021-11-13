#ifndef DECK_BUILDER_HPP
#define DECK_BUILDER_HPP

#include <random>
#include <algorithm>
#include <vector>
#include <time.h>
#include <iostream>
#include "Card.hpp"
#include "Enums.hpp"

class DeckBuilder {
public:
    static vector<Card *> generate32();
    static vector<Card *> generate40();
    static vector<Card *> generate52(bool = false);
    static vector<Card *> generateUno();
private:
    static const vector<int> ENTITIES;
    static const vector<int> COLORS;
    static vector<Card *> generate(vector<int>, vector<int>, int = 1, int = CLASSIC);
    static vector<Card *> concat(vector<Card *>, vector<Card *>);
};

#endif
