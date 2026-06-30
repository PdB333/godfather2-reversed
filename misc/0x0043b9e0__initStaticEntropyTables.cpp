// FUNC_NAME: initStaticEntropyTables
// Function address: 0x0043b9e0
// Initializes static global variables for entropy coding (likely Huffman or bitstream).
// Sets g_bitCount = 5 (bits to represent 0x1f), g_fullMask = 0xFFFFFFFF, zeroes a 128-byte table
// and updates g_tableIndex to 127. Returns pointer to g_bitCount.

// Static globals (addresses from decompilation):
// g_bitCount    (int)   at 0x0120e710
// g_fullMask    (int)   at 0x0120e714
// g_table       (byte*) at 0x0120e718 (128 bytes)
// g_tableIndex  (int)   at 0x0120e918

static int g_bitCount;       // +0x0120e710
static int g_fullMask;       // +0x0120e714
static byte g_table[128];    // +0x0120e718
static int g_tableIndex;     // +0x0120e918

__declspec(naked) int* initStaticEntropyTables()
{
    __asm {
        // Original assembly not provided; reconstructing from decompiled C.
    }

    // Decompiled logic:
    g_bitCount = 0;
    g_fullMask = 0;
    g_tableIndex = 0;

    // Compute bit count for 0x1f (31) -> 5
    unsigned int temp = 0x1f;
    while (temp != 0)
    {
        g_bitCount++;
        temp >>= 1;
    }

    // Set all 32 bits in fullMask
    for (unsigned int i = 0; i < 32; i++)
    {
        g_fullMask |= 1 << (i & 0x1f);
    }

    // Zero out 128 bytes of g_table and track index
    unsigned int index = 0;
    for (int loop = 0; loop < 32; loop++)
    {
        if (index < 128)
        {
            g_table[index] = 0;
            index = ++g_tableIndex;
        }
        if (index < 128)
        {
            g_table[index] = 0;
            index = ++g_tableIndex;
        }
        if (index < 128)
        {
            g_table[index] = 0;
            index = ++g_tableIndex;
        }
        if (index < 128)
        {
            g_table[index] = 0;
            index = ++g_tableIndex;
        }
    }

    // After zeroing, g_tableIndex == 127

    return &g_bitCount; // Return pointer to the first global (handle)
}