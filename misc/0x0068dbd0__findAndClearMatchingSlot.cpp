// FUNC_NAME: findAndClearMatchingSlot
// Function at 0x0068dbd0: Searches an array of slots (entry size 0x24) for one that matches criteria in key.
// Returns the slot's char identifier (at +0x20) and clears it to zero if found, else returns '\0'.

char __fastcall findAndClearMatchingSlot(void* baseObj, int* countInfo, int* key)
{
    char result = '\0';
    uint i = 0;
    int numSlots = *countInfo * 3; // Number of slots is three times the given value

    if (numSlots != 0) {
        char* slotCharPtr = (char*)((int)baseObj + 0x20); // Array of slots starts at offset 0x20 in baseObj
        do {
            if (*slotCharPtr != '\0') {
                // Check the "flags" at offset 0x00 and 0x14 of this slot
                bool slotFlagsActive = (*(int*)(slotCharPtr - 0x20) != 0) || (*(int*)(slotCharPtr - 0x0C) != 0);
                bool keyFlagsActive = (key[5] != 0) || (key[0] != 0);
                if (slotFlagsActive == keyFlagsActive &&
                    *(int*)(slotCharPtr - 4) == key[7] &&  // Compare offset +0x1C to key[7]
                    *(int*)(slotCharPtr - 8) == key[6])    // Compare offset +0x18 to key[6]
                {
                    result = *slotCharPtr;
                    *slotCharPtr = '\0'; // Clear the identifier
                }
            }
            i++;
            slotCharPtr += 0x24; // Advance to next slot (0x24 bytes per entry)
        } while (i < (uint)numSlots);
    }
    return result;
}