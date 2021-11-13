#ifndef TEST_HPP
#define TEST_HPP

#include "DeckBuilder.hpp"
#include "Player.hpp"
#include "CrazyEights.hpp"
#include "Briscola.hpp"
#include <assert.h>

#define DECK_32 32
#define DECK_52 52
#define DECK_52_JOKERS 54
#define DECK_UNO 108
#define DECK_40 40

class Test {
public:
    static void unitTest(){

        /** Check for DeckBuilder */
        assert(DeckBuilder::generate32().size() == DECK_32);
        assert(DeckBuilder::generate52(false).size() == DECK_52);
        assert(DeckBuilder::generate52(true).size() == DECK_52_JOKERS);
        assert(DeckBuilder::generateUno().size() == DECK_UNO);
        assert(DeckBuilder::generate40().size() == DECK_40);

        vector<Card *> cards = DeckBuilder::generate32();
        assert(cards[0]->getId() != cards[1]->getId());

        /** Check for Deck */
        Deck *deck = new Deck();
        deck->setDeck(DeckBuilder::generate32());
        assert(deck->getDeck().size() == DECK_32);

        deck->addOnBoard(deck->drawCard());
        assert(deck->getDeck().size() == (DECK_32 - 1));
        assert(deck->getBoard().size() ==  1);

        while(deck->getDeck().size() > 1) deck->addOnBoard(deck->drawCard());

        assert(deck->getDeck().size() == 1);
        deck->fromBoardToDeck();
        assert(deck->getDeck().size() == (DECK_32 - 1));

        /** Check for players */
        Player *player = new Player("John");
        assert(player->getName().compare("John") == 0);
        player->addCard(cards[0]);
        player->addCard(cards[1]);
        player->removeCard(cards[0]);
        assert(player->getCards().size() == 1);

        /** Checks for CrazyEights */
        CrazyEights *crazy = new CrazyEights();
        crazy->setPlayers({new Player("robot"), new Player("robot")});
        crazy->start();

        /** Check for function isPlayable */
        Card *card = new Card(7, HEART);
        crazy->getDeck()->addOnBoard(card);
        assert(crazy->getDeck()->getLastOnBoard()->getId() == card->getId());
        assert(crazy->isPlayable(new Card(7, CLOVER)));
        assert(crazy->isPlayable(new Card(9, HEART)));

        Card *card1 = new Card(8, HEART);
        card1->setHint(DIAMOND);
        crazy->getDeck()->addOnBoard(card1);
        assert(crazy->isPlayable(new Card(4, DIAMOND)));
        assert(!crazy->isPlayable(new Card(4, HEART)));

        /** Checks Briscola */
        Briscola *briscola = new Briscola();
        int sum = 0;
        vector<Card *> cards40 = DeckBuilder::generate40();
        for(Card *card : cards40) sum += briscola->getScore(card);
        assert(sum == 120);
    }
};

#endif
