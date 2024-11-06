#include<iostream>
#include<sstream>
#include "Player.h"
using std::vector, std::string, std::size_t;

Player::Player(bool isAI) /* TODO: initialize */ 
{

}

void Player::addToHand(Card* c)
{
    // TODO: Add the card c to the player's hand
}

size_t Player::getHandSize()
{
    // TODO: Implement getter
}

std::string Player::getHandString()
{
    // TODO: Implement getter
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit)
{
    // TODO: Choose a card to play and return the chosen card
}