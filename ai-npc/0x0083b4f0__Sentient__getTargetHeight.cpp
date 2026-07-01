// FUNC_NAME: Sentient::getTargetHeight
float __fastcall Sentient::getTargetHeight(void* thisPtr)
{
    float height = *(float*)((int)thisPtr + 0x70); // +0x70: currentHeight or baseHeight

    // Check if entity is alive/has state flags (0x18000 = AI_STATE_ALIVE | AI_STATE_VISIBLE)
    if (((*(uint*)((int)thisPtr + 0xa8) & 0x18000) != 0) &&
        (height < *(float*)((int)thisPtr + 0x74)) && // +0x74: targetHeight or maxHeight
        ((*(uint*)((int)thisPtr + 0xa8) >> 0x10 & 1) != 0)) // Check "inCover" or "isProne" flag (bit 16)
    {
        // If entity is in a lowered position, use their actual height (standing -> crouching adjustment)
        height = *(float*)((int)thisPtr + 0x74); // Return the target/standing height instead
    }

    return (float10)height; // Cast to 10-byte float for x87
}