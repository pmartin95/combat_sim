#pragma once
#include <string>
#include <random>
#include <fstream>
#include <algorithm>
#include <map>
#include <memory>
#include "json.hpp"
#include "diceroller.hpp"
#include "action.hpp"
#include "utility.hpp"
#include "combat.hpp"

class action;
class actor;
class combat;

class effect
{
protected:
    std::string name;
    std::string uuid;
    std::string effectType;
    std::string actionTrigger;
    bool isActive = false;
    int duration = 0;

public:
    effect(/* args */) {}
    virtual ~effect() {}

    virtual void execute(combat &battlefield) = 0; // Pure virtual function
    virtual bool shouldActivate(combat &battlefield) = 0;
    virtual void deactivate() = 0;
    int get_duration() { return duration; }
    std::string get_uuid() { return uuid; }
    std::string get_name() { return name; }
    std::string get_effectType() { return effectType; }
    std::string get_actionTrigger() { return actionTrigger; }
    void set_duration(int d) { duration = d; }
    void set_uuid(std::string u) { uuid = u; }
    void set_name(std::string n) { name = n; }
    void set_effectType(std::string e) { effectType = e; }
    void set_actionTrigger(std::string a) { actionTrigger = a; }
};
