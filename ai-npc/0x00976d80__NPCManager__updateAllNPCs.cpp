// FUNC_NAME: NPCManager::updateAllNPCs
void __thiscall NPCManager::updateAllNPCs(bool forceUpdate) {
    int* group;
    uint count;
    int* npcList;
    int npc;
    
    group = (int*)getSimGroup(*(int*)(this + 0x13C));
    if (group != nullptr && group[0x98 / 4] != 0) {
        npcList = (int*)group[0x94 / 4];
        count = 0;
        while (count < (uint)group[0x98 / 4]) {
            npc = npcList[count];
            // Skip if type is 9 and not in a valid state via some check
            if (npc[0xC4 / 4] != 9 || isEntityValid(*(int*)(npc + 0x38)) != 0) {
                if (forceUpdate) {
                    updateAI(npc);       // FUN_0097e200
                } else {
                    updateNormal(npc);   // FUN_0097d800
                }
            }
            count++;
        }
    }
}