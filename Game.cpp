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
    std::ifstream file(filename);
    if (!(file.is_open())) throw std::runtime_error("Could not open file.");

    std::string line;
    std::stringstream ss;

    // read in suits
    if (getline(file, line))
    {
        std::string word;
        ss.clear();
        ss.str(line);
        while (ss >> word) suits.push_back(word);
    }

    // read in ranks
    if (getline(file, line))
    {
        std::string word;
        ss.clear();
        ss.str(line);
        while (ss >> word) ranks.push_back(word);
    }

    while (getline(file, line))
    {
        std::string suit, rank;
        bool suitExists = false;
        bool rankExists = false;
        ss.clear();
        ss.str(line);
        
        // check for too few values
        if (ss >> rank >> suit)
        {
            // check for extra values
            std::string extra;
            if (ss >> extra) throw std::runtime_error("Too many values");

            // check if rank is in list of ranks
            for (std::string r : ranks)
            {
                if (rank == r)
                {
                    rankExists = true;
                    break;
                }
            }
            // check if suit is in list of suits
            for (std::string s : suits)
            {
                if (suit == s)
                {
                    suitExists = true;
                    break;
                }
            }

            if (!(rankExists && suitExists)) throw std::runtime_error("rank or suit does not exist");

            try
            {
                Card* newCard = new Card(rank, suit);
                deck.push_back(newCard);
                drawPile.insert(drawPile.begin(), newCard);
            }
            catch(const std::exception& e)
            {
                throw std::runtime_error(e.what());
            }
            
        }
        else throw std::runtime_error("Missing value");
    }
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