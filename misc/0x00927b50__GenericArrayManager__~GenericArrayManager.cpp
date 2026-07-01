// FUNC_NAME: GenericArrayManager::~GenericArrayManager
void __thiscall GenericArrayManager::~GenericArrayManager(uint *this) {
    uint loopIndex;
    uint *elementPtr;

    // Set vtable pointer (offset +0x0)
    *this = (uint)&VMT_GenericArrayManager;

    // Check if element count at offset +0xC8 is non-zero
    if (this[0x32] != 0) { // offset 0xC8 = 0x32 * 4
        elementPtr = this + 0x2A; // offset +0xA8 = 0x2A * 4 (start of array)
        for (loopIndex = 0; loopIndex < this[0x32]; loopIndex++) {
            // Destroy element at current position (each element is 8 bytes)
            releaseElement(elementPtr);   // FUN_004086d0
            deallocateElement(elementPtr); // FUN_00408310
            elementPtr += 2; // advance by 8 bytes
        }
    }
    // Global cleanup
    finalizeCleanup(); // FUN_004083d0
}