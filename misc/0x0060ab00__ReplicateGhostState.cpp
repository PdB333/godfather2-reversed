// FUNC_NAME: ReplicateGhostState
// Function address: 0x0060ab00
// Purpose: Compares and replicates a block of floats (ghost state) from a source buffer
// to either a local or remote state buffer, triggering a notification if changed.
// param_2: Combined ID and direction flag (high bit set = remote, clear = local).
// param_3: Source buffer pointer (cast to int).
// param_4: Number of floats to replicate.
// param_1: Unused in this function; passed through to the notification callback.

void ReplicateGhostState(uint param_1, uint stateId, int srcBuffer, int floatCount)
{
    float fVar1;
    bool bChanged;
    float *pfDest;
    float *pfSrc;
    int iProcessed;        // number of floats already processed in the main loop
    int iRemaining;
    uint uIndex;           // low byte of stateId, used as table index
    undefined *puDestBase; // pointer into the selected state table

    if (stateId == 0) {
        return;
    }

    uIndex = stateId & 0xff;
    bChanged = false;

    // Select the state buffer based on high bit of stateId
    // 0x011d97f0: local state table; 0x011ea8f0: remote state table
    if ((stateId & 0x80000000) == 0) {
        // Local state
        puDestBase = (undefined *)(0x011d97f0 + uIndex * 0x10);  // each entry is 16 bytes (4 floats)
    } else {
        // Remote state
        puDestBase = (undefined *)(0x011ea8f0 + uIndex * 0x10);
    }

    iProcessed = 0;

    // Process in blocks of 4 floats (16 bytes)
    if (3 < floatCount) {
        pfSrc = (float *)(srcBuffer + 0xc);  // source pointer initially offset by 3 floats? Actually +12 bytes = 3 floats, but then used with pfDest[-3].
                                              // This is an artifact of pointer arithmetic; effectively source starts 12 bytes ahead.
        iRemaining = (floatCount - 4U >> 2) + 1;  // number of full 4-float blocks (round down)
        pfDest = (float *)(puDestBase + 4);       // dest pointer offset by 1 float (4 bytes) to allow negative indexing
        iProcessed = iRemaining * 4;

        do {
            // Compare and copy 4 floats
            if (pfDest[-1] != pfSrc[-3]) {
                bChanged = true;
                pfDest[-1] = pfSrc[-3];
            }
            fVar1 = *(float *)((srcBuffer - (int)puDestBase) + (int)pfDest);  // source = srcBuffer + (pfDest - puDestBase)
            if (*pfDest != fVar1) {
                bChanged = true;
                *pfDest = fVar1;
            }
            if (pfDest[1] != pfSrc[-1]) {
                bChanged = true;
                pfDest[1] = pfSrc[-1];
            }
            if (pfDest[2] != *pfSrc) {
                bChanged = true;
                pfDest[2] = *pfSrc;
            }
            pfDest = pfDest + 4;  // advance by 4 floats (16 bytes)
            pfSrc = pfSrc + 4;
            iRemaining = iRemaining - 1;
        } while (iRemaining != 0);
    }

    // Process remaining floats (less than 4)
    if (iProcessed < floatCount) {
        pfDest = (float *)(puDestBase + iProcessed * 4);
        iRemaining = floatCount - iProcessed;
        do {
            fVar1 = *(float *)((int)pfDest + (srcBuffer - (int)puDestBase));
            if (*pfDest != fVar1) {
                bChanged = true;
                *pfDest = fVar1;
            }
            pfDest = pfDest + 1;
            iRemaining = iRemaining - 1;
        } while (iRemaining != 0);
    }

    // If any value changed, notify the network manager
    if (bChanged) {
        if ((stateId & 0x80000000) != 0) {
            // Remote update: call method at offset 0x178 on the global network manager
            (**(code **)(*(int *)0x01205750 + 0x178))();
            return;
        }
        // Local update: call method at offset 0x1b4 with state ID, buffer, and block count
        (**(code **)(*(int *)0x01205750 + 0x1b4))
            (0x01205750, uIndex, puDestBase, (floatCount + 3 + ((floatCount + 3) >> 0x1f & 3U)) >> 2);
    }
    return;
}