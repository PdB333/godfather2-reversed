// FUNC_NAME: SomeClass::isDataFlagSet
// Address: 0x0083b6d0
// This function checks a flag in a data structure retrieved by a hash lookup.
// It returns 1 if the flag is not set, 0 if it is set.
// The first parameter (this) is unused; the second parameter points to an object with a short ID at offset 0x12.

bool SomeClass::isDataFlagSet(void* unusedThis, int objectPtr) {
    char* dataPtr = nullptr;
    int dataSize = 0;

    // Call a lookup function with a short ID from the object, a hash constant, and a pointer to receive data.
    bool success = FUN_005fd340(*(short*)(objectPtr + 0x12), 0x48043505, &dataPtr);

    if (success) {
        uint flags = 0;
        // Check if data is valid: non-null, size > 0, and type byte at offset 6 equals 2.
        if ((dataPtr != nullptr) && (dataSize != 0) && (dataPtr[6] == 0x02)) {
            flags = *(uint*)dataPtr; // Read first 4 bytes as flags
        }
        // If bit 3 (value 8) is set, return false (0)
        if ((flags & 8) != 0) {
            return false;
        }
    }
    return true;
}