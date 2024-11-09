#include<iostream>
#include<fstream>
#include<string>
#include "Card.h"
#include "Player.h"
#include "Game.h"
using std::string;

bool loadDeck(Game& g)
{
    string filename;
    std::cout << "Choose a file to load the deck from:" << std::endl;
    std::cin >> filename;
    try
    {
        g.loadDeckFromFile(filename);
    }
    catch(std::runtime_error const&)
    {
        std::cout << "The file was invalid. Aborting." << std::endl;
        return false;
    }
    return true;
}

int getPlayerCount()
{
    std::cout << "Enter number of players:" << std::endl;
    int numPlayers;
    while(true)
    {
        if((!(std::cin >> numPlayers)) || numPlayers <= 0)
        {
            if(std::cin.fail())
            {
                // Clear the fail flag
                std::cin.clear();
                // Remove the non-integer data from the stream
                string garbage;
                std::cin >> garbage;
            }
            std::cout << "Please enter a positive number" << std::endl;
        }
        else
        {
            //break out of the loop once we've read a valid number
            break;
        }
    }
    return numPlayers;
}

void setupPlayers(Game& g, int numPlayers)
{
    // Determine whether each player is a human or an AI
    // and add them to the game
    for (int i=0 ; i<numPlayers ; ++i)
    {
        std::cout << "Is player " << i << " an AI? (y/n)" << std::endl;
        
        char input; std::cin >> input;

        while (!(input == 'y' || input == 'n'))
        {
            std::cout << "Please enter y or n" << std::endl;
            std::cin >> input;
        }

        switch (input)
        {
        case 'y':
            g.addPlayer(true);
            break;
        
        case 'n':
            g.addPlayer(false);
            break;
        }
    }
}

void setupGame(Game& g)
{
    // Determine how many cards to deal, deal the cards, and
    // print the initial discard
    std::cout << "How many cards should each player start with?" << std::endl;
    
    int input;

    while (true)
    {
        if (!(std::cin >> input) || (input <= 0))
        {
            if (std::cin.fail())
            {
                std::cin.clear();
                std::string garbage;
                std::cin >> garbage;
            }
            std::cout << "Please enter a positive number" << std::endl;
        }
        else
        {
            break;
        }
    }

    Card* card = g.deal(input);

    std::cout << "The initial discard is " << card->getRank() << " " << card->getSuit() << std::endl;
}

int main()
{
    Game g;
    if(!loadDeck(g))
    {
        return 1;
    }
    int numPlayers = getPlayerCount();
    setupPlayers(g,numPlayers);
    setupGame(g);
    int winner = g.runGame();
    if(winner != -1)
    {
        std::cout << "Player " << winner << " wins!" << std::endl;
    }
    else
    {
        std::cout << "The game is a draw!" << std::endl;
    }
    std::cout << "The most played suit was " << g.mostPlayedSuit() << std::endl;
    return 0;
}