// FUNC_NAME: PlayerSM::handleStateStop
// Function at 0x0096c0f0 - Handles player state cleanup when transitioning out of a state (ground or wall cover)
// Uses offsets: +0xDC = currentState, +0x6F4 = flags, +0xC4 and +0xD4 = timers/counters
void __fastcall PlayerSM::handleStateStop(PlayerSM* this)
{
    int currentState = *(int*)((char*)this + 0xDC);
    uint flags = *(uint*)((char*)this + 0x6F4);
    bool bit1Clear = ((flags >> 1) & 1) == 0; // bit 1 flag indicates whether cleanup is needed

    if (currentState == 1) // ground state
    {
        if (bit1Clear)
        {
            *(int*)((char*)this + 0xC4) = 0; // clear ground-specific timer (e.g., sprint timer)
            *(int*)((char*)this + 0xD4) = 0; // clear another ground timer (e.g., stamina recovery)
            stopGroundState(); // calls FUN_0096a490
        }
    }
    else if (currentState == 6) // wall cover state
    {
        if (bit1Clear)
        {
            *(int*)((char*)this + 0xC4) = 0; // clear cover-specific timer (e.g., peek timer)
            *(int*)((char*)this + 0xD4) = 0; // clear another cover timer (e.g., blindfire timer)
            stopWallCoverState(); // calls FUN_00965f40
        }
    }
}