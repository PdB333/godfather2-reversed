// FUNC_NAME: GodfatherGameManager::resetAudioSystem
// Function address: 0x006ae200
// This function reads a member at +0x180 (probably an audio manager), sets up a temporary object, and calls a global reset function with a flag of 0.

int __thiscall GodfatherGameManager::resetAudioSystem(int this, int param2, int param3)
{
    int* audioManager = *(int**)(this + 0x180); // +0x180: pointer to audio subsystem manager
    int globalHandle = DAT_0112a610; // global audio handle
    // Temporary stack object: vtable pointer chain (PTR_LAB_00d5dbb4)
    void* vtablePointer = &PTR_LAB_00d5dbb4;
    void* selfReference = &vtablePointer;
    (void)param2; // unused parameter
    (void)param3; // unused parameter
    (void)audioManager; // member read but not used
    // Call global reset function with address of handle and 0 (reset flag)
    FUN_00408a00(&globalHandle, 0);
    return 0;
}