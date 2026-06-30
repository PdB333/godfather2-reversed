// FUNC_NAME: setGlobalStateFlag (0x0060b610)
// Simple setter for a global state byte flag. Called from initialization or configuration routines.
void setGlobalStateFlag(byte value) {
    // Address 0x00f15a3a - likely a global toggle or mode flag.
    DAT_00f15a3a = value;
}