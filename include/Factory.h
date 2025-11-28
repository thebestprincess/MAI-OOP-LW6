#ifndef FACTORY_H
#define FACTORY_H

#include "NPC.h"
#include <memory>

class NPCFactory
{
public:
    static std::shared_ptr<NPC> create_npc(const std::string& type, int x, int y);
};


#endif // FACTORY_H