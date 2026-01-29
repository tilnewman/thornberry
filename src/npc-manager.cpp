//
// npc-manager.cpp
//
#include "npc-manager.hpp"

namespace thornberry
{

    NpcManager::NpcManager()
        : m_npcs{}
    {}

    void NpcManager::setup(const Context &) {}

    void NpcManager::update(const Context & t_context, const float t_elapsedSec)
    {
        for (Npc & npc : m_npcs)
        {
            npc.update(t_context, t_elapsedSec);
        }
    }

} // namespace thornberry
