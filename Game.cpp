#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "Game.h"
using std::string, std::vector;

Game::Game(): players({}), suits({}), ranks({}), deck({}), drawPile({}), discardPile({}) {}

void Game::loadDeckFromFile(string filename)
{
    // TODO: initialize suits, ranks, deck, and drawPile from the given file
}

void Game::addPlayer(bool isAI)
{
    // TODO: add a new player to the game
}

void Game::drawCard(Player* p)
{
    // TODO: Move the top card of the draw pile to Player p's hand
    // If the draw pile is empty, flip the discard pile to create a new one
}

//deals numCards cards to each player
Card* Game::deal(int numCards)
{
    // TODO: Flip the top card of the draw pile to be the initial discard
    // then deal numCards many cards to each player
}

string Game::mostPlayedSuit()
{
    // TODO: Return the suit which has been played the most times
    // if there is a tie, choose any of the tied suits
}

int Game::runGame()
{
    // TODO: Run the game and return the number of the winning player
}

//Destructor--Deallocates all the dynamic memory we allocated
Game::~Game(){
    for (unsigned int i = 0; i < deck.size(); i++)
    {
        delete deck.at(i);
    }
    for (unsigned int i = 0; i < players.size(); i++) 
    {
        delete players.at(i);
    }
}