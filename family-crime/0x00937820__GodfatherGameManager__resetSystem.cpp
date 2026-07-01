// FUNC_NAME: GodfatherGameManager::resetSystem

void __thiscall GodfatherGameManager::resetSystem()
{
    // Call to set some flag/state to 0 (maybe disable a feature)
    setSomeFlag(0);

    // Check global instance count or initialization state (DAT_01130020 + 0x78)
    // If not yet initialized (count < 1), perform first-time setup
    if (*(int *)(DAT_01130020 + 0x78) < 1) {
        initSystem(1, 1);   // First-time initialization with parameters (1,1)
        processEvents();    // Process pending events
    }

    // Reset member variable at offset +0x6C (likely m_bIsActive or m_initialized)
    *(undefined4 *)(this + 0x6C) = 0;
}