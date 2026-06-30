// FUNC_NAME: AnimationSystem::evaluateBlendTree
// Function at 0x006711e0: Selects and activates a node from an animation blend tree.
// Handles both random selection and weighted selection based on flags.
// Updates current node pointer and calls FUN_00674d40 to process the animation.

// The object structure (this) contains an array of slots (0x3c bytes each) at offset 0.
// Each slot has: +0x1e = short id, +0x48 = short count, +0x4c = pointer to array of node pointers,
// +0x50 = pointer to array of weight/data pointers.
// The node structure at +0x20..+0x4c, +0x60, +0x62 holds transform data, +0xbc holds weight for weighted selection.

// Parameters:
// this - pointer to AnimationSystem object
// animSlotId - index into the slot array (masked to 0x7f)
// sourceData - pointer to source data to copy into selected node
// selectionValue - used for weighted selection (cumulative target)
// processParamA, processParamB - passed to FUN_00674d40
// processParamC - unused
// flags - bit 3 enables weighted selection (otherwise random)
// outStatus - returns status code (0 if ok, 0x4e23 if invalid slot)

void AnimationSystem::evaluateBlendTree(
    void* this,
    uint animSlotId,
    int* sourceData,
    int selectionValue,
    undefined4 processParamA,
    undefined4 processParamB,
    undefined4 processParamC,
    uint flags,
    int* outStatus)
{
    int i;
    int cumulativeWeight;
    short randomResult;
    int scannedIndex;
    uint currentIndex;
    bool selectionFound = false;

    int slotBase = (int)this + (animSlotId & 0x7f) * 0x3c;
    // Verify slot ID matches stored ID
    if (*(short*)((int)this + 0x1e + (animSlotId & 0x7f) * 0x3c) != (short)animSlotId) {
        *outStatus = 0x4e23; // Invalid slot
        return;
    }

    // Get count of nodes in this slot (minus 1 for zero-based indexing)
    currentIndex = (uint)(ushort)(*(short*)(slotBase + 0x48) - 1);
    // Set current node pointer from the last entry in the array
    *(undefined4*)((int)this + 0x1e20) = *(undefined4*)(*(int*)(slotBase + 0x4c) + currentIndex * 4);

    bool weightedSelection = (flags & 8) != 0;
    if (!weightedSelection || *(short*)(slotBase + 0x48) < 2) {
        // Random selection from available nodes (or single node)
        while (true) {
            int nodePtrIndex = (currentIndex & 0xffff) * 4;
            // Overwrite current node with the one at currentIndex
            *(undefined4*)((int)this + 0x1e20) = *(undefined4*)(*(int*)(slotBase + 0x4c) + nodePtrIndex);
            int dataPtr = *(int*)(*(int*)(slotBase + 0x50) + nodePtrIndex);
            *(int*)((int)this + 0x1e24) = dataPtr;

            if (*(int*)((int)this + 0x1e20) == 0 || dataPtr == 0) {
                goto LAB_006714ea;
            }

            // Copy source data into the selected node (8 dwords + 2 shorts)
            *(undefined4*)(*(int*)((int)this + 0x1e20) + 0x20) = *(undefined4*)(*sourceData + 0x20);
            *(undefined4*)(*(int*)((int)this + 0x1e20) + 0x24) = *(undefined4*)(*sourceData + 0x24);
            *(undefined4*)(*(int*)((int)this + 0x1e20) + 0x40) = *(undefined4*)(*sourceData + 0x40);
            *(undefined4*)(*(int*)((int)this + 0x1e20) + 0x44) = *(undefined4*)(*sourceData + 0x44);
            *(undefined4*)(*(int*)((int)this + 0x1e20) + 0x48) = *(undefined4*)(*sourceData + 0x48);
            *(undefined4*)(*(int*)((int)this + 0x1e20) + 0x4c) = *(undefined4*)(*sourceData + 0x4c);
            *(undefined2*)(*(int*)((int)this + 0x1e20) + 0x60) = *(undefined2*)(*sourceData + 0x60);
            *(undefined2*)(*(int*)((int)this + 0x1e20) + 0x62) = *(undefined2*)(*sourceData + 0x62);

            if ((short)weightedSelection == 0) {
                randomResult = FUN_00675740(); // Get random value
            } else {
                randomResult = (short)selectionValue;
            }

            if (randomResult != 0 || (short)currentIndex == 0) {
                FUN_00674d40(selectionValue, processParamA, processParamB, &selectionFound);
            }

            if (randomResult != 0 || (short)currentIndex == 0) break;

            if (selectionFound) {
                goto LAB_006714cf;
            }
            currentIndex = currentIndex + 0xffff; // Decrement (wraps to 0xffff)
        }

        if (selectionFound) {
LAB_006714cf:
            int clearedIndex = (currentIndex & 0xffff) * 4;
            *(undefined4*)(*(int*)(slotBase + 0x4c) + clearedIndex) = 0;
            *(undefined4*)(*(int*)(slotBase + 0x50) + clearedIndex) = 0;
        }
    } else {
        // Weighted selection: accumulate weights until passing selectionValue
        int index = 0;
        cumulativeWeight = 0;
        while (true) {
            currentIndex = index & 0xffff;
            *(undefined4*)((int)this + 0x1e20) = *(undefined4*)(*(int*)(slotBase + 0x4c) + currentIndex * 4);
            int dataPtr2 = *(int*)(*(int*)(slotBase + 0x50) + currentIndex * 4);
            *(int*)((int)this + 0x1e24) = dataPtr2;

            cumulativeWeight = cumulativeWeight + *(int*)(dataPtr2 + 0xbc); // Add weight from data structure
            if (selectionValue < cumulativeWeight) break;

            if (*(short*)(slotBase + 0x48) - 1 <= (int)currentIndex) {
                // Exhausted all nodes; use source data as fallback
                *(int*)((int)this + 0x1e20) = *sourceData;
                FUN_00674d40(0, processParamA, processParamB, &selectionFound);
                goto LAB_006714ea;
            }
            index++;
            // cumulativeWeight already updated
        }

        // Copy source data into selected node (same as random path)
        *(undefined4*)(*(int*)((int)this + 0x1e20) + 0x20) = *(undefined4*)(*sourceData + 0x20);
        *(undefined4*)(*(int*)((int)this + 0x1e20) + 0x24) = *(undefined4*)(*sourceData + 0x24);
        *(undefined4*)(*(int*)((int)this + 0x1e20) + 0x40) = *(undefined4*)(*sourceData + 0x40);
        *(undefined4*)(*(int*)((int)this + 0x1e20) + 0x44) = *(undefined4*)(*sourceData + 0x44);
        *(undefined4*)(*(int*)((int)this + 0x1e20) + 0x48) = *(undefined4*)(*sourceData + 0x48);
        *(undefined4*)(*(int*)((int)this + 0x1e20) + 0x4c) = *(undefined4*)(*sourceData + 0x4c);
        *(undefined2*)(*(int*)((int)this + 0x1e20) + 0x60) = *(undefined2*)(*sourceData + 0x60);
        *(undefined2*)(*(int*)((int)this + 0x1e20) + 0x62) = *(undefined2*)(*sourceData + 0x62);

        FUN_00674d40(selectionValue - cumulativeWeight, processParamA, processParamB, &selectionFound);
    }

LAB_006714ea:
    *sourceData = *(int*)((int)this + 0x1e20); // Output selected node pointer via sourceData
    *outStatus = selectionFound ? 1 : 0; // Assuming selectionFound is boolean; adjust as needed
    return;
}