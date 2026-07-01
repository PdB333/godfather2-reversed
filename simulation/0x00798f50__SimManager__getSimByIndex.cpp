// FUNC_NAME: SimManager::getSimByIndex
// Function at 0x00798f50: Accessor for an array of 4-byte values at offset 0x2950.
// Likely returns a pointer or ID for an object by index, used extensively by many manager functions.
int __thiscall SimManager::getSimByIndex(int index) {
    // +0x2950: array of pointers/IDs (each 4 bytes)
    return *(int*)(this + 0x2950 + index * 4);
}