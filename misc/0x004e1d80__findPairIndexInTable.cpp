// FUNC_NAME: findPairIndexInTable

// Function at 0x004e1d80: Searches a global table of 0x56-byte entries for a pair of short IDs.
// Returns 1 and sets *outIndex to the entry index if found; returns 0 otherwise.
// Likely __fastcall: first param in ECX? But signature shows uint* and short; extra short in DX (unaff_DI).
uint32_t findPairIndexInTable(uint32_t *outIndex, short id1, short id2) // id2 likely passed in DX register
{
    uint32_t ret = 0;
    uint32_t index = 0;

    if (g_entryCount != 0) {
        short *pEntrySecondShort = &g_entryArray[0].secondShort; // points to second short of first entry

        while (pEntrySecondShort[-1] != id1 || *pEntrySecondShort != id2) {
            index++;
            pEntrySecondShort += 86; // 0x56 bytes per entry (86 shorts? Actually 86 bytes, short size 2, so +43 shorts? Wait, 0x56 / 2 = 43 shorts. But pointer increment by 0x56 bytes means +86 short positions? No: pEntrySecondShort is short*, so incrementing by 0x56 bytes means adding 0x56/sizeof(short) = 0x56/2 = 43 short offsets. But the code says psVar3 + 0x56, which on a short pointer adds 0x56 * 2 = 172 bytes? Wait, careful: In C, pointer arithmetic adds the number of elements, not bytes. The decompiler says "psVar3 = psVar3 + 0x56". But that's in the decompiled pseudo-C; the actual assembly might add 0x56 bytes. Ghidra's decompiler assumes pointer increments are in units of the pointed-to type. Since psVar3 is short*, +0x56 adds 0x56*2 = 172 bytes. That contradicts the entry size being 0x56 bytes. So the decompiler likely misinterpreted the pointer type. The actual array is of structures of size 0x56 bytes, and the pointer should be char* or struct pointer. The increment should be by 0x56 bytes, not by 0x56 shorts. The decompiler incorrectly typed the pointer as short* because it saw short comparisons. To reconstruct correctly, we'll use a struct and increment by sizeof(Entry).)
            // Use byte offset to advance by 0x56 bytes.
            // We'll cast to (char*) or use a struct pointer.
            // To be safe, reinterpret pEntrySecondShort as byte pointer and advance by 0x56.
            pEntrySecondShort = (short*)((char*)pEntrySecondShort + 0x56);
            if (g_entryCount <= index) {
                return ret;
            }
        }
        *outIndex = index;
        ret = 1;
    }
    return ret;
}

// Global data: number of entries (0x012054d8)
extern uint32_t g_entryCount; // DAT_012054d8

// Structure for each entry (size 0x56 bytes)
struct EntryPair {
    short id1; // first short, at offset 0
    short id2; // second short, at offset 2
    // ... remaining 0x52 bytes (82 bytes) of unknown data
};

// Array of entries starting at 0x0119455a
extern EntryPair g_entryArray[]; // DAT_0119455a