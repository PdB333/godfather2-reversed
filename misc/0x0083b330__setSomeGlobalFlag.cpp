// FUNC_NAME: setSomeGlobalFlag
// This function sets a global byte at 0x00e53f38 and returns the previous value.
// It appears to be a simple setter/getter for a global flag or state variable.
// The function takes a single byte parameter and returns the old value.
// This pattern is common for atomic flag operations or state transitions.
// The global at 0x00e53f38 is likely a boolean or small enum used by the game engine.

uint8_t setSomeGlobalFlag(uint8_t newValue)
{
    uint8_t oldValue = DAT_00e53f38;  // Global byte at 0x00e53f38
    DAT_00e53f38 = newValue;
    return oldValue;
}