// FUNC_NAME: GodfatherGameManager::setDebugMode
void __thiscall GodfatherGameManager::setDebugMode(GodfatherGameManager* this, bool enabled)
{
    // Offset +0x1F4 (500): debugModeEnabled flag
    *(char*)((int)this + 0x1F4) = enabled ? 1 : 0;

    // Offset +0x144: isDebugging flag (bool)
    *(bool*)((int)this + 0x144) = !enabled;

    if (!enabled)
    {
        // Set our own debug flag to 0
        *(char*)((int)this + 0x1F4) = 0;
        // Set global singleton debug state to 0 (offset +0xd3)
        *(char*)((int)DAT_01129914 + 0xd3) = 0;
        // Call disable-related functions
        FUN_0095eb90(false);
        FUN_0095e490();
    }
    else
    {
        // Set debug flags to 1
        *(char*)((int)this + 0x1F4) = 1;
        *(char*)((int)DAT_01129914 + 0xd3) = 1;
        // Call enable-related functions
        FUN_0095eb90(true);
        FUN_00967e30();
        // Reset some target ID at singleton+0x34
        *(int*)((int)DAT_0112b9b4 + 0x34) = -1;
    }
}