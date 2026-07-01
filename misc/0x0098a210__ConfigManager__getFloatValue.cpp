// FUNC_NAME: ConfigManager::getFloatValue
// Function address: 0x0098a210
// Retrieves a float value from a data table lookup given a string key and sub-key.
// Uses a delegate for string deallocation.

typedef void (__cdecl *StringDeleter)(char*);

float __thiscall ConfigManager::getFloatValue(int thisPtr, int subKey, const char* keyString)
{
    char* retrievedString = nullptr;
    StringDeleter deleter = nullptr; // local_4; will be set by Internal_GetString

    // Call to internal string retrieval function, likely copies or allocates a string
    // and sets the deleter function pointer
    Internal_GetString(keyString, &retrievedString, &deleter);

    char* effectiveString = retrievedString;
    if (effectiveString == nullptr) {
        effectiveString = (char*)0x0120546e; // Default string constant
    }

    // Call the actual lookup function: uses the string, a member at offset 0x38 (presumably a table pointer),
    // and the subKey parameter to compute a float value
    float10 rawValue = Internal_LookupFloat(effectiveString, *(int*)(thisPtr + 0x38), subKey);

    float10 scaledValue = rawValue * (float10)DAT_0120588c; // Apply multiplier

    if (retrievedString != nullptr) {
        // Call the deleter to free the allocated string
        deleter(retrievedString);
        // Convert scaled value to single precision float (truncation)
        float result = (float)scaledValue;
        return result;
    }

    // No string allocated, return the scaled extended precision value directly
    // (the function returns float, so conversion happens anyway)
    return (float)scaledValue;
}