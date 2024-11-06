#include<cctype>
#include<stdexcept>
#include "Card.h"
using std::string;

Card::Card(string rank, string suit) : rank(rank), suit(suit), timesPlayed(0) 
{
    // implement constructor checks
    if (rank.empty() || suit.empty())
    {
        throw std::invalid_argument("rank or suit empty.");
    }

    for (char c : rank)
    {
        if (!isalnum(c))
        {
            throw std::invalid_argument("rank contains non alpha-numeric value.");
        }
    }

    for (char c : suit)
    {
        if (!isalnum(c))
        {
            throw std::invalid_argument("suit contains non alpha-numeric value.");
        }
    }
}

string Card::getRank()
{
    // implement getter
    return this->rank;
}

string Card::getSuit()
{
    // implement getter
    return this->suit;
}

int Card::getTimesPlayed()
{
    // implement getter
    return this->timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit)
{
    // return whether or not the card can legally be played
    if (this->rank == currentRank || this->suit == currentSuit || this->rank == "8")
    {
        return true;
    }
    return false;
}

void Card::play()
{
    timesPlayed++;
}