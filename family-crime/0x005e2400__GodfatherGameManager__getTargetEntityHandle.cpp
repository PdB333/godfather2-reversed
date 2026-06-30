// FUNC_NAME: GodfatherGameManager::getTargetEntityHandle
// Function address: 0x005e2400
// Retrieves a target entity handle from the current player or active entity.
uint32_t __thiscall GodfatherGameManager::getTargetEntityHandle(uint32_t* outHandle)
{
    // Check if the game manager has an active target (bool at +0x1744)
    if (*(uint8_t*)(this + 0x1744) != 0)
    {
        // Get the player/entity controller (returns pointer to some component)
        void* controller = getActiveController(); // callee: FUN_005e2150, likely a thiscall member
        if (controller != nullptr)
        {
            // Read the target handle from the controller at offset +0x250 (e.g., m_targetHandle)
            uint32_t handle = *(uint32_t*)((uint8_t*)controller + 0x250);
            *outHandle = handle;
            // Return success: low byte set to 1, high 24 bits come from handle
            return (handle & 0xFFFFFF00) | 1;
        }
    }
    // Failed: return the original this pointer with low byte cleared (signals failure)
    return (uint32_t)this & 0xFFFFFF00;
}