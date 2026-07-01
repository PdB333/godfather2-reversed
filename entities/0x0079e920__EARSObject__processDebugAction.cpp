// FUNC_NAME: EARSObject::processDebugAction
uint __thiscall EARSObject::processDebugAction(int arg)
{
    // Read flags field at +0x249c, shift right 1 to check bit 1 (original bit at position 1)
    uint flags = *(uint *)(this + 0x249c) >> 1;
    if ((flags & 1) != 0)
    {
        // Global check: is debug allowed? (FUN_00481620 returns char, treated as bool)
        bool allowed = (FUN_00481620() != 0);
        if (allowed)
        {
            // Read debug action byte from +0x2498
            byte debugAction = *(byte *)(this + 0x2498);
            // Execute the debug action with the provided argument
            uint result = FUN_004657d0(debugAction, arg);
            return result;
        }
    }
    // Return the shifted flags with the lower byte cleared
    return flags & 0xffffff00;
}