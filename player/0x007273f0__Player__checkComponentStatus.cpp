// FUNC_NAME: Player::checkComponentStatus
// Address: 0x007273f0
// This function checks if a component handle (at +0x2134) resolves to an object, then compares a field at +0x14 of a nested structure with a local value derived from +0x1ed8.
// Returns a 32-bit value; low byte = 1 on match, else 0 (high bits come from the resolved object pointer).

extern uint __cdecl getGameState(void);          // e.g., returns 3 for "in-mission"
extern uint __cdecl resolveHandle(uint handle); // e.g., entity handle -> ptr

uint __thiscall Player::checkComponentStatus(void)
{
    uint state = getGameState();
    if (state != 3)
        return state & 0xFFFFFF00; // state==3 -> returns 0

    uint handle = *(uint *)(this + 0x2134);   // +0x2134: handle to a component (e.g., crew leader)
    if (handle == 0)
        return 0;

    uint obj = resolveHandle(handle);
    if (obj == 0)
        return 0;

    uint target = *(uint *)(*(int *)(obj + 0x180) + 0xfc); // +0x180 likely a pointer to a sub-object, +0xfc is a field
    if (target == 0)
        return 0;

    int *compareField = (int *)(target + 0x14); // +0x14: field to compare with local value
    int localVal;
    if (*(int *)(this + 0x1ed8) == 0)            // +0x1ed8: possibly a pointer to a different object
        localVal = 0;
    else
        localVal = *(int *)(this + 0x1ed8) - 0x48; // subtract offset to get base pointer?

    // Build result: low byte = 1, upper 24 bits from localVal >> 8
    uint result = (((uint)((int)(localVal >> 8))) & 0xFFFFFF00) | 1;
    if (*compareField == localVal)
        return result;   // match -> low byte = 1
    else
        return target & 0xFFFFFF00; // no match -> low byte = 0
}