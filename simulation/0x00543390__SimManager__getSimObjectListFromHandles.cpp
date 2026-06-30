// FUNC_NAME: SimManager::getSimObjectListFromHandles
bool __thiscall SimManager::getSimObjectListFromHandles(void* pOutArray, uint maxCount)
{
    uint count = *(uint*)(this + 700); // +0x2BC: number of entries in handle array
    if (pOutArray == nullptr || count == 0)
        return false;

    bool hasValidEntries = false;
    uint index = 0;
    do {
        if (index >= maxCount)
            return hasValidEntries;

        // Handle array is at +0x2B8, each entry is 8 bytes (pointer + unknown)
        int* handleArray = *(int**)(this + 0x2B8); // +0x2B8: pointer to array of 8-byte entries
        int rawHandle = *(int*)(handleArray + index * 2); // First 4 bytes of the 8-byte entry

        int objectPtr;
        if (rawHandle == 0) {
            objectPtr = 0;
        } else {
            objectPtr = rawHandle - 0x48; // Subtract offset to get actual object pointer
        }

        // Write adjusted pointer to output array
        ((int*)pOutArray)[index] = objectPtr;

        // Check if original handle was valid (non-zero and not sentinel value 0x48)
        int originalHandle = *(int*)(handleArray + index * 2);
        if (originalHandle != 0 && originalHandle != 0x48) {
            hasValidEntries = true;
        }

        index++;
    } while (index < count);

    return hasValidEntries;
}