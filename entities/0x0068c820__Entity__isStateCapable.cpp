// FUNC_NAME: Entity::isStateCapable

bool __fastcall Entity::isStateCapable(int thisPtr)
{
    // Current state ID (e.g., from an enum of states)
    byte state = *(byte *)(thisPtr + 0x14);

    bool result = true;

    // State 0x13: requires a valid pointer (e.g., vehicle, weapon) at +0x2c
    if (state == 0x13) {
        if (*(int *)(thisPtr + 0x2c) == 0) {
            return false;
        }
    }
    // State 0x12: always capable (e.g., "dead" or "none")
    else if (state != 0x12) {
        // For other states, check a bitmask at +0x2c; bit index is state & 0x1f
        result = (*(uint *)(thisPtr + 0x2c) & (1 << (state & 0x1f))) != 0;
    }

    return result;
}