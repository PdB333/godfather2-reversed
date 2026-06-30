// FUNC_NAME: SpatialHash::findEntityAtPoint
// Address: 0x006e68b0
// This function searches the spatial hash for an entity near the given point. It uses a grid-based hash with neighbor cell offsets and a y-distance threshold.
// param_1: this pointer (SpatialHash instance)
// param_2: pointer to float[3] (x, y, z) query point
// param_3: optional filter function pointer (pointer to function that returns bool*, if null ignored)

int __thiscall SpatialHash::findEntityAtPoint(const float* point, bool (*filter)(int entity)) {
    // Compute grid cell from x and z coordinates (each grid cell is 8 units: shift right 3)
    int cellX = ((int)point[0] >> 3) & 0x1f;   // 5 bits for x within a chunk?
    int cellZ = ((int)point[2] >> 3) & 0x1f;   // 5 bits for z
    int cellIdx = cellZ * 0x20 + cellX;         // linear index within a 32x32 grid

    // Global table of neighbor cell offsets (2 bytes per entry: first byte = deltaX, second byte = deltaZ)
    extern unsigned char neighborOffsets[]; // DAT_0112a960 array of 2-byte entries

    unsigned char* offsetEntry = neighborOffsets;
    do {
        // Compute hash bucket index from cellIdx and neighbor offset
        int bucketIdx = (offsetEntry[1] * 0x20 + cellIdx) & 0x3e0; // &0x3e0 masks 5 bits for z (shifted)
        bucketIdx |= (offsetEntry[0] + cellIdx) & 0x1f;            // &0x1f masks 5 bits for x
        // Each bucket is a pointer to the head of a linked list; table starts at this+0x20, each entry 8 bytes
        // Actually we dereference an int* from the table, then use as Node*
        EntityNode* node = *(EntityNode**)((char*)this + 0x20 + bucketIdx * 8);

        while (node != nullptr) {
            // Check if y difference (absolute) is below threshold (using integer trick to mask sign bit)
            float yDiff = node->yPos - point[1];
            // Fast abs via integer masking (DAT_00e44680 is 0x7fffffff)
            if (*(uint32_t*)&yDiff & 0x7fffffff < *(float*)&yThreshold) // DAT_00d5eee4
            {
                // Check entity is not flagged (bit 0 of flags at +0x8a is clear)
                if ((node->flags & 1) == 0) {
                    // Apply optional filter callback (returns false to accept, true to reject)
                    if (filter == nullptr || filter((int)node) == false) {
                        return (int)node;
                    }
                }
            }
            // Move to next node in chain (next pointer at offset +8)
            node = (EntityNode*)(*(int*)((char*)node + 8));
        }
        // Move to next neighbor offset entry (2 bytes each)
        offsetEntry += 2;
        // If we've exceeded the table size, stop (table end address ~0x112A999)
    } while ((uintptr_t)offsetEntry <= 0x112A999);

    return 0;
}