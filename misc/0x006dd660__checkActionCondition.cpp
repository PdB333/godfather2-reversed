// FUNC_NAME: checkActionCondition
// Description: Checks if an action can be performed. Returns 1.0f if conditions are met, else 0.0f.
// This function is part of an unknown game object (likely from the EARS engine hierarchy).
// It checks a virtual property (hash 0x383225a1) on the object, then validates a target object and flags.

float checkActionCondition(int* thisObj, int* targetObj, uint flags)
{
    int result = 0;

    // Call a virtual function at offset 0x10 to check a property (likely a capability or permission)
    // The hash 0x383225a1 may be a CRC32 of a property name like "canPerformAction" or similar.
    char canPerform = (*(char (__thiscall**)(int*))(*thisObj + 0x10))(0x383225a1);

    if (canPerform &&
        targetObj != nullptr &&
        targetObj != (int*)0x48 &&            // Exclude a specific invalid pointer (0x48)
        *reinterpret_cast<char*>(targetObj + 0x160 / 4) == 0x01 &&  // Check a bool flag at offset 0x160 (e.g., "isAlive" or "isActive")
        ((flags >> 10) & 1) != 0)             // Check bit 10 of flags (e.g., "allowOverride" or "mustBeVisible")
    {
        result = 1;
    }

    return static_cast<float>(result);
}