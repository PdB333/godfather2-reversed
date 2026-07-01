// FUNC_NAME: isActionAllowed
// Function address: 0x00977390
// Checks if an action is allowed based on a resource/cooldown structure.
// The global pointer g_pResourceManager points to a structure with fields:
// +0x54: bool active (byte)
// +0x58: int mode (0 = normal, non-zero = alternate behavior)
// +0x5c: float currentValue
// +0x70: float maxValue

bool isActionAllowed()
{
    // Global pointer to a resource manager or cooldown object
    // (likely a singleton or specific game object)
    uint8_t* pResource = (uint8_t*)DAT_01223394;

    // Check if the resource is active
    if (*(char*)(pResource + 0x54) != '\0')
    {
        float current = *(float*)(pResource + 0x5c);
        float max = *(float*)(pResource + 0x70);
        int mode = *(int*)(pResource + 0x58);

        if (current <= max)
        {
            // If resource is not depleted and mode is normal, allow action
            if (mode == 0)
                return true;
        }
        else
        {
            // Resource is over max (e.g., overflow or special state)
            float ratio = max / current;
            if (mode != 0)
            {
                // In alternate mode, invert the ratio
                ratio = 1.0f - ratio; // _DAT_00d5780c is likely 1.0f
            }
            // Allow action only if ratio >= 1.0 (i.e., max >= current or max <= 0)
            if (1.0f <= ratio)
                return true;
        }
    }
    return false;
}