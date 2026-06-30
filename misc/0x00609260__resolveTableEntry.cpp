// FUNC_NAME: resolveTableEntry

struct TableEntry {
    int    field0;       // +0x00 (return value)
    int    field4;       // +0x04 (used when flag == 0)
    int    field8;       // +0x08 (low byte = flag)
    float  field12;      // +0x0C (multiplier base if flag != 0)
    float  field16;      // +0x10 (multiplier base if flag != 0)
    int    field20;      // +0x14 (unused in this function)
};

// global state
extern int   g_tableEnabled;             // DAT_011f3910
extern short g_someIndex;                // DAT_011f3914
extern int   g_tableCount;               // DAT_00f15a6c   (number of entries in table)
extern float g_multiplier1;              // DAT_0120587c
extern float g_multiplier2;              // DAT_01205880

// The table is stored as an array of TableEntry starting at g_tableBase.
// The pointer g_tableMid points to the field8 of the first entry,
// which is the base for the iterative search.
extern TableEntry g_tableBase[];         // DAT_0120577c (first element)
extern char* g_tableMid;                 // DAT_01205770 (points to &g_tableBase[0].field8)

// Forward declaration of a helper called during initialization
void processIndex(short value);          // FUN_006066e0

int __cdecl resolveTableEntry(unsigned short param1, unsigned short param2) {
    if (g_tableEnabled == 0) {
        return g_tableBase[0].field0;    // DAT_0120577c (first entry's field0)
    }

    processIndex(g_someIndex);

    char* current = g_tableMid;          // points to field8 of first entry
    for (int i = 0; i < g_tableCount; ++i) {
        unsigned int uVar2;
        // First comparison: param1
        if (*current == '\0') {
            uVar2 = *(unsigned int*)(current - 8);   // field0
        } else {
            uVar2 = (unsigned int)(g_multiplier1 * *(float*)(current + 4)); // field12
            if ((int)uVar2 < 1) {
                uVar2 = 1;
            }
        }
        if (uVar2 == param1) {
            // Second comparison: param2
            if (*current == '\0') {
                uVar2 = *(unsigned int*)(current - 4); // field4
            } else {
                uVar2 = (unsigned int)(g_multiplier2 * *(float*)(current + 8)); // field16
                if ((int)uVar2 < 1) {
                    uVar2 = 1;
                }
            }
            if (uVar2 == param2) {
                return ((int*)g_tableBase)[i * 6]; // &g_tableBase[i].field0
            }
        }
        current += sizeof(TableEntry); // 0x18 bytes
    }
    return g_tableBase[0].field0; // fallback
}