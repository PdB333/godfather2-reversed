// FUNC_NAME: Animated::applyBoneDelta
// Function address: 0x00892600
// Applies a compressed delta (animation frame) to a bone array.
// param_1 (this) - pointer to float array of size 11 floats (44 bytes), representing bone state.
// param_2 - pointer to delta buffer: first uint = number of float groups, followed by float data.
// param_3 - threshold: if < 9, uses index remapping (bone permutation); else copies directly.
// Returns number of bytes consumed from delta buffer.

int __thiscall Animated::applyBoneDelta(float* this, uint* deltaBuffer, uint elementThreshold)
{
    uint numGroups = *deltaBuffer;                 // Number of float groups (4 floats per group in remap mode)
    float* srcFloats = (float*)(deltaBuffer + 1); // Float data after the count
    uint processedGroups = 0;                      // Tracks number of floats processed

    // Remap mode: when threshold < 9, apply delta using a static index mapping table.
    if (elementThreshold < 9) {
        if (numGroups > 3) {
            int loopCount = ((numGroups - 4) >> 2) + 1; // Process in blocks of 4 groups
            int* remapTable = &DAT_00e542d4;            // Static remapping table (pairs of ints)
            processedGroups = loopCount * 4;

            do {
                // Each iteration processes 4 groups (4 floats from source, 4 indices to add to)
                int idx;

                idx = remapTable[-2];  // Index for first float
                if (idx >= 0) this[idx] += srcFloats[0];

                idx = remapTable[0];   // Index for second float
                if (idx >= 0) this[idx] += srcFloats[1];

                idx = remapTable[2];   // Index for third float
                if (idx >= 0) this[idx] += srcFloats[2];

                idx = remapTable[4];   // Index for fourth float
                if (idx >= 0) this[idx] += srcFloats[3];

                srcFloats += 4;
                remapTable += 8;       // Skip 2 ints per group? Actually 8 ints because pairs for 4 groups? (4 groups × 2 ints = 8)
                loopCount--;
            } while (loopCount != 0);
        }

        // Process remaining groups individually (less than 4 in last block)
        if (processedGroups < numGroups) {
            int remaining = numGroups - processedGroups;
            int* singleRemapTable = &DAT_00e542cc + processedGroups * 2;
            processedGroups += remaining;

            do {
                int idx = *singleRemapTable;
                if (idx >= 0) this[idx] += *srcFloats;

                srcFloats++;
                singleRemapTable += 2;
                remaining--;
            } while (remaining != 0);
        }
    }
    // Direct copy mode: when threshold >= 9, copy floats directly (no remap)
    else {
        if (numGroups > 3) {
            int loopCount = ((numGroups - 4) >> 2) + 1;
            processedGroups = loopCount * 4;
            float* dest = this + 2;      // Write to offset 8 (2 floats from start)
            float* src = srcFloats;

            do {
                // Copy 4 floats from source to destination (dest -2 to dest+1)
                dest[-2] = src[0];
                dest[-1] = src[1];
                dest[0]  = src[2];
                dest[1]  = src[3];

                src += 4;
                dest += 4;
                loopCount--;
            } while (loopCount != 0);
        }

        // Copy remaining floats one by one
        while (processedGroups < numGroups) {
            processedGroups++;
            this[processedGroups - 1] = *srcFloats;  // Note: writes to this[processedGroups-1] (since starting at 0)
            srcFloats++;
        }
    }

    // Zero out any uninitialized floats up to index 10 (0xB total)
    if (processedGroups < 11) {
        float* clearStart = this + processedGroups;
        int clearCount = 11 - processedGroups;
        do {
            *clearStart = 0.0f;
            clearStart++;
            clearCount--;
        } while (clearCount != 0);
    }

    // Return number of bytes consumed from delta buffer
    return (int)srcFloats - (int)deltaBuffer;
}