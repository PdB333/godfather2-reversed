// FUNC_NAME: getGlobalFloatConstant
// Address: 0x0054c3f0
// Returns a global float constant from data address 0x00e2cd54.
// Likely a singleton or timing constant used by the EARS engine.
float getGlobalFloatConstant() {
    // Read 32-bit float from global data location
    return *(float*)0x00e2cd54;
}