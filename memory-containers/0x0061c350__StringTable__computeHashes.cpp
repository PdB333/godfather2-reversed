// FUNC_NAME: StringTable::computeHashes
// Function address: 0x0061c350
// Role: Relocates string pointers within a string table structure and computes hashes for each entry.
// The structure at 'this' contains:
//   +0x00: char* baseString (first string)
//   +0x04: uint8_t versionFlags? (byte at this+1)
//   +0x06: uint16_t numEntries
//   +0x08: uint32_t* hashArray (array of computed hashes)
//   +0x0C: Entry* entries (array of Entry, each 0x18 bytes)
// Each Entry structure:
//   +0x00: char* string
//   +0x10: char* anotherString
//   +0x14: char* subStrings (pointer to an array of substrings)
//   +0x0F: uint8_t numSubStrings
// Substring entry (5 bytes each):
//   byte0: if zero, then bytes1-4 are a pointer to the actual substring

void StringTable::computeHashes() {
    int* base = reinterpret_cast<int*>(this);
    int* entryPtr;
    char* stringPtr;
    uint16_t numEntries;
    int i, j;
    int hash;
    int entryIndex;
    uint8_t* entryBase;
    char* currentString;
    char* subStrings;
    char* subPtr;
    uint8_t numSubStrings;
    char ch;

    // Relocate the base pointers relative to 'this'
    base[0] = reinterpret_cast<int>(base) + base[0];  // baseString pointer fixup
    base[2] = reinterpret_cast<int>(base) + base[2];  // hashArray pointer fixup
    base[3] = reinterpret_cast<int>(base) + base[3];  // entries pointer fixup

    entryIndex = 0;
    numEntries = *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(base) + 6);
    if (numEntries != 0) {
        int localOffset = 0;
        do {
            entryPtr = reinterpret_cast<int*>(base[3] + localOffset);

            // Relocate entry pointers
            entryPtr[0] = reinterpret_cast<int>(base) + entryPtr[0];
            entryPtr[4] = reinterpret_cast<int>(base) + entryPtr[4];
            entryPtr[5] = reinterpret_cast<int>(base) + entryPtr[5];

            numSubStrings = *reinterpret_cast<uint8_t*>(reinterpret_cast<char*>(entryPtr) + 0x0F);
            if (numSubStrings != 0) {
                j = 0;
                subPtr = reinterpret_cast<char*>(entryPtr[5]);
                for (i = 0; i < numSubStrings; i++) {
                    if (*subPtr == '\0') {
                        // Relocate the subsequent pointer (4 bytes after null)
                        int* ptrToFix = reinterpret_cast<int*>(subPtr + 1);
                        *ptrToFix = reinterpret_cast<int>(base) + *ptrToFix;
                    }
                    j++;
                    subPtr += 5;
                }
            }

            // Check version flag (byte at base+1, i.e., offset 4)
            if (*reinterpret_cast<uint8_t*>(reinterpret_cast<char*>(base) + 4) < 3) {
                stringPtr = reinterpret_cast<char*>(*base);
                currentString = stringPtr;
                while (*currentString != '\0') {
                    currentString++;
                }
                hash = FUN_00ab8560(0, stringPtr, (currentString - stringPtr) - 1);

                stringPtr = reinterpret_cast<char*>(*entryPtr);
                currentString = stringPtr;
                while (*currentString != '\0') {
                    currentString++;
                }
                hash = FUN_00ab8560(hash, stringPtr, (currentString - stringPtr) - 1);

                *reinterpret_cast<uint32_t*>(base[2] + entryIndex * 4) = hash;
            }

            localOffset += 0x18;
            entryIndex++;
        } while (entryIndex < numEntries);
    }
    return;
}