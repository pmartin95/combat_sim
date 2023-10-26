#include "actor.hpp"

actor::actor(/* args */)
{
}

actor::actor(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file " + filename);
    }
    nlohmann::json j;
    file >> j;
    file.close();
    name = j["name"];
    race = j["race"];
    actorClass = j["class"];
    level = j["level"];
    for (const auto &[key, value] : j["stats"].items())
    {
        stats[key] = value;
    }
    ac = j["armorClass"];
    max_hp = j["hitPoints"];
    current_hp = max_hp;
    calc_mods();
}

actor::~actor()
{
}
void actor::calc_mods()
{
    for (auto &stat : stats_save)
    {
        stats_mod[stat.first] = (stats[stat.first] - 10) / 2;
    }
    calc_saves();
}
void actor::calc_saves()
{
    for (auto &stat : stats_save)
    {
        stats_save[stat.first] = stats_mod[stat.first];
        if (stats_save_prof[stat.first])
        {
            stats_save[stat.first] += proficiency_bonus;
        }
    }
}

void actor::inputstats(const int (&stats_in)[6])
{
    auto it = stats.begin();
    for (int i = 0; i < 6; i++)
    {
        it->second = stats_in[i];
        ++it;
    }
    calc_mods();
}

void actor::inputstats(const std::map<std::string, int> &stats_in)
{
    stats.clear(); // if you want to replace the stats completely
    stats.insert(stats_in.begin(), stats_in.end());
    calc_mods();
}

void actor::rollInitiative()
{
    initiative = dice.roll(1, 20) + stats_mod["dex"];
}
int actor::rollSavingThrow(std::string stat)
{
    return dice.roll(1, 20) + stats_save[stat];
}

void actor::assign_combat_hash(std::string hash)
{
    combat_hash = hash;
}
void actor::add_action(std::shared_ptr<action> new_action)
{
    actions.push_back(new_action);
}
void actor::add_skill(std::string skill)
{
    skills.push_back(skill);
}

void actor::take_damage(int dmg, std::string dmg_type)
{
    if (utility::vectorContainsString(dmg_resistances, dmg_type))
    {
        dmg /= 2;
    }
    else if (utility::vectorContainsString(dmg_vulnerabilities, dmg_type))
    {
        dmg *= 2;
    }
    else if (utility::vectorContainsString(dmg_immunities, dmg_type))
    {
        dmg = 0;
    }
    current_hp -= dmg;
    if (current_hp < 0)
    {
        current_hp = 0;
    }
}
std::string actor::get_combat_hash()
{
    return combat_hash;
}

void actor::restoreHealth()
{
    current_hp = max_hp;
}

void actor::make_strategy(combat &combat_instance)
{
    strategy_instance->formulatePlan(*this, combat_instance);
}

void actor::make_actions(combat &combat_instance)
{
    for (auto &localAction : strategy_instance->get_actions())
    {
        if (localAction->get_actionType() == "attack")
        {
            std::vector<std::shared_ptr<actor>> targets{strategy_instance->get_nearestEnemy()};

            localAction->execute(*this, targets, combat_instance);
        }
        else if (localAction->get_actionType() == "heal")
        {
        }
        else if (localAction->get_actionType() == "move")
        {
            std::vector<std::shared_ptr<actor>> targets;
            localAction->execute(*this, targets, combat_instance);
        }
    }
}