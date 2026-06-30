// FUNC_NAME: EntityController::processCommand
bool __fastcall EntityController::processCommand(void* thisPtr)
{
    // +0x00: vtable (implicit)
    // +0xe8: pointer to data/behavior object
    // +0x120: command buffer (input data)
    // +0x130: value to write to active context

    EntityController* self = (EntityController*)thisPtr;
    void* pData = *(void**)(self + 0xe8);          // +0xe8
    if (pData == nullptr)
        return false;

    // Process data with command buffer; returns success flag
    // FUN_005e2ce0 likely a validation/processing function
    char success = ProcessData(pData, (char*)(self + 0x120));   // +0x120

    // Global state: likely g_bGameActive or g_bMissionRunning
    // DAT_0122350c + 0x1744 is often a byte flag in EARS global context
    bool bGameActive = *(bool*)(DAT_0122350c + 0x1744);
    if (bGameActive)
    {
        // FUN_005e2150 returns a pointer to the current mission/context object
        // Could be GetActiveContext() or GetCurrentMission()
        int* pContext = (int*)GetActiveContext();   // returns int for pointer offset arithmetic
        if (pContext != nullptr)
        {
            // +0x24c is likely a member field (e.g., m_commandedValue)
            pContext[0x24c / 4] = *(int*)(self + 0x130);   // +0x130
            return success != 0;
        }
    }
    return false;
}