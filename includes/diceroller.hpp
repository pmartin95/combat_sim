#include <random>
#include <algorithm>
#pragma once

class diceroller
{
private:
    /* data */
    std::mt19937 rng;

public:
    diceroller(/* args */);
    ~diceroller();

    int roll(int numDice, int numSides);
    int rollNkeepbestK(int numDice, int numSides, int numKeep);
    int rollNkeepworstK(int numDice, int numSides, int numKeep);
};
