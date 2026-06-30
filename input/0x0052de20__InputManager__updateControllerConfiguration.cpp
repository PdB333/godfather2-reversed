// FUNC_NAME: InputManager::updateControllerConfiguration
int __cdecl UpdateControllerConfiguration(int countParam, int flag1, int flag2, int flag3, int flag4, int flag5, int flag6)
{
    int eaxValue; // from implicit EAX register
    uint newFlags = 0;

    // If EAX (count parameter) > 0, build a count field shifted by 8 bits
    if (0 < eaxValue) {
        // Check a global boolean flag (likely indicates whether controller count is active)
        if (DAT_0120551e == '\0') {
            eaxValue = 1;
        }
        newFlags = eaxValue << 8;
    }

    // Combine boolean flags into bits 0-7
    if (flag1 != 0) {
        newFlags |= 4;      // bit 2
    }
    if (flag2 != 0) {
        newFlags |= 0xc;    // bits 2,3
    }
    if (flag3 != 0) {
        newFlags |= 0x10;   // bit 4
    }
    if (flag4 != 0) {
        newFlags |= 1;      // bit 0
    }
    if (flag5 != 0) {
        newFlags |= 0x20;   // bit 5
    }
    if (flag6 != 0) {
        newFlags |= 2;      // bit 1
    }

    // If flags changed, trigger an update via a global function
    if (newFlags != DAT_01205538) {
        // This call likely updates the global state and returns a result
        return FUN_0053dff0();
    }

    // Return the stored result from last successful configuration
    return DAT_01205540;
}