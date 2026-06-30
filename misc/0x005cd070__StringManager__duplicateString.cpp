// FUNC_NAME: StringManager::duplicateString
// Address: 0x005cd070
// Role: Duplicates a string using a custom allocator with callback for deallocation
// Purpose: Part of the game's string management system (EA EARS engine)

char* StringManager::duplicateString(void* thisPtr, int flags, const char* sourceString)
{
    char cCurrent;
    char* newString;
    char* sourcePtr;
    char* destPtr;
    int allocSize;
    char* stringToCopy;    // local_20: either sourceString or default fallback
    int deallocCallback;   // local_14: pointer to deallocation function (set by allocator)
    int unused;

    // Acquire read lock on string pool
    lockStringPool(sourceString);
    // Ensure string manager is initialized
    assertManagerInitialized();
    // Increment global pool reference counter (likely for locking)
    incrementPoolRefcount(&gStringPoolMutex);

    allocSize = 2;                              // Size parameter (could be flags or minimal allocation)
    stringToCopy = (char*)0x4;                  // This likely is a global string literal, e.g., "4" or a placeholder
    unused = 0;

    // Allocate memory via a function pointer from global vtable (DAT_012234ec + 4)
    // The allocator returns a new buffer and also sets a deallocation callback via &deallocCallback
    newString = (char*)((* (code (__stdcall *)(int*, int*)) *(int*)(DAT_012234ec + 0x4) ))(&deallocCallback, &allocSize);

    // Determine the source string to copy: use provided source if non-null, otherwise fallback to default
    sourcePtr = stringToCopy;
    destPtr = newString;
    if (stringToCopy == (char*)0x0) {
        sourcePtr = (char*)DAT_0120546e;       // Default string constant (e.g., "unknown")
    }

    // Copy the source string into the new buffer (null-terminated)
    do {
        cCurrent = *sourcePtr;
        *destPtr = cCurrent;
        sourcePtr++;
        destPtr++;
    } while (cCurrent != '\0');

    // Increment global allocation counter for debugging
    gAllocationCount++;

    // If the original source was non-null, release it via the deallocation callback
    if (stringToCopy != (char*)0x0) {
        (* (void (__stdcall *)(char*)) deallocCallback)(stringToCopy);
    }

    return newString;
}