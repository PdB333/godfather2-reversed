// FUNC_NAME: SomeArray::findDataById
// Function at 0x00604d20: Searches an array of 0x101-byte entries (1 byte ID + 256 bytes data) for a matching ID.
// Returns pointer to the data portion (ID+1) of the matching entry, or 0 if not found.
// Structure layout:
//   +0x00: int count            // number of entries
//   +0x04: first entry:         // entry size = 0x101
//           +0x00: char id
//           +0x01: char data[0x100]
//   +0x105: second entry, etc.

int __thiscall SomeArray::findDataById(int *thisPtr, char targetId) {
    int index = 0;
    if (0 < *thisPtr) {
        // Point to the ID byte of the first entry (at thisPtr+1 as int* = byte offset +4)
        char *currentId = (char *)(thisPtr + 1);
        do {
            if (*currentId == targetId) {
                // Return pointer to the data after the ID
                return (int)thisPtr + 5 + index * 0x101;
            }
            index++;
            // Move to next entry's ID (each entry is 0x101 bytes)
            currentId += 0x101;
        } while (index < *thisPtr);
    }
    return 0;
}