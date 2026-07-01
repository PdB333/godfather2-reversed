// FUNC_NAME: Entity::checkBehaviorStateFlags
uint __fastcall Entity::checkBehaviorStateFlags(Entity *thisPtr)
{
    // Offset +0x64: pointer to behavior state object (may be 0 or sentinel 0x48)
    uint behaviorStatePtr = *(uint *)((uint)thisPtr + 0x64);

    // First path: valid pointer (not 0, not sentinel 0x48)
    if ((behaviorStatePtr != 0) && (behaviorStatePtr != 0x48))
    {
        // Subtract 0x48 to get to base of state structure
        uint stateBase = behaviorStatePtr - 0x48;
        // Read flags at +0x11c (284 bytes into structure)
        uint flags = *(uint *)(stateBase + 0x11c);
        // Check bit 0 of flags >> 2 (i.e., bit 2 of flags)
        if ((flags & 4) != 0)
        {
            // Return flags>>2 with low byte cleared (high byte preserved)
            return (flags >> 2) & 0xFFFFFF00;
        }
    }

    // Second path: fallback check
    uint value = behaviorStatePtr;
    if ((value != 0) && ((value = value - 0x48) != 0))
    {
        // Same state base calculation
        uint stateBase2 = behaviorStatePtr - 0x48;
        // Check if any of bits 0,4,5,6 (0x71 = 01110001) are set in flags
        bool hasFlag = (*(uint *)(stateBase2 + 0x11c) & 0x71) != 0;
        // Construct return value: stateBase2 >> 8 as high 3 bytes + hasFlag as LSB
        uint result = ((stateBase2 >> 8) & 0xFFFFFF00) | (hasFlag ? 1 : 0);
        if (hasFlag)
        {
            return result & 0xFFFFFF00;
        }
    }

    // Default: return (original behaviorStatePtr >> 8) with LSB set to 1
    return ((behaviorStatePtr >> 8) & 0xFFFFFF00) | 1;
}