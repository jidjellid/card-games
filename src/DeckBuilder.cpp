#include "DeckBuilder.hpp"

const vector<int> DeckBuilder::ENTITIES = {SPADE, HEART, DIAMOND, CLOVER};
const vector<int> DeckBuilder::COLORS = {Bleu, Rouge, Jaune, Vert};

vector<Card *> DeckBuilder::concat(vector <Card *> deck1, vector <Card *> deck)
{
    deck1.insert(deck1.end(), deck.begin(), deck.end());
    return deck1;
}

vector<Card *> DeckBuilder::generate(vector<int> values, vector<int> colors, int repeat, int type)
{
    vector<Card *> deck;
    for (int value : values)
        for (int color : colors)
            for (int k = 0; k < repeat; k++)
                deck.push_back(new Card(value, color, type));

    srand(unsigned(time(NULL)));

    for (unsigned int i = 0; i < deck.size() - 1; i++) {
        int j = i + rand() % (deck.size() - i);
        swap(deck[i], deck[j]);
    }

    return deck;
}

vector<Card *> DeckBuilder::generate32()
{
    return generate({7, 8, 9, 10, As, Valet, Dame, Roi}, ENTITIES);
}

vector<Card *> DeckBuilder::generate52(bool withJokers)
{
    vector<Card *> deck = concat(generate32(), generate({2, 3, 4, 5, 6}, ENTITIES));
    return (!withJokers) ? deck : concat(deck, generate({Joker}, {-1}, 2));
}

vector<Card *> DeckBuilder::generateUno()
{
    vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, PlusDeux, InversementDeSens, PasseTonTour};

    vector<Card *> part1 = generate({0}, COLORS, 1, UNO);
    vector<Card *> part2 = generate(values, COLORS, 2, UNO);
    vector<Card *> part3 = generate({Joker, PlusQuatre}, {-1}, 4, UNO);

    return concat(concat(part1, part2), part3);
}

vector<Card *> DeckBuilder::generate40()
{
    return generate({2, 3, 4, 5, 6, 7, As, Valet, Dame, Roi}, ENTITIES);
}

