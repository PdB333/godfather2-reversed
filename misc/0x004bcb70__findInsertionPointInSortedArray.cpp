// FUNC_NAME: findInsertionPointInSortedArray
typedef struct InsertionSearchParams {
    int start;        // +0x04: Starting index offset (maybe count of used slots)
    uint maxCount;    // +0x08: Maximum number of slots in the table
    float value;      // +0x0c: Value to insert (find first index where table[index] >= value)
};

// Global state for sorted float table search
static float* g_floatTable;          // DAT_010c2680 - Array of sorted floats
static uint g_tableMask;             // DAT_010c2678 - Mask to index into table (e.g., 0x7FF)
static uint g_searchCursor;          // DAT_012054b4 - Persistent cursor for linear search (continues from last call)

uint __fastcall findInsertionPointInSortedArray(void* unused, InsertionSearchParams* params)
{
    uint uVar3 = params->start + 2;  // Extend search range by 2 from start
    if (params->maxCount < uVar3) {
        uVar3 = params->maxCount;
    }
    uint index = 0;                  // Local counter tracking absolute position from start of search
    uint currentCursor = g_searchCursor; // Load persistent cursor

    // Unrolled loop: process 4 candidates at a time
    if (uVar3 > 3) {
        do {
            if (params->value <= g_floatTable[g_tableMask & currentCursor]) {
                g_searchCursor = currentCursor + 1;
                return index;
            }
            g_searchCursor = currentCursor + 2; // Note: cursor updated but not yet used in next check
            if (params->value <= g_floatTable[g_tableMask & (currentCursor + 1)]) {
                return index + 1;
            }
            g_searchCursor = currentCursor + 3;
            if (params->value <= g_floatTable[g_tableMask & (currentCursor + 2)]) {
                return index + 2;
            }
            currentCursor += 4;
            if (params->value <= g_floatTable[g_tableMask & g_searchCursor]) { // g_searchCursor updated above
                g_searchCursor = currentCursor;
                return index + 3;
            }
            index += 4;
            g_searchCursor = currentCursor;
        } while (index < uVar3 - 3);
    }

    // Remaining elements (less than 4)
    if (index < uVar3) {
        while (true) {
            uint tableIndex = g_tableMask & g_searchCursor;
            g_searchCursor++;
            if (params->value <= g_floatTable[tableIndex]) break;
            index++;
            if (uVar3 <= index) {
                g_searchCursor = currentCursor; // Note: currentCursor is not updated in this path? Actually currentCursor is the original before unrolled loop. Might be bug, but matching decomp.
                return index;
            }
        }
    }
    return index;
}