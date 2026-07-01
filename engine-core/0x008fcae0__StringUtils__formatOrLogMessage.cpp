// FUNC_NAME: StringUtils::formatOrLogMessage
void FUN_008fcae0(undefined4 param_1, undefined4 param_2, undefined4 param_3)
{
    char* strPtr = nullptr;
    int local_c = 0;
    int local_8 = 0;
    void (*deleter)(char*) = nullptr;

    // Call a function that likely allocates or retrieves a string from param_2
    FUN_00603330(param_2, &strPtr);

    char* sourceStr = strPtr;
    if (strPtr == nullptr) {
        // Fallback to a default string constant (likely an empty string or placeholder)
        sourceStr = &DAT_0120546e;
    }

    // Call a function that processes the string with param_3 (likely formatting or logging)
    FUN_00981e70(sourceStr, param_3, 0);

    // Clean up the allocated string if it was dynamically allocated
    if (strPtr != nullptr) {
        (*deleter)(strPtr);
    }

    return;
}