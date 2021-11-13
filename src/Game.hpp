#ifndef Game_HPP
#define Game_HPP

#include "DeckBuilder.hpp"
#include "Player.hpp"
#include "Deck.hpp"
#include "View.hpp"

/**
 *  Abstract class for card games
 *  This class need to be extend to implement card games
 *  We tried to make it generic as much as possible
 */
class Game
{
private:
	const string name;

    /**
     * Players number min and max to play the game
     * Permissions to see card on the board or which are in player hands
     */
    const int min, max, seeBoard, seeOwn;

    /**
     * Check if player number is between min and max
     */
    void enoughPlayers();
	
protected:

    /**
     * Index of the player turn
     */
	int turnToPlay = 0;

	/**
	 * Direction clockwise and counterclockwise
	 */
    bool direction = false;

    /**
     * Players of the game
     */
	vector<Player *> players;

	/**
	 * Deck of the game
	 * Contains cards of the pick and board
	 */
	Deck *deck = nullptr;

public:

    /**
     * Constructor
	 * @param name
	 * @param min
	 * @param max
	 * @param seeBoard
	 * @param seeOwn
     */
	Game(string, unsigned int, unsigned int, int, int);

	/**
	 * Destroy the Game object
	 */
	virtual ~Game();

	void clean();

	/**
	 * The current player take a card
	 */
	void draw();

	/**
	 * Get the current player whose turn it is
	 */
    Player *turnOf() const;

    /**
      * Get the next player whose turn it is
      */
    Player *nextPlayer();

    /**
      * Iterate the turn
      */
	void nextTurn();

	/**
	 * Check if the current player has playable card
	 */
	bool hasPlayable();

	/**
	 * Init the game with pack of cards
	 * and distribution of card to players
	 * @param cards
	 * @param distrib
	 */
	void init(vector<Card *>, int);

	/**
	 * Start of the game
	 */
	virtual void start() = 0;

	/**
	 * Iteration of game with users inputs
	 * @param inputs
	 */
	virtual void iterate(vector<int>) = 0;

	/**
	 * Simulate robot input based on game rules
	 */
	virtual vector<int> automatic() = 0;

	/**
	 * Check for winners
	 */
	virtual Player *checkForWinners() = 0;

	/**
	 * Check if game can continue
	 */
	virtual bool canContinue() = 0;

	/**
	 * Check if the card is playable
	 */
	virtual bool isPlayable(Card *) = 0;

	/**
	 * Get the message which needs to be displayed
	 */
	virtual vector<string> messages(int) = 0;

	/**
	 * Returns a number of inputs to ask for given a specific step
	 */
	virtual int InputMessages(int, int,bool *) = 0;

    /**
     * Getters
     */
    Deck * getDeck() const;
    vector<Player *> getPlayers() const;
    const string getName() const;
    int const getMin() const;
    int const getMax() const;
    int const getSeeBoard() const;
    int const getSeeOwn() const;

    /**
     * Setters
     */
    void setPlayers(vector<Player *>);
};

#endif