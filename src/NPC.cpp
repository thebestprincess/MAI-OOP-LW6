#include "../include/NPC.h"

#include "../include/Visitor.h"
#include <cmath>

NPC::NPC(int x, int y): x(x), y(y) {}

bool NPC::is_close(const NPC& other, size_t distance) const 
{
    int delta_y = y - other.y;
    int delta_x = x - other.x;
    return std::pow(delta_x, 2) + std::pow(delta_y, 2) <= std::pow(distance, 2);
}

Squirrel::Squirrel(int x, int y): NPC(x, y) {}

void Squirrel::accept(NPCVisitor& visitor)
{
    visitor.visit(*this);
}

std::string Squirrel::get_type() const
{
    return "Squirrel";
}

Druid::Druid(int x, int y): NPC(x, y) {}

void Druid::accept(NPCVisitor& visitor)
{
    visitor.visit(*this);
}

std::string Druid::get_type() const
{
    return "Druid";
}

Werewolf::Werewolf(int x, int y): NPC(x, y) {}

void Werewolf::accept(NPCVisitor& visitor)
{
    visitor.visit(*this);
}

std::string Werewolf::get_type() const
{
    return "Werewolf";
}



