// FUNC_NAME: someClass::isSomethingEnabled
// Function at 0x006aba10 - checks if a flag/pointer is non-zero and returns result from another function
// Likely a getter or validation check for some game system (e.g., debug mode, cheat, or feature toggle)
// param_1 appears to be a pointer (likely 'this' or a flag value)
// Returns 0 if param_1 is null, otherwise delegates to FUN_006ab960

char someClass::isSomethingEnabled(void* param_1) // param_1 is likely 'this' or a flag pointer
{
    if (param_1 != 0) {
        return FUN_006ab960(); // Returns some boolean/char value from another function
    }
    return 0; // Return false/null if pointer is null
}