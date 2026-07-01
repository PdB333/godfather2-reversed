// FUNC_NAME: QuadWordSet::contains
// Function at 0x0083faa0: Searches a list of 128-bit (4-int) keys for a match.
bool __thiscall QuadWordSet::contains(int thisPtr, int* key) {
    int count = *(int*)(thisPtr + 0x50); // +0x50: number of entries
    if (count > 0) {
        int* entries = *(int**)(thisPtr + 0x58); // +0x58: pointer to array of entries (each entry is 4 ints)
        for (int i = 0; i < count; i++) {
            if (entries[0] == key[0] && entries[1] == key[1] && entries[2] == key[2] && entries[3] == key[3]) {
                return true;
            }
            entries += 4; // advance to next entry
        }
    }
    return false;
}