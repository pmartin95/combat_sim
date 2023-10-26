#include "diceroller.hpp"
#include "random"

diceroller::diceroller(/* args */)
{
    std::random_device rd;
    rng = std::mt19937(rd());
}

diceroller::~diceroller()
{
}

int diceroller::roll(int numDice, int numSides)
{
    std::uniform_int_distribution<int> dist(1, numSides);
    int sum = 0;
    for (int i = 0; i < numDice; i++)
    {
        sum += dist(rng);
    }
    return sum;
}

int diceroller::rollNkeepbestK(int numDice, int numSides, int numKeep)
{
    std::uniform_int_distribution<int> dist(1, numSides);
    int sum = 0;
    int rolls[numDice];
    for (int i = 0; i < numDice; i++)
    {
        rolls[i] = dist(rng);
    }
    std::sort(rolls, rolls + numDice);
    for (int i = numDice - 1; i >= numDice - numKeep; i--)
    {
        sum += rolls[i];
    }
    return sum;
}

int diceroller::rollNkeepworstK(int numDice, int numSides, int numKeep)
{
    std::uniform_int_distribution<int> dist(1, numSides);
    int sum = 0;
    int rolls[numDice];
    for (int i = 0; i < numDice; i++)
    {
        rolls[i] = dist(rng);
    }
    std::sort(rolls, rolls + numDice);
    for (int i = 0; i < numKeep; i++)
    {
        sum += rolls[i];
    }
    return sum;
}
