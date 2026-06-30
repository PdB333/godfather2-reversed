// FUNC_NAME: NPCManager::updateActiveNPCs
void __thiscall NPCManager::updateActiveNPCs(void)
{
    // Count of NPCs stored at this+0x14
    int npcCount = *(int *)((char *)this + 0x14);
    // Pointer to array of NPC objects (each 0x114 bytes) at this+0x10
    int *npcArray = *(int **)((char *)this + 0x10);

    // Iterate from last to first (reverse order)
    for (int idx = npcCount - 1; idx >= 0; idx--)
    {
        int *currentNPC = (int *)((char *)npcArray + idx * 0x114);
        // Check flags at offset +0x10c: mask 0x6 (bits 1-2), expecting value 2 (bit1 set, bit2 clear)
        if ((*(unsigned int *)((char *)currentNPC + 0x10c) & 6) == 2)
        {
            // Process NPC that matches state criteria
            FUN_005ca760(); // NPCManager::processNPCState(currentNPC)
        }
    }
    return;
}