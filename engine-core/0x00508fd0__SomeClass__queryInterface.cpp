// FUNC_NAME: SomeClass::queryInterface
// Address: 0x00508fd0
// Role: Interface query supporting two known interface IDs (swapcase-like COM QueryInterface). Returns this pointer for supported IDs.

bool __thiscall SomeClass::queryInterface(void *thisPtr, int interfaceId, void **outPtr) {
    // Check for first supported interface ID (0x8EFAA286 = -0x71055d7a)
    if (interfaceId == -0x71055d7a) {
        if (outPtr != nullptr) {
            *outPtr = thisPtr;
        }
        return true;
    } else {
        // Clear output pointer if non-null
        if (outPtr != nullptr) {
            *outPtr = nullptr;
        }
        // Check for second supported interface ID (0xFFD2E5B1 = -0x2d1a4f)
        if (interfaceId != -0x2d1a4f) {
            return false;
        }
        // Second interface supported – set output pointer and return success
        if (outPtr != nullptr) {
            *outPtr = thisPtr;
        }
        return true;
    }
}