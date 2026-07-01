// FUNC_NAME: PlayerCoverSM::getCoverState
// Function address: 0x008a6010
// Description: Returns the current cover state/action. If the base state is 2 (COVERED),
// checks directional flags at +0x1c: bit1 -> 0x1e (30, cover left), bit0 -> 0x1f (31, cover right).
// Otherwise returns the base state value at +4.

int PlayerCoverSM::getCoverState(void)
{
    int baseState = *(int *)(this + 0x4);  // +0x4: current cover state (e.g., 0=none,1=peeking,2=covered)
    if (baseState == 2) {
        byte flags = *(byte *)(this + 0x1c); // +0x1c: cover direction flags (bit0=right, bit1=left)
        if ((flags >> 1) & 1) {
            return 0x1e; // 30 = cover left
        }
        if (flags & 1) {
            return 0x1f; // 31 = cover right
        }
        // Default: fall through to resolve via another function
        baseState = FUN_008a5d20(this); // Possibly get the default cover state
    }
    return baseState;
}