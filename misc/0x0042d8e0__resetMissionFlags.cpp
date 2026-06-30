// FUNC_NAME: resetMissionFlags
// Function at 0x0042d8e0: Clears various mission-related flags in a large state struct.
// Likely part of game state management (e.g., MissionManager or GameStateController).
// Uses a global ushort at 0x012053dc to determine which of two possible flag bytes to clear.

void __thiscall resetMissionFlags(void* this)
{
    uint flagMask;
    uint conditionResult;
    int flagOffsetBase;

    // Clear multiple flag bytes in the state structure.
    // Offsets: +0x18E9, +0x1F89, +0x2629, +0x3369 (each 1 byte)
    someResetFunction(); // FUN_004c5170 – possibly a general state reset or timer
    *(uint8_t*)((int)this + 0x18E9) = 0;
    someResetFunction();
    *(uint8_t*)((int)this + 0x1F89) = 0;
    someResetFunction();
    *(uint8_t*)((int)this + 0x2629) = 0;
    someResetFunction();
    *(uint8_t*)((int)this + 0x3369) = 0;

    // Get a flag/value from another function
    flagMask = getSomeFlag(); // FUN_0042e5e0 – returns some uint
    // Global data: two-byte value at 0x012053DC (likely a bitmask or flag)
    conditionResult = (uint)(ushort)g_SomeUshort; // DAT_012053dc

    // Determine which flag byte to clear based on condition:
    // If ((flagMask >> 8) & conditionResult) is nonzero, then use offset +0x2CC9
    // else use offset +0x1249.
    someResetFunction();
    *(uint8_t*)((- (uint)(((flagMask >> 8) & conditionResult) != 0) & 4) * 0x6A0 + (int)this + 0x1249) = 0;

    // Clear three more flags (likely in a different subsystem)
    clearAnotherFlag(); // FUN_0042d8a0 (called three times)
    clearAnotherFlag();
    clearAnotherFlag();
    return;
}