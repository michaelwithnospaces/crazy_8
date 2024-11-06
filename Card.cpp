#include<cctype>
#include<stdexcept>
#include "Card.h"
using std::string;

Card::Card(string rank, string suit) : rank(rank), suit(suit) 
{
    // constructor checks
    for (char c : rank)
    {
        if (!isalnum(c)) throw std::invalid_argument("Rank contains a value that is not alphanumeric.");
    }
    for (char c : suit)
    {
        if (!isalnum(c)) throw std::invalid_argument("Suit contains a value that is not alphanumeric.");
    }
}

string Card::getRank()
{
    return this->rank;
}

string Card::getSuit()
{
    return this->suit;
}

int Card::getTimesPlayed()
{
    return this->timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit)
{
    // return whether or not the card can legally be played
    if (this->rank == "8") return true;
    if (currentRank == this->rank || currentSuit == this->suit) return true;
    return false; 
}

void Card::play()
{
    timesPlayed++;
}