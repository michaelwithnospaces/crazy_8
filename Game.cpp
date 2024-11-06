#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "Game.h"
using std::string, std::vector;

Game::Game(): players({}), suits({}), ranks({}), deck({}), drawPile({}), discardPile({}) {}

void Game::loadDeckFromFile(string filename)
{
    // initialize suits, ranks, deck, and drawPile from the given file
    std::string line, word;
    std::ifstream fs(filename);

    if (!(fs.is_open())) throw std::runtime_error("Could not open file.");

    if (getline(fs, line))
    {
        std::stringstream s(line);
        while (s >> word)
        {
            suits.push_back(word);
        }
    }
    
    if (getline(fs, line))
    {
        std::stringstream s(line);
        while (s >> word)
        {
            ranks.push_back(word);
        }
    }

    while (getline(fs, line))
    {
        std::string rank, suit, extra;
        std::stringstream s(line);
        if (!(s >> rank >> suit)) throw std::runtime_error ("Too little information.");
        if (s >> extra) throw std::runtime_error("Too much information");

        Card* card = new Card(rank, suit);
        deck.push_back(card);
        drawPile.insert(drawPile.begin(), card);
    }
}

void Game::addPlayer(bool isAI)
{
    // add a new player to the game
    Player* player = new Player(isAI);
    players.push_back(player);
}

void Game::drawCard(Player* p)
{
    // Move the top card of the draw pile to Player p's hand
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
Game::~Game()
{
    for (unsigned int i = 0; i < deck.size(); i++)
    {
        delete deck.at(i);
    }
    for (unsigned int i = 0; i < players.size(); i++) 
    {
        delete players.at(i);
    }
}