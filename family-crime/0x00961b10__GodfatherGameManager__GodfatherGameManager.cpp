// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
undefined4* __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this, byte isHeapAllocated)
{
    // Set vtable pointers for multiple inheritance
    this->vtable1 = &VMT_GodfatherGameManager;          // +0x00
    this->vtable2 = &VMT_GodfatherGameManager_Base2;    // +0x10
    this->vtable3 = &VMT_GodfatherGameManager_Base3;    // +0x4C, temporary

    // Initialize subobject at offset 0x84 (e.g., a manager member)
    FUN_009c8eb0(this->subManager);                     // +0x84, called on subobject

    // Final vtable for most-derived class
    this->vtable3 = &VMT_GodfatherGameManager_Final;    // +0x4C

    // Set global manager flag
    gGameManagerInitialized = false;                    // DAT_011305a0 = 0

    // Perform global initialization (e.g., input, audio)
    FUN_005c16e0();

    // If object was heap-allocated, call the destructor (debug/custom delete)
    if ((isHeapAllocated & 1) != 0) {
        GodfatherGameManager::__destructor(this);       // FUN_005c4480
    }

    return this;
}