// FUNC_NAME: setParameterValue
// Address: 0x005e2d30
// Role: Sets a parameter value (e.g., cheat/feature state) on a manager object if a global flag is enabled.
// The first parameter (arg1) appears unused; likely a relic of calling convention or a placeholder.

extern void* DAT_0122350c; // Global data base pointer, maybe a game manager singleton or large state block.

// Forward declaration of the instance getter (FUN_005e2150)
void* getManagerInstance(void);

int setParameterValue(void* arg1, int value) {
    // Check a global flag at offset 0x1744 from the base pointer.
    // If the flag is non-zero, the feature/system is active.
    char* basePtr = (char*)DAT_0122350c;
    if (basePtr[0x1744] != 0) {
        void* manager = getManagerInstance();
        if (manager != 0) {
            // Store 'value' at offset 0x24C of the manager object.
            // This likely sets a member like m_parameter or m_state.
            *(int*)((char*)manager + 0x24C) = value;
            return 1; // Success
        }
    }
    return 0; // Failure
}