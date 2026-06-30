// FUNC_NAME: setGlobalValue
// Address: 0x004e9cc0
// Reconstructed C++: simple setter for a global variable (DAT_012054f8).
// Returns the previous value of the global.
int setGlobalValue(int newValue) {
    int oldValue = DAT_012054f8; // Global at 0x012054f8 (likely engine state)
    DAT_012054f8 = newValue;
    return oldValue;
}