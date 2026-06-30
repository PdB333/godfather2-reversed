// FUNC_NAME: ObjectManager::findNextMatchingObject
// Address: 0x006bb240
// Role: Iterates through an array of 0x18-byte structures, skipping empty/deleted slots, and checks a matching condition via an external function.

// Constants for array element status
const int kInvalidSlot = 0x48; // Possibly marks unused or deleted objects

// External function used to check if an object matches the desired condition.
// Address 0x007914e0 - likely returns an identifier or property value.
extern int __cdecl GetObjectMatchProperty();

// Returns 1 if a matching object is found, 0 otherwise.
// Updates *outIndex to the index of the matching object (or remains at the last checked index if not found).
// The array is stored at this+0xA0 (pointer to array of structs of size 0x18) and count at this+0xA4.
__thiscall int ObjectManager::findNextMatchingObject(int this, int matchingValue, uint* outIndex) {
    int objectPtr;

    // Advance to next index
    *outIndex = *outIndex + 1;

    // If we've reached the end of the array, no match
    if (*outIndex >= *(uint*)(this + 0xA4)) {
        return 0;
    }

    // Loop while the current slot is invalid or doesn't match
    while (true) {
        // Read the first field of the structure at current index (0x18 bytes per element)
        objectPtr = *(int*)(*(int*)(this + 0xA0) + *outIndex * 0x18);
        
        // Skip if slot is empty (0) or marked as invalid (0x48)
        if (objectPtr != 0 && objectPtr != kInvalidSlot) {
            // Call external check function; compare result to matchingValue
            if (GetObjectMatchProperty() == matchingValue) {
                // Match found
                return 1;
            }
        }

        // Move to next index
        *outIndex = *outIndex + 1;
        if (*outIndex >= *(uint*)(this + 0xA4)) {
            return 0;
        }
    }

    // Unreachable
    return 0;
}