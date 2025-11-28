#include "../include/Factory.h"

#include <memory>
#include <stdexcept>

std::shared_ptr<NPC> NPCFactory::create_npc(const std::string& type, int x, int y)
{
    if (type == "Squirrel")
    {
        return std::make_shared<Squirrel>(x, y);
    }
    if (type == "Werewolf")
    {
        return std::make_shared<Werewolf>(x, y);
    }
    if (type == "Druid")
    {
        return std::make_shared<Druid>(x, y);
    }

    throw std::runtime_error("Unknown NPC type: " + type);
}