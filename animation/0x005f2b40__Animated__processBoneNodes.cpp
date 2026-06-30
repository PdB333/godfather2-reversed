// FUNC_NAME: Animated::processBoneNodes
uint __thiscall Animated::processBoneNodes(void* parent, void* this) {
    byte childCount;
    bool toggleFlag;
    uint result;
    int* nodePtrArrayEnd;
    int** nodePtrIter;

    // Capture incoming EAX (likely return value or status)
    result = (uint)(int)parent & 0xffffff00; // Mask off low byte? Possibly alignment or error code

    if (parent == nullptr || this == nullptr) {
        return result;
    }

    childCount = *(byte*)((int)this + 0x6f); // +0x6f: number of child bone nodes
    toggleFlag = false;
    nodePtrIter = (int**)((int)this + 0xc); // +0xc: array of pointers to child nodes
    nodePtrArrayEnd = (int*)((int)this + 0xc + childCount * 4);

    for (; nodePtrIter < nodePtrArrayEnd; nodePtrIter++) {
        int* childNode = *nodePtrIter;
        if (childNode == nullptr || childNode == 0) {
            continue;
        }

        // FUN_005dbc10: likely sets bone rotation/quaternion from parent transform
        // Parameters: (this+0x5c - some ID?), (double)parent->x, (double)this->someFloat, (double)parent->z, childNode->boneType)
        FUN_005dbc10(
            *(undefined4*)((int)this + 0x5c),          // +0x5c: bone set identifier?
            (double)*(float*)((int)parent + 0x3c),     // +0x3c: parent X position/rotation
            (double)*(float*)((int)this + 0x50),       // +0x50: own Y? (some float)
            (double)*(float*)((int)parent + 0x4c),     // +0x4c: parent Z position/rotation
            *(byte*)((int)childNode + 0x1c)            // +0x1c: bone type index or mapping
        );

        // Copy parent transform index to child node (maybe linkage)
        *(int*)((int)childNode + 0xc) = *(int*)((int)parent + 4); // +0x4: parent's transform ID?

        // Call to update internal state (likely marks node as processed)
        FUN_005f2680();

        // Toggle flag affects processing of child flags
        if (toggleFlag) {
            // Even-indexed nodes
            if ((*(byte*)((int)this + 0x6c) & 4) != 0 && 
                (*(ushort*)((int)childNode + 0x10) & 0x100) != 0) {
                *(ushort*)((int)childNode + 0x10) &= 0xfeff; // Clear bit 8 (0x100)
                *(byte*)((int)childNode + 0x1d) = 1;         // +0x1d: flag? set to 1
            }
        } else {
            // Odd-indexed nodes
            if ((*(byte*)((int)this + 0x6c) & 4) == 0 && 
                (*(ushort*)((int)childNode + 0x10) & 0x100) != 0) {
                *(ushort*)((int)childNode + 0x10) &= 0xfeff;
                *(byte*)((int)childNode + 0x1d) = 1;
            }
        }

        // Retrieve some object and register for update
        int temp = FUN_005f37b0();
        FUN_005f1400(temp);

        toggleFlag = !toggleFlag;
    }

    // Construct return value (likely an index or success indicator)
    result = CONCAT31((int3)((uint)nodePtrIter >> 8), 1);
    return result;
}