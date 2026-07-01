// FUNC_NAME: FUN_007f98e0
// This function appears to convert an internal state/enum value from a virtual function call to a different enum representation.
// It reads a value via a virtual method at offset 0x270 of the vtable of *param_1,
// then maps it to a different enum value (likely a generic gameplay enum).
// Called from 0x00806590 (likely a state machine or controller update).
__fastcall char FUN_007f98e0(int* thisPtr)
{
    // Call virtual method at vtable offset 0x270 (0x270 / 4 = 0x9Cth virtual function, counting from 0)
    // This returns a value in range [0..4]
    int internalValue = (*(int (__thiscall**)(int*))(thisPtr[0] + 0x270))(thisPtr);
    
    // Map internal value to output enumeration:
    switch (internalValue)
    {
        case 0: return 0; // None/Idle
        case 1: return 3; // Some state 3
        case 2: return 4; // Some state 4
        case 3: return 1; // Some state 1
        case 4: return 2; // Some state 2
        default:
            return internalValue; // fallback (should not happen)
    }
}