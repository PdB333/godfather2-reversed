// FUNC_NAME: Sentient::queryActionState
uint __thiscall Sentient::queryActionState(
    void *this,
    uint param2,
    uint param3,
    uint commandId,
    uint param5
)
{
    char flagCheck;
    uint result;
    int statePtr;
    uint bitFlags;
    uint someCount;
    int interPtr;
    bool condition;

    result = 0;
    switch (commandId) {
    case 0x12: // check if both pointers are non-zero
        if ((*(int *)((int)this + 0x70) != 0) && (*(int *)((int)this + 0x78) != 0)) {
            // both present -> action disallowed
            return 0;
        }
        return 1;

    case 0x13:
        statePtr = *(int *)((int)this + 0x5c); // +0x5c: pointer to state machine or component
        flagCheck = FUN_004abe10(0x20); // check a global flag (0x20)
        if ((flagCheck == 0) && ((*(byte *)(statePtr + 0x1b97) & 1) == 0)) {
            // if flag not set and bit 0 of byte at statePtr+0x1b97 is clear
            result = FUN_0054f220(0x2ee); // allow action based on resource check
            return result;
        }
        return 1;

    case 0x14:
        // Return a transformed version of a 32-bit value at +0x88
        bitFlags = *(uint *)((int)this + 0x88);
        return (bitFlags >> 4) & 0xFFFFFF01;

    case 0x15:
        // Check if object at +0xb8 exists and is not an invalid ID (0x50)
        interPtr = *(int *)((int)this + 0xb8);
        if ((interPtr != 0) && (interPtr != 0x50)) {
            if (interPtr == 0) {
                statePtr = 0;
            } else {
                statePtr = interPtr - 0x50; // offset by 0x50
            }
            if (*(int *)(statePtr + 0x74) == 3) {
                return 1; // condition met
            }
        }
        break;

    case 0x16:
        // Check count at +0xb4
        someCount = *(uint *)((int)this + 0xb4);
        if (1 < someCount) {
            return 1;
        }
        break;

    case 0x17:
        // Check global pointer at DAT_012233a0+4
        // DAT_012233a0 likely points to a singleton manager (e.g., GameManager)
        if (**(int **)(DAT_012233a0 + 4) != 0) {
            // compare with constant 0x1f30 (maybe a type ID)
            return (uint)(**(int **)(DAT_012233a0 + 4) == 0x1f30);
        }
        return 1;

    case 0x18:
        result = FUN_00760fa0(); // call another query function
        return result;

    default:
        // Defer to base class implementation
        result = FUN_0073e300(param2, param3, commandId, param5);
    }

    return result;
}