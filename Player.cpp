#include<iostream>
#include<sstream>
#include "Player.h"
using std::vector, std::string, std::size_t;

Player::Player(bool isAI) : isAI(isAI), hand({}) {}

void Player::addToHand(Card* c)
{
    // TODO: Add the card c to the player's hand
    this->hand.push_back(c);
}

size_t Player::getHandSize()
{
    // Implement getter
    return this->hand.size();
}

std::string Player::getHandString()
{
    // Implement getter
    std::string s = "";
    for (unsigned int i=0 ; i<hand.size() ; ++i)
    {
        s += hand[i]->getRank() + " " + hand[i]->getSuit();
        if (i < hand.size() - 1) s += ", ";
    }
    return s;
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit)
{
    // Choose a card to play and return the chosen card
    if (this->isAI) // if player is AI
    {
        for (unsigned int i=0 ; i<this->hand.size() ; ++i)
        {
            Card* currentCard = this->hand[i];
            // This technically handles 8's as well because the AI just chooses the cards suit
            if (currentCard->canBePlayed(currentRank, currentSuit))
            {
                currentCard->play();
                this->hand.erase(this->hand.begin() + i);
                currentRank = currentCard->getRank();
                currentSuit = currentCard->getSuit();
                return currentCard;
            }
        }
        return nullptr; // draw card if no card can be played
    }

    else // if player is not AI
    {
        std::cout << "Your hand contains: " << this->getHandString() << std::endl;
        std::cout << "The next card played must be a " << currentRank << " or " << currentSuit << std::endl;
        std::cout << "What would you like to play? (enter \"draw card\" to draw a card)\n";
        
        std::string rank, suit; std::cin >> rank >> suit;
        
        while (true)
        {
            if (rank == "draw" && suit == "card") return nullptr;

            bool cardInHand = false;
            bool eight = false;
            int currentCardIndex;
            Card* currentCard;

            if (rank == "8") eight = true;
            for (unsigned int i=0 ; i<this->hand.size() ; ++i)
            {
                currentCard = this->hand[i];
                if (currentCard->getRank() == rank && currentCard->getSuit() == suit)
                {
                    cardInHand = true;
                    currentCardIndex = i;
                    break;
                }
            }

            if (cardInHand && eight)
            {
                std::cout << "What suit would you like to declare?" << std::endl;
                std::string newSuit; std::cin >> newSuit;
                while (true)
                {   
                    bool validSuit = false;
                    for (std::string s : suits)
                    {
                        if (newSuit == s)
                        {
                            validSuit = true;
                            break;
                        }     
                    }

                    if (validSuit) break;
                    std::cout << "That's not a suit in this deck. Try again." << std::endl;
                    std::cin >> newSuit;
                }
                currentCard->play();
                this->hand.erase(this->hand.begin() + currentCardIndex);
                currentRank = currentCard->getRank();
                currentSuit = newSuit;
                return currentCard;
            }
            else if (cardInHand && currentCard->canBePlayed(currentRank, currentSuit))
            {
                currentCard->play();
                this->hand.erase(this->hand.begin() + currentCardIndex);
                currentRank = currentCard->getRank();
                currentSuit = currentCard->getSuit();
                return currentCard;
            }
            else if (!cardInHand)
            {
                std::cout << "That's not a card you have. Try again." << std::endl;
            }
            else 
            {
                std::cout << "You can't play that card. Try again." << std::endl;
            }

            std::cin >> rank >> suit;
        }
    }
}