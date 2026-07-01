// FUNC_NAME: getComponentIfValid
// Function at 0x008c6d50: Guards a component retrieval by checking if a global/static condition is met.
// param_1 is a pointer to an entity or component (likely this pointer for a __thiscall, but treated as generic pointer).
// Returns the result of FUN_008c1250 if the check passes, otherwise 0.

int getComponentIfValid(void* param_1) // param_1 is likely a pointer to an object (e.g., a component/entity)
{
    // Check if the pointer is non-null
    if (param_1 != 0) {
        // Check some global state (e.g., system initialized, game mode active)
        int isValid = FUN_00791540(); // Returns non-zero if condition is met
        if (isValid != 0) {
            // Retrieve the component or data associated with param_1
            int result = FUN_008c1250(param_1); // Likely returns component pointer or handle
            return result;
        }
    }
    return 0; // Return null/zero if invalid
}