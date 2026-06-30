// FUNC_NAME: SpatialHashTable::findEntityInRange

// Function: 0x006e68b0
// Searches a spatial hash table (32x32 grid) for an entity within vertical range at a given position,
// with optional filter callback.

// Constants from binary
static const float g_fVerticalThreshold = *(float*)0x00d5eee4;   // Compare threshold for Y difference
static const unsigned int g_uAbsMask = *(unsigned int*)0x00e44680; // Likely 0x7FFFFFFF (absolute value)

// Probe table at 0x0112a960: 29 pairs of signed byte offsets (dx, dz)
static const char g_probeTable[29][2] = {
    // Actual data omitted; pair values from binary
};

// Structure for filtering entities (vtable-based)
struct EntityFilter {
    virtual char isValid(int entity) const = 0;  // Returns 0 if entity passes filter
};

// __thiscall SpatialHashTable::findEntityInRange
int __thiscall SpatialHashTable_findEntityInRange(void* thisPtr, float* pos, EntityFilter* filter) {
    // pos[0] = X, pos[1] = Y (vertical), pos[2] = Z
    int cellX = ((int)pos[0] >> 3) & 0x1F;          // 5-bit X cell
    int cellZ = ((int)pos[2] >> 3) & 0x1F;          // 5-bit Z cell
    int baseCell = cellZ * 0x20 + cellX;             // Combined index (0-1023)

    const char (*probe)[2] = g_probeTable;
    const char (*probeEnd)[2] = g_probeTable + 29;  // 29 pairs

    while (probe < probeEnd) {
        int dz = (signed char)(*probe)[1];          // Signed Z offset
        int dx = (signed char)(*probe)[0];          // Signed X offset
        // Compute bucket index using probe offsets modulo grid size
        int bucketIndex = ((dz * 0x20 + baseCell) & 0x3E0) | ((dx + baseCell) & 0x1F);
        // Access bucket array at this+0x20, each bucket is 8 bytes (head pointer + padding)
        int* bucketHead = (int*)((char*)thisPtr + 0x20 + bucketIndex * 8);
        int entity = *bucketHead;
        while (entity != 0) {
            // Entity fields at known offsets:
            float entityY = *(float*)(entity + 0x48);         // +0x48: vertical position
            // Compute absolute difference using integer trickery
            float yDiff = entityY - pos[1];
            unsigned int asInt = *(unsigned int*)&yDiff;       // Reinterpret as uint
            unsigned int absBits = asInt & g_uAbsMask;         // Clear sign bit
            float absDiff = *(float*)&absBits;                  // Back to float
            if (absDiff < g_fVerticalThreshold) {
                // Check flag at +0x8A: bit 0 must be 0 (entity active/enabled)
                if ((*(unsigned char*)(entity + 0x8A) & 1) == 0) {
                    // If no filter or filter returns 0 (accept)
                    if (filter == nullptr || filter->isValid(entity) == 0) {
                        return entity;
                    }
                }
            }
            entity = *(int*)(entity + 8);   // +0x08: next entity in same bucket (linked list)
        }
        probe++;
    }
    return 0;  // Not found
}