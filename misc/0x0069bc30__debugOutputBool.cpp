// FUNC_NAME: debugOutputBool
// Function at 0x0069bc30: Outputs a boolean value for debug logging, with caching and scoped output.
bool debugOutputBool(EntityID entityId, bool value)
{
    char cachedValue;
    // Try to get a cached boolean value for this entity (e.g., from a property or previous log)
    if (FUN_006998f0(entityId, &cachedValue) != 0) {
        return cachedValue;
    }

    // Check if debug array index is valid: g_debugArrayIndex >= 0 and within range
    // DAT_00e506ac is the current index, DAT_01129f8c and DAT_01129f90 are bounds
    if ((g_debugArrayIndex >= 0) && (g_debugArrayIndex < (g_debugArrayEnd - g_debugArrayStart) / 4)) {
        // Push debug context for this entity (e.g., indent or scope)
        FUN_004d3bc0(entityId);

        // Choose string representation
        const char* str = value ? "true" : "false";

        // Create a scoped debug output object (likely RAII with destructor)
        int local_10[3];  // 12-byte structure (possibly DebugOutputStack)
        code *destructorFunc;  // Function pointer (uninitialized? likely part of the struct)
        // Initialize the scoped object (sets up destructor, etc.)
        FUN_0069b380(local_10);

        // Output the string (immediate print)
        FUN_004d3d90(str);

        // Call destructor if the internal state indicates it's needed
        // local_10[0] is likely a magic number or pointer to self
        // destructorFunc should have been set by FUN_0069b380, but decompiler shows it as separate variable
        // This is likely a vtable destructor call for the scoped object.
        if (local_10[0] != 0) {
            (*destructorFunc)(local_10[0]);  // call destructor
        }
    }

    // Return the original value (or cached if available)
    return value;
}