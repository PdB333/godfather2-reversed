// FUNC_NAME: CInputState::clearFlags
// Address: 0x004abce0
// Clears specified flag bits in the object's flag field, then conditionally triggers an update if a subordinate object is in an inactive state.

void __thiscall CInputState::clearFlags(uint flagsMask)
{
    // Clear the bits specified by flagsMask in the flag field at offset +0x3C
    *(uint *)(this + 0x3C) &= ~flagsMask;

    // If there's a subordinate object pointer at +0x1C and its active flag (byte at +0x44) is zero (false),
    // then call the processing function (likely to evaluate state changes)
    if (*(int *)(this + 0x1C) != 0 && *(char *)(*(int *)(this + 0x1C) + 0x44) == '\0')
    {
        FUN_004abd20(); // processStateChange or onFlagsCleared
    }
    return;
}