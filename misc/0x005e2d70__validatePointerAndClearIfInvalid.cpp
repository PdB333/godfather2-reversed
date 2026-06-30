// FUNC_NAME: validatePointerAndClearIfInvalid
bool validatePointerAndClearIfInvalid(void** ptr) {
    // Call helper to check if the pointer is valid (e.g., non-null and points to a valid object)
    char isValid = isPointerValid(ptr); // FUN_005e2490
    if (isValid == '\0') {
        // Pointer is invalid; clear it to null
        *ptr = 0;
        return false;
    }
    return true;
}