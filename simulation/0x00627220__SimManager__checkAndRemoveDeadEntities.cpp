//FUNC_NAME: SimManager::checkAndRemoveDeadEntities
void SimManager::checkAndRemoveDeadEntities(void* entity) {
    // entity is a pointer to some game object (e.g., Sentient, NPC, Player)
    // g_simManager is a global pointer to the SimManager singleton (unaff_EDI)
    SimManager* simMgr = g_simManager; // unaff_EDI
    int* entityData = *(int**)((char*)entity + 0x10); // +0x10: pointer to entity data block

    // Check first condition: some count at simMgr+0x10+0x34 > 3 and flags at simMgr+0x10+0x38+5 have bits 0x11 clear
    if (*(int*)(*(int*)((char*)simMgr + 0x10) + 0x34) > 3 &&
        (*(unsigned char*)(*(int*)(*(int*)((char*)simMgr + 0x10) + 0x38) + 5) & 0x11) == 0) {
        removeEntity(); // FUN_00626640
    }

    // Check second condition: similar but with offsets 0x2c and 0x30
    if (*(int*)(*(int*)((char*)simMgr + 0x10) + 0x2c) > 3 &&
        (*(unsigned char*)(*(int*)(*(int*)((char*)simMgr + 0x10) + 0x30) + 5) & 0x11) == 0) {
        removeEntity(); // FUN_00626640
    }

    updateEntity(); // FUN_00626ac0

    // Final check: if simMgr is not equal to entityData+0x3c and simMgr's own flags at +5 have bits 0x11 clear
    if (simMgr != *(void**)((char*)entityData + 0x3c) &&
        (*(unsigned char*)((char*)simMgr + 5) & 0x11) == 0) {
        removeEntity(); // FUN_00626640
        return;
    }
}