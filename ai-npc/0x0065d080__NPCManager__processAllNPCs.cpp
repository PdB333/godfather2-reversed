// FUNC_NAME: NPCManager::processAllNPCs
// Function address: 0x0065d080
// Iterates over all NPCs from the SimManager singleton and processes each via a virtual dispatch.

// The global function at 0x00ad8d40 returns a singleton instance (likely SimManager or EntityManager).
// Offsets:
//   +0x34 on manager: getNPCList (returns container of NPC pointers)
//   +0x20 on container: getCount (returns uint32 numNPCs)
//   +0x24 on container: getNPCAt(uint32 index) (returns NPC*)
//   +0x20 on this: processNPC(NPC* npc)

typedef void* (__thiscall* GetSingletonFunc)();   // 0x00ad8d40 style
typedef void* (__thiscall* GetListFunc)(void* mgr);
typedef uint32_t (__thiscall* GetCountFunc)(void* list);
typedef int* (__thiscall* GetAtFunc)(void* list, uint32_t index);
typedef void (__thiscall* ProcessNpcFunc)(void* thisObj, int* npc);

void __thiscall NPCManager::processAllNPCs()
{
    void* manager = reinterpret_cast<GetSingletonFunc>(0x00ad8d40)();
    void* npcList = nullptr;

    if (manager != nullptr)
    {
        npcList = reinterpret_cast<GetListFunc>(*reinterpret_cast<uint32_t*>(manager) + 0x34)();
    }
    else
    {
        npcList = nullptr;
    }

    uint32_t count = reinterpret_cast<GetCountFunc>(*reinterpret_cast<uint32_t*>(npcList) + 0x20)();

    for (uint32_t i = 0; i < count; ++i)
    {
        int* npc = reinterpret_cast<GetAtFunc>(*reinterpret_cast<uint32_t*>(npcList) + 0x24)(i);
        if (npc != nullptr)
        {
            reinterpret_cast<ProcessNpcFunc>(*reinterpret_cast<uint32_t*>(this) + 0x20)(npc);
        }
    }
}