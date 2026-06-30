// FUNC_NAME: NameTable_FindOrInsert
// Address: 0x00660590
// This function searches a global table of 32-byte records for a match with a global pattern.
// If found, returns the index; if not found, inserts into the first empty slot and returns that index.
// Returns -1 if table is full.

#define NAME_TABLE_SIZE 32
#define NAME_RECORD_SIZE 32 // 8 ints

// Global table of 32-byte records (starting at address 0x01206008)
extern int g_NameTable[NAME_TABLE_SIZE][8];

// Global pattern to search/insert (starting at address 0x00e2a708)
extern int g_InputPattern[8];

// __cdecl (default)
int NameTable_FindOrInsert()
{
    int index;
    int result;
    int* tableEntry;
    int* patternEntry;
    int* emptySlotPtr;
    int diff;
    int i;

    // Linear search through table
    index = 0;
    tableEntry = &g_NameTable[0][0];
    do {
        int bytesRemaining = NAME_RECORD_SIZE; // 0x20
        patternEntry = &g_InputPattern[0];
        // Compare full record (8 ints = 32 bytes)
        do {
            if (*tableEntry != *patternEntry) {
                goto not_equal;
            }
            bytesRemaining -= 4; // 4 bytes per int
            patternEntry++;
            tableEntry++;
        } while (bytesRemaining > 12); // loop while > 3 ints remaining (i.e., after 4 comparisons? Actually condition is 3 < uVar2, so while uVar2 > 3. Since uVar2 decrements by 4 each iteration, this loop runs until uVar2 <= 3. That means it compares the first 5 ints (since initially 32, after 5 iterations uVar2 becomes 12? Wait: 32 -> 28 -> 24 -> 20 -> 16 -> 12. After 5 iterations uVar2=12, condition 3<12 true, so it continues. After 6th: 8, 3<8 true. After 7th: 4, 3<4 true. After 8th: 0, 3<0 false, exit loop. So it compares all 8 ints. But the unrolled logic is messy. Simplified here.

        // If all ints matched (bytesRemaining == 0)
        if (bytesRemaining == 0) {
            result = 0; // match found
        } else {
            // Partial match not possible here, but code flows to not_equal
            goto not_equal;
        }

        // Check match
        if (result == 0) {
            return index;
        }

    not_equal:
        // Byte-level comparison to determine ordering (not used for decision, only for match check)
        // Actually the original code after LAB_006605c8 does a byte-by-byte difference
        // to compute iVar3 (1, 0, -1). But then it checks if iVar3 == 0.
        // Since we know they are not equal (because first int mismatch), we can compute diff to be nonzero.
        // Clean implementation:
        // We'll compute the first differing byte for logic, but result is not used.
        // For simplicity, we just skip to next entry.

        tableEntry = &g_NameTable[0][0] + (index + 1) * 8; // advance to next record
        index++;
        if ((uint)tableEntry > 0x01206407) { // check if beyond table end
            // Table exhausted, search for empty slot
            index = 0;
            // Scan for first record whose first int is zero
            emptySlotPtr = &g_NameTable[0][0];
            do {
                if (*emptySlotPtr == 0) {
                    // Found empty slot, insert pattern
                    int slotOffset = index * 8; // in ints
                    g_NameTable[index][0] = g_InputPattern[0];
                    g_NameTable[index][1] = g_InputPattern[1];
                    g_NameTable[index][2] = g_InputPattern[2];
                    g_NameTable[index][3] = g_InputPattern[3];
                    g_NameTable[index][4] = g_InputPattern[4];
                    g_NameTable[index][5] = g_InputPattern[5];
                    g_NameTable[index][6] = g_InputPattern[6];
                    g_NameTable[index][7] = g_InputPattern[7];
                    return index;
                }
                emptySlotPtr += 8; // next record (8 ints)
                index++;
            } while ((int)emptySlotPtr < 0x01206408); // while within bounds
            // Table full
            return -1;
        }
    } while(1); // infinite loop until match or full
}