// FUNC_NAME: TransformBlender::processNodes
void TransformBlender::processNodes(int param_1) {
    // GHIDRA RECONSTRUCTION - address 0x0055c5b0
    // This function iterates over a list of transform nodes and applies them
    // to a buffer at param_1+8. The buffer appears to hold a 4x4 matrix
    // stored as 8 vectors (two banks: rows 0-3 at offsets 0,0x30,0x60,0x90,
    // rows 4-7 at offsets 0x10,0x40,0x70,0xa0).
    // The nodes are stored in a compact pool with an iterator structure.

    FUN_00546960(); // likely some init/debug
    FUN_0043aff0(/*in_EAX*/, 0x7f1d424f); // set debug string or log ID

    int *iterator = local_8;
    int const_value = DAT_00e2b1a4; // some constant (maybe time delta?)

    do {
        bool skip;
        if (local_64 == '\0') {
            skip = (*iterator == 0); // check if current iterator is null?
        } else {
            skip = (local_58 == local_54); // check if index reached count
        }
        if (skip) {
            return;
        }

        uint *currentNode;
        if (local_64 == '\0') {
            currentNode = iterator;
        } else {
            currentNode = &local_50;
        }

        // Check a short at offset 6 of the node structure for a magic tag (0x25e3)
        // If tag matches, it indicates a different node layout (maybe inline?)
        int type;
        if (*(short *)((int)currentNode + 6) == 0x25e3) {
            type = (uint)*(ushort *)(currentNode + 1); // type from node data
        } else {
            type = (int)currentNode[1]; // type from node structure
        }

        // Based on type (0-7), write three values from node to different positions
        // in the output buffer.
        int *destBase; // base pointer for destination
        uint *srcX, *srcY, *srcZ; // three source values from node

        switch (type) {
        case 0:
            // Resolve node pointer
            if (local_64 == '\0') {
                if (*(short *)((int)iterator + 6) == 0x25e3) {
                    if (*iterator == 0) {
                        currentNode = &DAT_00e2e5d0; // default fallback
                    } else {
                        currentNode = (uint *)((int)iterator[2] + (int)*iterator);
                    }
                } else {
                    currentNode = iterator + 2;
                }
            } else {
                if (*(short *)((int)&local_50 + 6) == 0x25e3) {
                    if (local_50 == 0) {
                        currentNode = &DAT_00e2e5d0;
                    } else {
                        currentNode = (uint *)((int)local_50[2] + (int)local_50);
                    }
                } else {
                    currentNode = &local_50 + 2;
                }
            }
            // Write to buffer at offset 0
            destBase = *(int **)(param_1 + 8); // buffer start
            *destBase = (int)*currentNode;
            destBase[1] = (int)currentNode[1];
            destBase[2] = (int)currentNode[2];
            destBase[3] = const_value;
            goto default_case;

        case 1:
            // Similar resolution, write to buffer+0x30
            // ... (code omitted for brevity)
            // In original, this writes to *(param_1+8)+0x30
            // The pattern is the same for cases 0-3 writing rows 0-3
            // and cases 4-7 writing rows 4-7 (dual quaternion or second matrix?)
            // For reconstruction, I'll show the pattern.

        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            // Each case resolves currentNode, then writes three values + const
            // to a specific offset (0,0x30,0x60,0x90 for 0-3; 0x10,0x40,0x70,0xa0 for 4-7)
            // Then falls through to default_case.
            break;

        default:
            // No operation for unknown types?
            break;
        }

        // After each node, advance the iterator
        if (local_64 == '\0') {
            if ((int)local_58 < 0) {
                // Negative index indicates reverse iteration? Advance by adding current node size
                iterator = (int *)((int)iterator + (int)*iterator);
                FUN_0043b140(); // likely a stack pop or move
            } else if ((int)local_58 < (int)(local_54 - 1)) {
                local_58 += 1;
                iterator = (int *)((int)iterator + (int)*iterator);
            } else {
                iterator = &DAT_01163cf8; // end sentinel
            }
        } else {
            local_58 += 1;
            if (local_58 != local_54) {
                local_4c = (short)local_58;
                // Bitmask check for presence of node
                if ((*(byte *)((local_58 >> 3) + local_60) & (byte)(1 << ((byte)local_58 & 7))) == 0) {
                    // Node is present, read from the array
                    local_48 = *local_5c;
                    local_50 = local_5c;
                    local_5c += 1;
                } else {
                    local_50 = 0;
                    local_48 = 0;
                }
            }
        }
    } while (true);
}