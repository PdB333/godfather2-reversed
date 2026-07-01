// FUNC_NAME: TextManager::setStringTableEntry
// This function sets a 32-byte string in a text table indexed by major, minor, and string indices.
// The global table (starting at PTR_DAT_00e564f8) contains an array of 8-byte structures.
// Each structure holds a pointer to a block of 100-byte entries.
// Each 100-byte entry has a 4-byte flag at offset 0 and a 32-byte string at offset (stringIndex*0xC + 2)*4.
// The string copy is guarded by a check that the entry's flag is non-zero.
// Returns 1 on success, 0 if the entry's flag is zero.

int __thiscall TextManager::setStringTableEntry(int thisPtr, char *text)
{
    // Global pointer array base (interpreted as int* for indexing)
    // PTR_DAT_00e564f8 is a static pointer variable; its address is the start of an array of 8-byte structures.
    // Structure at index majorIndex: first int is a pointer to a 100-byte block array.
    int majorIndex = *(int *)(thisPtr + 0x58);
    int minorIndex = *(int *)(thisPtr + 0x54);
    int stringIndex = *(int *)(thisPtr + 0x5c);

    // Get the pointer to the 100-byte block array for the given major index
    int *blockArrayPtr = (int *)(((int *)(&PTR_DAT_00e564f8))[majorIndex * 2]);
    // Offset to the specific 100-byte entry
    int *entry = (int *)((char *)blockArrayPtr + minorIndex * 100);

    // Check if the entry's flag (first int) is non-zero
    if (*entry == 0)
    {
        return 0;
    }

    // Calculate destination string offset within the entry: (stringIndex * 12 + 2) * 4 bytes
    char *dest = (char *)entry + (stringIndex * 12 + 2) * 4;
    // Safe copy (max 32 characters)
    _strcpy_s(dest, 0x20, text);
    return 1;
}