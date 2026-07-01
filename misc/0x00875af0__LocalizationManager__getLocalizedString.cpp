// FUNC_NAME: LocalizationManager::getLocalizedString
undefined4 __thiscall LocalizationManager::getLocalizedString(int this, undefined4 param_2, undefined4 key)
{
    char validFlag;
    undefined4 resultPtr;
    undefined1 *bufferPtr;
    
    // Check if the localization buffer size is non-zero (indicating system is initialized)
    if (*(int *)(this + 0xa40) == 0) {
        // Not initialized, return the key itself as fallback
        return key;
    }
    
    // Get the working buffer; if null, use a global default string pointer
    bufferPtr = *(undefined1 **)(this + 0xa3c);
    if (bufferPtr == (undefined1 *)0x0) {
        bufferPtr = (undefined1 *)&DAT_0120546e; // Default "empty" string
    }
    
    // Copy localized string for the given key into the buffer, with buffer size limit
    resultPtr = FUN_004db3f0(key, bufferPtr, *(int *)(this + 0xa40));
    
    // Check if the result string is valid (non-empty)
    validFlag = FUN_0045f1b0(resultPtr);
    if (validFlag == '\0') {
        // Invalid result, fall back to the original key
        return key;
    }
    
    // Return pointer to the localized string
    return resultPtr;
}