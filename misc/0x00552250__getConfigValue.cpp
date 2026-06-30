// FUNC_NAME: getConfigValue
// Function at 0x00552250: Retrieves a configuration value using message code 0x2006.
// The `internalGetConfigValue` function is assumed to set result[0] based on the code.
// The redundant check if (result[0] == 0) result[0] = 0; is preserved from decompilation.
int getConfigValue() {
    int result[2];
    internalGetConfigValue(result, 0x2006); // Set result based on code 0x2006
    if (result[0] == 0) {
        result[0] = 0; // No-op, likely leftover from optimization
    }
    return result[0];
}