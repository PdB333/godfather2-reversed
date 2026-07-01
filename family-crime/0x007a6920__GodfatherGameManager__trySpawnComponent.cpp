// FUNC_NAME: GodfatherGameManager::trySpawnComponent
void __fastcall GodfatherGameManager::trySpawnComponent(GodfatherGameManager* this)
{
    char isReady;
    int allocatedPtr;
    void* newComponent;

    FUN_009ae900(0);                                          // global initialization step? param 0 = possible reset
    if (*(int*)((int)this + 0x3148) != 0) {                   // +0x3148: existing component pointer? If non-null, cleanup
        FUN_004df600();                                       // cleanup/release previous component
    }
    isReady = FUN_00481660();                                 // check game state (e.g. multiplayer, loading complete)
    if (isReady) {
        allocatedPtr = FUN_009c8e50(0x38);                    // allocate 56 bytes for component
        if (allocatedPtr != 0) {
            newComponent = FUN_007a09b0(this);                // construct/initialize component using `this`
            FUN_00481690(newComponent);                       // register/store component (e.g., add to manager list)
            return;
        }
        FUN_00481690(0);                                      // allocation failed, store null
    }
    return;
}