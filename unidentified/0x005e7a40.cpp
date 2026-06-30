// FUN_NAME: HashTable::lookupEntry
// Function at 0x005e7a40: looks up a 12-byte data entry from a hash table using an XOR-transformed key.
// Returns success flag in high byte (0 or 1) and the original XORed key's upper 24 bits in lower bytes.
// The hash table is a global structure at address DAT_01223504.
// Layout of hash table base:
//   +0x00: unknown?
//   +0x04: array[256] of pointer to entries (each 4 bytes?) Actually offset 4 + (low byte index)*4 yields a pointer.
//   +0x1c: byte count (max table size?)
// Each entry (at that pointer) contains:
//   +0x40: first uint (data[0])
//   +0x44: second uint (data[1])
//   +0x48: third uint (data[2])

typedef unsigned int uint32_t;
typedef unsigned char byte;

// Global pointer to hash table base (initialized elsewhere)
extern void* g_hashTableBase;  // DAT_01223504

uint32_t hashTableLookupEntry(uint32_t key, uint32_t* outData)
{
    byte tableCount;
    uint32_t xoredKey;
    byte success = 0;
    uint32_t entryPtr;
    uint32_t data0, data1, data2;

    // Read the byte at base+0x1c
    tableCount = *(byte*)((char*)g_hashTableBase + 0x1c);

    // XOR the input key with a constant
    xoredKey = key ^ 0xad103100;

    // Check if the xored key is less than the table count, tableCount != 0,
    // and the low byte of the original key is also less than tableCount.
    if ((xoredKey < tableCount) && (tableCount != 0) && ((byte)key < tableCount))
    {
        // Use low byte of original key as index into an array of pointers at base+4
        entryPtr = *(uint32_t*)((char*)g_hashTableBase + 4 + ((key & 0xff) * 4));
        if (entryPtr != 0)
        {
            // Read 12 bytes from entry+0x40
            data0 = *(uint32_t*)(entryPtr + 0x40);
            data1 = *(uint32_t*)(entryPtr + 0x44);
            data2 = *(uint32_t*)(entryPtr + 0x48);
            success = 1;
        }
    }

    if (success)
    {
        // Copy data to output (3 uints)
        outData[0] = data0;
        outData[1] = data1;
        outData[2] = data2;
    }

    // Return: high byte is success flag, low 24 bits are xoredKey >> 8
    return (success << 24) | (xoredKey >> 8);
}