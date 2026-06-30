// FUNC_NAME: SimManager::getSimObjectList
// Function at 0x00543390: Fills an output array with adjusted object pointers from an internal list.
// Returns true if any valid (non-null, non-0x48) object was found.
// this+0x2b8: pointer to array of 8-byte entries (each first 4 bytes is a pointer to an int)
// this+700: count of entries
// param_2: output array of int* (size at least param_3)
// param_3: maximum number of entries to process
// The stored pointer points to an int that is the actual object pointer minus 0x48.
// So we add 0x48 to get the base? Actually we subtract 0x48 from the dereferenced int.
// That suggests the stored int is the base + 0x48, so we subtract to get base.
// If the stored int is 0 or 0x48, the output is 0.

bool __thiscall SimManager::getSimObjectList(int* outputArray, uint maxCount)
{
    bool foundValid = false;
    uint count = *(uint*)(this + 700); // number of entries in the internal list
    if (outputArray != 0 && count != 0) {
        for (uint i = 0; i < count; i++) {
            if (i >= maxCount) {
                return foundValid;
            }
            // Each entry in the internal list is 8 bytes; first 4 bytes is a pointer to an int
            int* entryPtr = *(int**)(*(int*)(this + 0x2b8) + i * 8);
            int rawValue;
            if (entryPtr == 0) {
                rawValue = 0;
            } else {
                rawValue = *entryPtr - 0x48; // adjust to get base object pointer
            }
            outputArray[i] = rawValue;
            // Check if the original value was valid (non-zero and not the sentinel 0x48)
            int original = *entryPtr;
            if (original != 0 && original != 0x48) {
                foundValid = true;
            }
        }
    }
    return foundValid;
}