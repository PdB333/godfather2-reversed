// FUNC_NAME: SystemManager::updateState
void __fastcall SystemManager::updateState(int *thisPtr)
{
    // Reset global flag indicating some processing state
    g_bProcessingActive = 0;

    // Check if this system is allowed to update (virtual function at vtable+0xEC)
    bool isActive = (*(code **)(*thisPtr + 0xEC))();

    if (isActive)
    {
        resetAllProcessingFlags();          // FUN_005ef7a0
        processSubComponent(thisPtr, thisPtr[3]); // FUN_005ef5f0: process object at offset +0xC
    }
}