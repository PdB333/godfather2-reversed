// FUN_NAME: HashTable::findIndex
// Address: 0x00558d40
// Role: Finds the index of an entry in a hash table by a combined key (object pointer + hash byte).
// The table entries are 0x1c bytes, starting at base + 0x40.
// If the computed key matches the sentinel, returns extraOffset + count (e.g., for append slot).

uint __thiscall HashTable::findIndex(void* thisPtr, void* keyObject, uint extraOffset)
{
    // Descriptor structure at thisPtr+0x04: { int** basePtrPtr; int count; }
    // basePtrPtr points to a location that holds the actual base address of the entry array.
    int descriptorPtr = *(int**)((uint)thisPtr + 0x04);
    int count = *(int*)(descriptorPtr + 4);                     // uVar1: number of entries
    int baseAddr = **(int**)descriptorPtr;                     // base address from double indirect
    int entryArray = baseAddr + 0x40;                          // entries start at base+0x40

    // Compute key from keyObject: pointer value + byte at offset 0x10 (e.g., hash or length)
    uint8 hashByte = *(uint8*)((uint)keyObject + 0x10);
    uint key = (uint)keyObject + hashByte;

    // Check sentinel key at thisPtr+0x1c; if match, return special index
    int sentinelKey = *(int*)((uint)thisPtr + 0x1c);
    if (key == (uint)sentinelKey)
        return extraOffset + count;

    // Linear search over entries of size 0x1c bytes
    for (uint i = 0; i < count; i++)
    {
        int entryKey = *(int*)(entryArray + i * 0x1c);  // first int of each entry is the key
        if (entryKey == (int)key)
            return i;
    }

    return 0xffffffff;  // not found
}