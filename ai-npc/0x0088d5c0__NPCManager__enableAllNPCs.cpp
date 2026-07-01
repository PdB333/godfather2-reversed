// FUNC_NAME: NPCManager::enableAllNPCs
// Address: 0x0088d5c0
// Role: Sets the 'active' flag (byte at +0xAC) for all NPCs in the manager's list to 1.
void __thiscall NPCManager::enableAllNPCs()
{
    if (npcCount != 0) {
        for (int i = 0; i < npcCount; i++) {
            // npcList[i] offset +0xAC is the 'active' flag
            npcList[i]->active = true;
        }
    }
}