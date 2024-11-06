#include<cctype>
#include<stdexcept>
#include "Card.h"
using std::string;

Card::Card(string rank, string suit) /* TODO: initialize */ 
{
    // TODO: implement constructor checks
}

string Card::getRank()
{
    // TODO: implement getter
}

string Card::getSuit()
{
    // TODO: implement getter
}

int Card::getTimesPlayed()
{
    // TODO: implement getter
}

bool Card::canBePlayed(string currentRank, string currentSuit)
{
    // TODO: return whether or not the card can legally be played
}

void Card::play()
{
    timesPlayed++;
}