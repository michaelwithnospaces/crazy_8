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
    // add a new player to the game
    Player* newPlayer = new Player(isAI);
    players.push_back(newPlayer);
}

void Game::drawCard(Player* p)
{
    // Move the top card of the draw pile to Player p's hand
    // If the draw pile is empty, flip the discard pile to create a new one
    if (drawPile.empty())
    {
        if (discardPile.size() > 1)
        {
            std::cout << "Draw pile, empty, flipping the discard pile." << std::endl;

            for (int i=discardPile.size()-2 ; i>=0 ; --i)
            {
                drawPile.push_back(discardPile[i]);
            }

            // clear discard pile
            Card* topCard = discardPile.back();
            discardPile.clear();
            discardPile.push_back(topCard);


        }
        else
        {
            throw std::runtime_error("Discard pile empty");
        }
    }

    // draw card
    Card* cardDrawn = drawPile.back();
    drawPile.pop_back();
    p->addToHand(cardDrawn);
}

//deals numCards cards to each player
Card* Game::deal(int numCards)
{
    // Flip the top card of the draw pile to be the initial discard
    // then deal numCards many cards to each player
    if (drawPile.empty()) 
    {
        throw std::runtime_error("Draw pile is empty at start of deal");
    }

    Card* topCard = drawPile.back();
    discardPile.push_back(topCard);
    drawPile.pop_back();

    try
    {
        for (int i=0 ; i<numCards ; ++i)
        {
            for (Player* player : players)
            {
                drawCard(player);
            }
        }
    }
    catch(const std::exception& e)
    {
        throw std::runtime_error(e.what());
    }
    
    return topCard;
}

string Game::mostPlayedSuit()
{
    // Return the suit which has been played the most times
    // if there is a tie, choose any of the tied suits
    vector<int> suitCount(suits.size(), 0);

    for (Card* card : deck)
    {
        std::string currentSuit = card->getSuit();
        int timesPlayed = card->getTimesPlayed();

        for (unsigned int i=0 ; i<suits.size() ; ++i)
        {
            if (currentSuit == suits[i])
            {
                suitCount[i] += timesPlayed;
                break;
            }
        }
    }

    int largest = 0;
    int largestIndex = -1;
    for (unsigned int i=0 ; i<suitCount.size() ; ++i)
    {
        if (suitCount[i] > largest)
        {
            largest = suitCount[i];
            largestIndex = i;
        }
    }

    return suits[largestIndex];
}

int Game::runGame()
{
    // Run the game and return the number of the winning player
    std::string currentRank = discardPile.back()->getRank();
    std::string currentSuit = discardPile.back()->getSuit();

    while (true)
    {
        for (unsigned int i=0 ; i<players.size() ; ++i)
        {
            std::cout << "Player " << i <<"'s turn!" << std::endl;

            Card* currentCard = players[i]->playCard(suits, currentRank, currentSuit);

            if (currentCard == nullptr)
            {
                try
                {
                    drawCard(players[i]);
                    std::cout << "Player " << i << " draws a card." << std::endl;
                }
                catch(const std::runtime_error& e)
                {
                    std::cout << "Player " << i << " cannot draw a card." << std::endl;
                    return -1;
                }
            }
            else
            {
                discardPile.push_back(currentCard);
                std::cout << "Player " << i << " plays " << currentCard->getRank() << " " << discardPile.back()->getSuit();
                if (currentCard->getRank() == "8") std::cout << " and changes the suit to " << currentSuit;
                std::cout << "." << std::endl;
            }

            if (players[i]->getHandSize() == 0) return i;
        }
    }
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