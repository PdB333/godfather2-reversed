// FUNC_NAME: NPCManager::findNPCByFilter
// Function address: 0x008fa220
// Searches for an NPC matching a given condition (e.g., enemy team) within the NPC manager.
// Uses the global NPC manager's count of objects and iterates to find a valid, alive NPC satisfying the filter.
// Returns a pointer to the NPC (as int) or 0 if none found.

int NPCManager::findNPCByFilter(NPCManager* manager, int filterParam)
{
    // Check if the manager is valid/initialized
    if (!NPCManager::isValid(manager)) {
        return 0;
    }

    // Get global NPC manager instance (or some manager singleton)
    NPCManager* globalManager = NPCManager::getInstance();
    if (globalManager != 0) {
        int npcCount = *(int*)(globalManager + 0x50); // +0x50: number of NPCs registered
        for (int index = 0; index < npcCount; ++index) {
            // Get NPC by index
            int npc = NPCManager::getNPCByIndex(globalManager, index);
            if (npc != 0) {
                // Check if NPC is alive/active
                int aliveStatus = Sentient::isAlive(npc, 0);
                if (aliveStatus != 0) {
                    // Check filter condition (e.g., enemy team, specific type)
                    char conditionMet = Sentient::meetsFilterCondition(npc, filterParam); // FUN_008f78b0
                    if (conditionMet != 0) {
                        return npc; // Found matching NPC
                    }
                }
            }
        }
    }
    return 0;
}