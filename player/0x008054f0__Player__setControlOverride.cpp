// FUNC_NAME: Player::setControlOverride
// Function address: 0x008054f0
// Sets an override control value and propagates it to a target object, with optional debug output.
void __thiscall Player::setControlOverride(int overrideValue, bool triggerEvent)
{
    // Store override control index at +0x1010
    *(int *)(this + 0x1010) = overrideValue;

    // Get target object from +0xffc (likely a vehicle or character)
    int targetObj = *(int *)(this + 0xffc);
    if (targetObj != 0 && targetObj != 0x48) // 0x48 might be a null sentinel
    {
        // Set control input on the target at +0xfc8
        *(int *)(targetObj + 0xfc8) = overrideValue;

        if (triggerEvent)
        {
            // Compute adjusted target pointer (offset -0xc for some reason)
            int adjusted = (targetObj == 0 || targetObj == 0x48) ? 0 : (targetObj - 0xc);
            // Debug print or event dispatch
            DebugPrintf(&g_debugPrefix, adjusted, 0);
        }

        // Check another flag at +0x1028 (char) and a second object at +0xff0
        if (*(char *)(this + 0x1028) != 0)
        {
            int anotherObj = *(int *)(this + 0xff0);
            if (anotherObj != 0 && anotherObj != 0x48)
            {
                // Validate via global check function
                if (IsPlayerValid())
                {
                    // Send a control event (hash 0x764f8bec)
                    SendControlEvent(this, 0x764f8bec);

                    // Local debug string construction
                    char buffer[8];
                    char *formatStr = (char *)g_formatString; // DAT_0112ad7c
                    StringFormat(&formatStr, 0); // Write formatted data to buffer
                    if (*(int *)buffer != 0) {
                        OutputDebugString((int *)buffer);
                    }
                }
            }
        }
    }
}