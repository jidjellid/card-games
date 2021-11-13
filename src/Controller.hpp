#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <iostream>
#include <sstream>

#include "View.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "DeckBuilder.hpp"
#include "Bataille.hpp"
#include "Uno.hpp"
#include "Briscola.hpp"
#include "Scopa.hpp"
#include "CrazyEights.hpp"

class Controller {
private:
    Game *model = nullptr;
    View view;
public:
    void start();
    string chooseGame();
    int validateInput() const;
    vector<Player *> createPlayers();
};

#endif
