// FUNC_NAME: UIResourceText::setTextFromResource
void __thiscall UIResourceText::setTextFromResource(int thisPtr, int destString, int maxLength) {
    char* resourceString = nullptr;
    int stringLength = 0; // local_c
    void (*deallocFunc)(char*); // local_4 - likely a free function, but uninitialized here

    // Retrieve localized string from resource ID stored at offset +0x24
    // FUN_00603da0 parameters: (resourceID, 2, &outputPointer, 1) 
    // 2 and 1 are likely flags for the retrieval
    getResourceString(*(int*)(thisPtr + 0x24), 2, &resourceString, 1);

    char* stringToUse = resourceString;
    if (resourceString == nullptr) {
        // Use a default empty string if resource not found
        stringToUse = &DEFAULT_STRING; // DAT_0120546e - likely " " or ""
    }

    // Copy the string to the destination (e.g., UI text field)
    // FUN_005c4660 parameters: (destString, sourceString, maxLength, stringLength)
    setUIText(destString, stringToUse, maxLength, stringLength);

    if (resourceString != nullptr) {
        // Free the allocated resource string using a deallocator function pointer.
        // Note: In the decompilation, deallocFunc is uninitialized (0x0), which would cause a crash.
        // This suggests either a decompilation error or the actual code uses a global function.
        // For reconstruction, we assume a global deallocator is used.
        deallocFunc(resourceString);
    }
}