// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x006d2b50
// Constructor for the main game manager. Sets the vtable pointer at offset +0x58,
// resets the global initialization flag, calls base initialization, and optionally
// performs a memory management operation (likely deallocation) if the allocFlags
// bit 0 is set. The object size is 0x60.

int GodfatherGameManager::GodfatherGameManager(uint8_t allocFlags)
{
    // Set vtable pointer at offset +0x58
    this->vtablePtr = &PTR_LAB_00d5f2f0;

    // Reset global system initialized flag
    g_gameManagerInitialized = 0;

    // Call base class initializer
    this->baseInitialize();

    // If the alloc flag bit 0 is set, perform deallocation or registration
    if (allocFlags & 1)
    {
        // deallocObject likely frees the object from a custom pool
        deallocObject(this, 0x60);
    }

    return (int)this;
}