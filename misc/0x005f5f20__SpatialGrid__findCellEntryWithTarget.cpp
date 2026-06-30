// FUNC_NAME: SpatialGrid::findCellEntryWithTarget
// Function address: 0x005f5f20
// Searches for an entry in the spatial grid matching the given target and coordinate.
// Returns the cell address (offset from m_cellDataBase) if found, else 0.

// Forward declarations of helper functions
int __thiscall createOrGetEntry(int this, int index); // FUN_005faf10
void __thiscall releaseEntry(int* entryPtr);          // FUN_004daf90

// Structure for the "this" object (SpatialGrid)
struct SpatialGrid {
    int field_0x00;            // unknown
    int field_0x04;            // unknown
    int field_0x08;            // unknown
    // ... (many fields)
    int* m_cellDataBase;       // +0x28 - base pointer for cell data
    int m_cellOffset;          // +0x30 - offset for cell array
    ushort* m_lookupTable;     // +0x34 - lookup table mapping indices to values
    int** m_entryArray;        // +0x38 - array of pointers to entries (each entry pointer stored, 8 bytes per slot?)
};

// Structure for the search key (param_2)
struct SearchKey {
    // ... (fields before 0x15)
    byte m_numLayers;          // +0x15 - number of layers to iterate
    short m_baseIndex;         // +0x16 - base index for layer computation
};

// Structure for the search criteria (param_3)
struct SearchCriteria {
    int m_target;              // +0x00 - target object pointer to match
    // +0x04 unknown (not used)
    int m_someValue;           // +0x08 - value used for coordinate comparison
};

// Return value: pointer to cell data (int*, offset from m_cellDataBase) if found, else 0.
int __thiscall SpatialGrid::findCellEntryWithTarget(int param_1, int param_2, int* param_3)
{
    SearchCriteria* criteria = (SearchCriteria*)param_3;
    SearchKey* key = (SearchKey*)param_2;
    SpatialGrid* grid = (SpatialGrid*)param_1;

    int target = criteria->m_target;
    if (target == 0) {
        return 0;
    }

    int someValue = criteria->m_someValue;
    int targetField20 = *(int*)(target + 0x20);  // some field of the target object

    int counter = 0;
    if (key->m_numLayers != 0) {
        do {
            // Compute cell address: (baseIndex + counter) * 0x10 + cellOffset
            int cellAddr = ( (ushort)(key->m_baseIndex + (short)counter) ) * 0x10 + grid->m_cellOffset;
            int entry = 0;

            // Read index at cellAddr + 0xc
            ushort idx = *(ushort*)(grid->m_lookupTable + (uint)*(ushort*)(cellAddr + 0xc));
            if (idx != 0xffff) {
                // Compute pointer to entry slot (each entry is 8 bytes? Actually m_entryArray is array of pointers, each slot is sizeof(int*)?)
                // Index * 8 suggests each entry in m_entryArray is 8 bytes (maybe a pair of ints or a structure)
                int entrySlotOffset = (uint)*(ushort*)(cellAddr + 0xc) * 8;
                int* entrySlot = &grid->m_entryArray[entrySlotOffset / sizeof(int*)]; // simplified: treat as byte offset
                int firstEntry = grid->m_entryArray[entrySlotOffset];  // first int of the slot (treated as pointer)
                if (firstEntry == 0) {
                    // Entry not yet created; create it using the lookup value
                    int createParam = (uint)idx * 0x10 + (int)grid->m_cellDataBase;
                    int newEntry = createOrGetEntry((int)grid, createParam);
                    if (newEntry != 0) {
                        // Link the new entry into the array slot
                        if (grid->m_entryArray[entrySlotOffset] != newEntry) {
                            if (grid->m_entryArray[entrySlotOffset] != 0) {
                                releaseEntry(&grid->m_entryArray[entrySlotOffset]);  // release old entry
                            }
                            grid->m_entryArray[entrySlotOffset] = newEntry;
                            // +4 offset: store a pointer to the slot itself? (singly linked list or back pointer)
                            grid->m_entryArray[entrySlotOffset + 1] = *(int*)(newEntry + 4);
                            *(int**)(newEntry + 4) = &grid->m_entryArray[entrySlotOffset];
                        }
                        firstEntry = newEntry;
                    }
                } else {
                    firstEntry = firstEntry;
                }
                entry = firstEntry;
            }

            // Check if the entry matches target and the coordinate matches
            if (entry == target && *(short*)(cellAddr + 4) == (short)((someValue - targetField20) / 0x24)) {
                return cellAddr;  // return address of cell data (relative to m_cellDataBase)
            }
            counter++;
        } while (counter < (int)(uint)key->m_numLayers);
    }
    return 0;
}