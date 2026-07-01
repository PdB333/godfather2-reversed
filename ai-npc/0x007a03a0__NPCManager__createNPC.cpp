// FUNC_NAME: NPCManager::createNPC
void __thiscall NPCManager::createNPC(void* thisPtr, byte flag)
{
    char isReady;
    int objAlloc;

    isReady = FUN_00481660(); // check if system is initialized
    if (isReady != 0) {
        objAlloc = FUN_009c8e50(0x40); // allocate 64 bytes for NPC object
        if (objAlloc != 0) {
            objAlloc = FUN_007a0250(thisPtr); // call NPC constructor with parent
            *(byte *)(objAlloc + 0x38) = flag; // set NPC type/flag at offset +0x38
            FUN_00481690(objAlloc); // register NPC in manager list
            return;
        }
        // fallback: store flag in static variable and register null
        DAT_00000038 = flag;
        FUN_00481690(0);
    }
}