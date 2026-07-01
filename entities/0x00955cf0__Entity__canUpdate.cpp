// FUNC_NAME: Entity::canUpdate
bool __thiscall Entity::canUpdate(void* thisPtr)
{
    float value = *(float*)((char*)thisPtr + 8);   // +0x8: e.g., m_speed or m_stateFloat
    uint32 flags = *(uint32*)((char*)thisPtr + 0xC); // +0xC: bitfield flags (bit1 may be "disabled" or "dead")
    // Compare against a global float constant (likely 0.0f or a sentinel)
    extern float DAT_00d577a0; // from .data section
    // Check if not in a special state and a global system check passes
    if (value == DAT_00d577a0 && ((flags >> 1) & 1) == 0) // bit 1 clear means not disabled/dead?
    {
        if (FUN_00410eb0()) // likely global pause or lock check (e.g., IsGamePaused)
            return false;
    }
    return true;
}