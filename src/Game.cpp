#include "Game.hpp"

Game::Game(string name, unsigned int min, unsigned int max, int seeBoard, int seeOwn):
    name(name), min(min), max(max), seeBoard(seeBoard), seeOwn(seeOwn){}

Game::~Game(){
    /*delete deck;
    for(Player *player : players) delete player;*/
    cout << "Destructeur Game" << endl;
}

void Game::init(vector<Card *> cards, int distributed)
{
    deck = new Deck();
    deck->setDeck(cards);
    deck->shuffle();
    for(Player *player : players)
        for(int i = 0; i < distributed; i++)
            player->addCard(deck->drawCard());
}

bool Game::hasPlayable() 
{
    for (Card *card : turnOf()->getCards())
        if(isPlayable(card)) return true;
    return false;
}

void Game::clean(){
    delete deck;
    for(Player *player : players) delete player;
}

void Game::nextTurn()
{
    if(direction){
        turnToPlay++;
        if(turnToPlay > (int)players.size()-1)
            turnToPlay = 0;
    } else {
        turnToPlay--;
        if(turnToPlay < 0)
            turnToPlay = players.size()-1;
    }
}

Player * Game::nextPlayer()
{
    if(direction){
        if(turnToPlay+1 > (int)players.size()-1)
            return players[0];
        else
            return players[turnToPlay+1];
    } else {
        if(turnToPlay-1 < 0)
            return players[players.size()-1];
        else
            return players[turnToPlay-1];
    }
}

Deck * Game::getDeck() const
{
    return this->deck;
}

Player *Game::turnOf() const
{
    return players[abs(turnToPlay)];
}

void Game::draw()
{
    if(deck->getDeck().size() > 0)
        turnOf()->addCard(deck->drawCard());
    else
        cout << "error draw" << endl;
}

vector<Player *> Game::getPlayers() const
{
    return this->players;
}

void Game::setPlayers(vector<Player *> players)
{
    this->players = players;
    enoughPlayers();
}

const string Game::getName() const
{
    return this->name;
}

const int Game::getMin() const
{
    return this->min;
}

const int Game::getMax() const
{
    return this->max;
}

const int Game::getSeeBoard() const
{
    return this->seeBoard;
}

const int Game::getSeeOwn() const
{
    return this->seeOwn;
}

void Game::enoughPlayers()
{
	if(!((int)players.size() >= min && (int)players.size() <= max))
	{
        View::display(name + ": Wrong number of players! " + to_string(players.size()) +
            " is not between " + to_string(min) + " and " + to_string(max) + "!", FG_RED);
        exit(EXIT_FAILURE);
    }
}