#include "combat.hpp"

combat::combat(/* args */)
{
}

combat::~combat()
{
}

void combat::rollInitiatives()
{
    for (auto &actor : actors)
    {
        actor->rollInitiative();
    }
    std::sort(actors.begin(), actors.end(), [](const std::shared_ptr<actor> &a, const std::shared_ptr<actor> &b)
              { return a->get_initiative() > b->get_initiative(); });
}

void combat::add_actor(actor &c)
{
    actors.push_back(std::shared_ptr<actor>(&c));
    actors.back()->assign_combat_hash(generateUUID());
}
void combat::add_actor_mid(actor &c)
{
    actors.push_back(std::shared_ptr<actor>(&c));
    actors.back()->assign_combat_hash(generateUUID());
    actors.back()->rollInitiative();
    std::sort(actors.begin(), actors.end(), [](const std::shared_ptr<actor> &a, const std::shared_ptr<actor> &b)
              { return a->get_initiative() > b->get_initiative(); });
}

std::string generateUUID()
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    return boost::uuids::to_string(uuid);
}

void combat::remove_effect(std::string uuid)
{
    for (auto it = effects.begin(); it != effects.end(); ++it)
    {
        if ((*it)->get_uuid() == uuid)
        {
            effects.erase(it);
            break;
        }
    }
}

void combat::stepRound()
{
    for (auto &actor : actors)
    {
        // Check for effects that should be activated
        for (auto &effect : effects)
        {
            if (effect->shouldActivate(*this))
            {
                effect->execute(*this);
            }
        }
        // Check for effects that should be deactivated
        for (auto &effect : effects)
        {
            if (effect->get_duration() == 0)
            {
                remove_effect(effect->get_uuid());
            }
        }
        // Let player make intended actions
        actor->make_strategy(*this);
        actor->make_actions(*this);
    }
    // decrement all effect durations
    for (auto &effect : effects)
    {
        effect->set_duration(effect->get_duration() - 1);
    }
}

std::shared_ptr<actor> combat::get_actor_by_uuid(std::string uuid)
{
    for (auto &actor : actors)
    {
        if (actor->get_combat_hash() == uuid)
        {
            return actor;
        }
    }
    return nullptr;
}
