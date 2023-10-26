#pragma once
#include <string>
#include <algorithm>
#include <random>
#include <vector>
#include <random>
#include <iostream>
#include "diceroller.hpp"
#include "actor.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

class effect;
class actor;
class action;
class diceroller;

class combat
{
private:
    /* data */
    std::vector<std::shared_ptr<actor>> actors;
    std::vector<std::shared_ptr<effect>> effects;
    std::vector<int> initiatives;
    int gridSize[2] = {100, 100}; // [x, y]

public:
    combat(/* args */);
    ~combat();
    void rollInitiatives();
    void add_actor(actor &c);
    void add_actor_mid(actor &c);
    void add_effect(effect &e);
    void remove_effect(std::string uuid);
    void stepRound();
    std::vector<std::shared_ptr<actor>> &get_actors() { return actors; }
    std::shared_ptr<actor> get_actor_by_uuid(std::string uuid);
};

std::string generateUUID();
