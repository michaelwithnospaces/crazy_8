#include<iostream>
#include<sstream>
#include "Player.h"
using std::vector, std::string, std::size_t;

Player::Player(bool isAI) : isAI(isAI) {}

void Player::addToHand(Card* c)
{
    // Add the card c to the player's hand
    this->hand.push_back(c);
}

size_t Player::getHandSize()
{
    return this->hand.size();
}

std::string Player::getHandString()
{
    std::string handString = "";
    for (size_t i=0 ; i<hand.size() ; ++i)
    {
        handString += hand[i]->getRank() + " " + hand[i]->getSuit();
        if (i != hand.size() - 1) handString += ", ";
    }
    return handString;
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit)
{
    
}