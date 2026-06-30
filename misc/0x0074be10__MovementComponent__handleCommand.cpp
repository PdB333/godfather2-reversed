// FUNC_NAME: MovementComponent::handleCommand

extern float g_speedScale;          // DAT_00e448e8
extern float g_timeMultiplier;      // DAT_00d5c458

int __thiscall MovementComponent::handleCommand(int *thisPtr, int param2, int param3, int param4, int commandId, int param6)
{
    // Offset legend (relative to thisPtr):
    // +0x74 (0x1d) : position.x
    // +0x78 (0x1e) : position.y
    // +0x7C (0x1f) : position.z
    // +0x80 (0x20) : velocity.x (or scale)
    // +0x84 (0x21) : velocity.y
    // +0x88 (0x22) : velocity.z
    // +0x90 (0x24) : double (two floats packed, e.g. direction.x & y)
    // +0x98 (0x26) : int (unknown)
    // +0x9C (0x27) : double (two floats packed, e.g. direction.z & w)
    // +0xA0 (0x28) : int (override for y component)
    // +0xA4 (0x29) : int (unknown)
    // +0xA8 (0x2a) : output.x
    // +0xAC (0x2b) : output.y
    // +0xB0 (0x2c) : output.z
    // +0xB4 (0x2d) : function pointer (called when +0xC8 is null)
    // +0xC8 (0x32) : function pointer (called with this+0x2d as argument)
    // vtable[0x0b] (0x2c) : callback (result, 1, 1, 0, 1.0f, 1.0f)

    switch (commandId)
    {
    case 0x12: // Update movement
    {
        // Extract two packed float pairs from doubles at +0x24 and +0x27
        unsigned long long raw24 = *(unsigned long long *)(thisPtr + 0x24);
        unsigned long long raw27 = *(unsigned long long *)(thisPtr + 0x27);

        float low24 = *(float *)&raw24;
        float high24 = *(float *)((char *)&raw24 + 4);
        float low27 = *(float *)&raw27;
        float high27 = *(float *)((char *)&raw27 + 4);

        // Add global time multiplier to the high parts
        high24 += g_timeMultiplier;
        high27 += g_timeMultiplier;

        // Recombine into two doubles and process (likely normalization or cross product)
        unsigned long long new24 = *(unsigned long long *)&low24 | (unsigned long long)*(unsigned int *)&high24 << 32;
        unsigned long long new27 = *(unsigned long long *)&low27 | (unsigned long long)*(unsigned int *)&high27 << 32;

        FUN_0074b920(&new24, &new27);

        // Apply speed scaling and offset to output
        thisPtr[0x2a] = (int)((float)thisPtr[0x20] * g_speedScale + (float)thisPtr[0x1d]); // output.x
        thisPtr[0x2b] = (int)((float)thisPtr[0x21] * g_speedScale + (float)thisPtr[0x1e]); // output.y
        thisPtr[0x2c] = (int)((float)thisPtr[0x22] * g_speedScale + (float)thisPtr[0x1f]); // output.z
        thisPtr[0x2b] = thisPtr[0x28]; // Override output.y with stored value

        return 1;
    }
    case 0x13: // No specific action, falls through to default processing
        break;

    case 0x14: // Allocate something (size 0x20)
        FUN_004abdd0(0x20);
        return 1;

    case 0x15: // Enable feature
        FUN_00751e70();
        return 1;

    case 0x16: // Disable feature
        FUN_00751ec0();
        return 1;

    default:
        return FUN_0080e8e0(param2, param3, param4, commandId, param6);
    }

    // Common path for command 0x13 (and any other that falls through)
    int result;
    if ((void *)thisPtr[0x32] == NULL)
    {
        // No custom callback, use direct function at +0x2d
        result = ((int (*)())thisPtr[0x2d])();
    }
    else
    {
        // Custom callback expects this = thisPtr + 0x2d
        result = ((int (*)(int *))thisPtr[0x32])(thisPtr + 0x2d);
    }

    // Invoke virtual method from vtable at offset 0x2c
    void **vtable = *(void ***)thisPtr;
    ((void (*)(int, int, int, int, float, float))vtable[0x2c / 4])(result, 1, 1, 0, 1.0f, 1.0f);

    return 1;
}