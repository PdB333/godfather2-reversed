// FUNC_NAME: FlagSystem::setFlag
void FlagSystem::setFlag(uint flagMask)
{
    // Ensure the global flag system is initialized (calls internal setup)
    initializeFlagSystem(); // 0x004abd90

    // Resolve the game object associated with the given flag mask
    GameObject* obj = getObjectForFlag(flagMask); // 0x004abd50

    if (obj)
    {
        // Set the flag bit in the object's flags field at offset +0x38
        obj->flags |= flagMask; // +0x38
    }
}