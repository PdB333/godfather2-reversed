// FUNC_NAME: EventQueue::popMatchingEntry
char EventQueue::popMatchingEntry(Entry* entries, int* entryCountPtr, int* queryParams) {
    char result = '\0';
    uint index = 0;

    // Check if the total number of entries (entryCount * 3) is non-zero
    if (*entryCountPtr * 3 != 0) {
        char* flagPtr = (char*)(entries + 0x20); // Points to flag byte of first entry (offset +0x20)

        do {
            if (*flagPtr != '\0') { // Entry is occupied
                // Determine if first two fields of entry are both zero
                bool entryFieldsZero = (*(int*)(flagPtr - 0x20) == 0 && *(int*)(flagPtr - 0xc) == 0);
                // Determine if queryParams[0] and queryParams[5] are both zero
                bool queryFieldsZero = (queryParams[5] == 0 && queryParams[0] == 0);

                // Match if both boolean flags are equal and fields at offsets +0x18 and +0x1c match queryParams[6] and [7]
                if (entryFieldsZero == queryFieldsZero &&
                    *(int*)(flagPtr - 0x8) == queryParams[7] &&
                    *(int*)(flagPtr - 0x4) == queryParams[6]) {
                    result = *flagPtr;
                    *flagPtr = '\0'; // Remove the entry
                    break; // Assuming function returns after first match
                }
            }
            index++;
            flagPtr += 0x24; // Move to next entry (each entry is 0x24 bytes)
        } while (index < (uint)(*entryCountPtr * 3));
    }
    return result;
}