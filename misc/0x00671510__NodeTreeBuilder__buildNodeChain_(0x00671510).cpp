// FUNC_NAME: NodeTreeBuilder::buildNodeChain (0x00671510)
// Builds a chain of nodes from data tables, allocating and linking them.
// Returns pointer to last node or 0 on error. Outputs error code via outErrorCode.

int NodeTreeBuilder::buildNodeChain(ushort nodeIndex, int *outErrorCode) {
    int errorCode = 0;
    ushort originalNodeCount = 0;
    ushort minField6c = 0xffff;
    ushort maxField6e = 0;

    // Compute slot pointer from index (masked to 7 bits, stride 0x3c)
    int slotPtr = (int)this + (nodeIndex & 0x7f) * 0x3c;
    // Validate slot by stored ID
    if (*(ushort *)(slotPtr + 0x1e) != nodeIndex) {
        *outErrorCode = 0x4e23;
        return 0;
    }

    if (!FUN_00672320(this, &errorCode)) { // Some pre-check
        *outErrorCode = 0;
        int childListPtr = *(int *)(slotPtr + 0x30);
        if (childListPtr == 0) {
            childListPtr = 0;
        }
        // Look up node count from a data table
        int dataTableOffset = (uint)*(ushort *)(slotPtr + 0x1c) * 8;
        originalNodeCount = *(ushort *)(dataTableOffset + *(int *)((int)this + 0x14));
        int loopCounter = (short)originalNodeCount - 1;

        // Allocate three parallel arrays for node references
        int array1 = FUN_00673070(); // +0x4c
        int array2 = FUN_00673070(); // +0x50
        int array3 = FUN_00673070(); // +0x54
        *(int *)(slotPtr + 0x4c) = array1;
        *(int *)(slotPtr + 0x50) = array2;
        *(int *)(slotPtr + 0x54) = array3;
        *(short *)(slotPtr + 0x48) = 0; // count of processed nodes

        while (loopCounter >= 0 && errorCode == 0) {
            // Compute index into another data table
            int indexIntoTable = (uint)*(ushort *)(dataTableOffset + *(int *)((int)this + 0x14) + 4) + loopCounter * 2;
            int nodeId = *(ushort *)(indexIntoTable);
            int nodeTableOffset = nodeId * 0xc4;

            int field2 = (uint)*(ushort *)(*(int *)((int)this + 0xc) + nodeTableOffset + 2);
            int field0 = (uint)*(ushort *)(*(int *)((int)this + 0xc) + nodeTableOffset);
            int basePtr = field0 * 0xc + *(int *)((int)this + 4);

            int someStruct = *(int *)(basePtr + 4);
            int someValue = *(int *)(basePtr + 8);
            *(int *)(someStruct + 4) = *(int *)(someStruct + 0xc); // copy field

            int field20 = (uint)*(ushort *)(field0 * 0xc + *(int *)((int)this + 4));
            // Store a pointer from someStruct+0x14 into array3
            *(int *)(*(int *)(slotPtr + 0x54) + loopCounter * 4) = *(int *)(someStruct + 0x14);

            int nodeHandle = FUN_00675810(field20, field2, someStruct, someValue, childListPtr, &errorCode);
            *(int *)(*(int *)(slotPtr + 0x50) + loopCounter * 4) = nodeHandle;

            if (errorCode == 0) {
                int node = *(int *)(*(int *)(slotPtr + 0x50) + loopCounter * 4);
                if (*(ushort *)(node + 0x6c) < minField6c) {
                    minField6c = *(ushort *)(node + 0x6c);
                }
                if (maxField6e < *(ushort *)(node + 0x6e)) {
                    maxField6e = *(ushort *)(node + 0x6e);
                }
                *(int *)((int)this + 0x1e24) = node;

                int nodeData = FUN_00673280(node); // extract some data
                *(int *)(*(int *)(slotPtr + 0x4c) + loopCounter * 4) = nodeData;

                if (errorCode == 0) {
                    int nodeData2 = *(int *)(*(int *)(slotPtr + 0x4c) + loopCounter * 4);
                    *(int *)((int)this + 0x1e20) = nodeData2;
                    // Copy 16 bytes from slotPtr+0x20
                    long long vecA = *(long long *)(slotPtr + 0x20);
                    long long vecB = *(long long *)(slotPtr + 0x28);
                    FUN_006735d0(nodeData2, *(int *)((int)this + 0x1e34), &vecA);
                    if (errorCode == 0) {
                        *(ushort *)((int)this + 0x1e1c) = nodeIndex;
                        *(int *)(*(int *)((int)this + 0x1e20) + 0x38) = (int)this;
                        *(code **)(*(int *)((int)this + 0x1e20) + 0x3c) = &FUN_006711e0; // callback
                        *(short *)(*(int *)(*(int *)((int)this + 0x1e20) + 0x180) + 0x60) = *(short *)((int)this + 0x1e28);
                        *(short *)(*(int *)(*(int *)((int)this + 0x1e20) + 0x180) + 0x62) = *(short *)((int)this + 0x1e2a);
                        FUN_00674e10(); // finalize
                    }
                }
            }
            *(short *)(slotPtr + 0x48) = *(short *)(slotPtr + 0x48) + 1;
            loopCounter--;
        }
    }

    *outErrorCode = errorCode;
    if (errorCode == 0) {
        // Write min/max fields to the last node in array1
        int lastNodeIndex = (short)originalNodeCount * 4;
        int lastNode = *(int *)(*(int *)(slotPtr + 0x4c) + lastNodeIndex - 4);
        *(ushort *)(lastNode + 0x60) = minField6c;
        *(ushort *)(lastNode + 0x62) = maxField6e;
        int result = *(int *)(*(int *)(slotPtr + 0x4c) + lastNodeIndex - 4);
        *(int *)((int)this + 0x1e20) = result;
        return result;
    }
    return 0;
}