// FUNC_NAME: NPCManager::resetAllNPCStates
// Address: 0x00824ee0
// Iterates over all NPCs and clears a state flag in their behavior component,
// then calls a per-NPC processing function (FUN_00823f60).

void __fastcall NPCManager::resetAllNPCStates(NPCManager* this)
{
    uint idx = 0;
    // +0xac: count of NPCs in the array
    if (*(int*)((char*)this + 0xac) != 0) {
        do {
            // +0xa8: pointer to array of NPC pointers (size 4 each)
            // For each NPC, +0x5c points to its state/behavior component
            // Then +0x20 in that component is cleared (set to 0)
            *(int*)(*(int*)(*(int*)(*(int*)((char*)this + 0xa8) + idx * 4) + 0x5c) + 0x20) = 0;
            FUN_00823f60(); // per-NPC processing call
            idx++;
        } while (idx < *(uint*)((char*)this + 0xac));
    }
    return;
}