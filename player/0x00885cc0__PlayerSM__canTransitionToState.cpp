// FUNC_NAME: PlayerSM::canTransitionToState

byte __thiscall PlayerSM::canTransitionToState(int thisPtr, undefined param_2, undefined param_3, int stateId, undefined param_5)
{
    uint flags;
    char tempFlag;
    byte result = 0;

    switch (stateId - 0xB) {
    case 0: // stateId == 0xB (e.g., kStateIdle?)
        // If either state machine pointer is null or equals 0x48 (an invalid state),
        // or animation state pointer is null, force a transition by setting a flag and return 1.
        if ((*(int*)(thisPtr + 0x50) == 0) || (*(int*)(thisPtr + 0x50) == 0x48) ||
            (*(int*)(thisPtr + 0x58) == 0)) {
            *(uint*)(thisPtr + 0x70) |= 0x10;
            return 1;
        }
        break;

    case 1: // stateId == 0xC (e.g., kStateMoving?)
        flags = *(uint*)(thisPtr + 0x70);
        // Check if moving flags are cleared, then additional conditions from FUN_008859a0 and speed comparison.
        if ((((flags >> 8 & 1) == 0) && ((flags >> 9 & 1) == 0) &&
             (tempFlag = FUN_008859a0(), tempFlag != '\0') &&
             (*(float*)(thisPtr + 0x6c) <= *(float*)(thisPtr + 0x30))) ||
            // OR if moving flag is set and primary flag (bit 0) is set
            (((flags >> 9 & 1) != 0) && ((flags & 1) != 0))) {
            return 1;
        }
        break;

    case 2: // stateId == 0xD (e.g., kStateCombat?)
        if ((((*(uint*)(thisPtr + 0x70) >> 8 & 1) != 0) &&
             (*(uint*)(*(int*)(thisPtr + 0x58) + 0x820) >> 4 & 1) == 0) &&
            ((*(byte*)(thisPtr + 0x70) & 1) == 0)) {
            return 1;
        }
        break;

    case 3: // stateId == 0xE (e.g., kStateAiming?)
        flags = *(uint*)(thisPtr + 0x70);
        if ((((flags >> 8 & 1) != 0) && ((flags >> 9 & 1) == 0) &&
             (*(uint*)(*(int*)(thisPtr + 0x58) + 0x820) >> 4 & 1) != 0) &&
            DAT_00d5ddec <= *(float*)(thisPtr + 0x30)) {
            return 1;
        }
        // Additional condition: check bit 11 (0x800)
        if ((flags >> 0xB & 1) != 0) {
            return 1;
        }
        break;

    case 4: // stateId == 0xF (e.g., kStateStunned?)
        // Return inverted bit 10 of flags
        return ~(byte)(*(uint*)(thisPtr + 0x70) >> 10) & 1;

    default:
        // Fallback to generic state transition checker (likely shared with other state machines)
        result = FUN_004ac640(param_2, param_3, stateId, param_5);
    }

    return result;
}