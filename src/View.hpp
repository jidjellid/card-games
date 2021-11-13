#ifndef VIEW_HPP
#define VIEW_HPP

#include "Player.hpp"
#include "Card.hpp"
#include "Game.hpp"
#include "Score.hpp"

#include <iostream>
#include <vector>
using namespace std;

/**
 * Class charged to display outputs
 * also get the user inputs
 */
class View {
private:
    Game *model;
    static string getCardValue(Card *);
    static string getCardColor(Card *, bool = true);
public:
    View(Game *);
    View();
    ~View();

    /**
     * Display methods
     */
    void displayPlayers() const;
    void displayPlayersCards() const;
    void displayScore() const;
    void displayBoard() const;
    static void display(string = "", int = FG_DEFAULT, bool = true);
    static void displayCard(Card *);
    static void displayCardUno(Card *);

    /**
     * CLI: get user input
     */
    static string getResponse(string = "");
};


#endif
