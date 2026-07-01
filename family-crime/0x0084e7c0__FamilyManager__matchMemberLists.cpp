// FUNC_NAME: FamilyManager::matchMemberLists
void __thiscall FamilyManager::matchMemberLists(int thisPtr, int* nodePairPtr) {
    // nodePairPtr structure:
    //   [0] = pointer to first linked list head
    //   [1] = pointer to second linked list head
    //   [4] = pointer to an array of 8 ints (data buffer)
    //   [8] = result flag (set to 1 on success)

    int lastNode1;
    int lastNode2;
    int allocId1 = 0;
    int allocId2 = 0;
    int derivedBase;
    int selectedNode1;
    int selectedNode2;
    int selectedAllocId;
    int dataBuffer[8]; // copied from nodePairPtr[4]
    int unknown1, unknown2; // from list heads offset 4 (IDs?)
    int nodeField; // byte at offset 0x18 of selected node

    // Traverse first linked list to find last node (next at +0xC)
    lastNode1 = *nodePairPtr; // head of list1
    for (int current = *(int*)(*nodePairPtr + 0xC); current != 0; current = *(int*)(current + 0xC)) {
        lastNode1 = current;
    }

    // Traverse second linked list
    lastNode2 = nodePairPtr[1]; // head of list2
    for (int current = *(int*)(nodePairPtr[1] + 0xC); current != 0; current = *(int*)(current + 0xC)) {
        lastNode2 = current;
    }

    // If lastNode1 has a non-zero byte at offset 0x10, allocate an ID (0x2001 pool)
    if (*(char*)(lastNode1 + 0x10) + lastNode1 != 0) { // originally: check byte + pointer != 0 (likely checks non-null node and byte)
        allocId1 = 0;
        int* tempBuffer = (int*)FUN_004af8c0((int*)0x0, 0x2001); // allocate from pool
        if (tempBuffer != 0) {
            allocId1 = *tempBuffer;
        }
    }

    // Similarly for lastNode2
    if (*(char*)(lastNode2 + 0x10) + lastNode2 != 0) {
        allocId2 = 0;
        int* tempBuffer = (int*)FUN_004af8c0((int*)0x0, 0x2001);
        if (tempBuffer != 0) {
            allocId2 = *tempBuffer;
        }
    }

    unknown1 = -1; // uninitialized as 0xFFFFFFFF
    unknown2 = -1;
    selectedAllocId = 0;

    // Derive base pointer from this->+4 (which points to an object with a header of 0x48 bytes)
    if (*(int*)(thisPtr + 4) == 0) {
        derivedBase = 0;
    } else {
        derivedBase = *(int*)(thisPtr + 4) - 0x48;
    }

    if (allocId1 == derivedBase) {
        // First list matches, use data from second list
        unknown2 = *(int*)(nodePairPtr[1] + 4); // ID from head of list2
        unknown1 = *(int*)(*nodePairPtr + 4);   // ID from head of list1
        selectedNode1 = lastNode1;
        selectedNode2 = lastNode2;
        selectedAllocId = allocId2;
    } else {
        // Recompute derivedBase (maybe it changed? same logic)
        if (*(int*)(thisPtr + 4) == 0) {
            derivedBase = 0;
        } else {
            derivedBase = *(int*)(thisPtr + 4) - 0x48;
        }

        selectedNode1 = 0;
        selectedNode2 = 0;
        if (allocId2 == derivedBase) {
            // Second list matches, use data from first list
            unknown2 = *(int*)(*nodePairPtr + 4);
            unknown1 = *(int*)(nodePairPtr[1] + 4);
            selectedNode1 = lastNode2;
            selectedNode2 = lastNode1;
            selectedAllocId = allocId1;
        }
    }

    // Copy the 8-int data buffer from nodePairPtr[4]
    int* dataSource = (int*)nodePairPtr[4];
    dataBuffer[0] = dataSource[0];
    dataBuffer[1] = dataSource[1];
    dataBuffer[2] = dataSource[2];
    dataBuffer[3] = dataSource[3];
    dataBuffer[4] = dataSource[4];
    dataBuffer[5] = dataSource[5];
    dataBuffer[6] = dataSource[6];
    dataBuffer[7] = dataSource[7];

    // Get the base object again for virtual call
    int* baseObj;
    if (*(int*)(thisPtr + 4) == 0) {
        baseObj = 0;
    } else {
        baseObj = (int*)(*(int*)(thisPtr + 4) - 0x48);
    }

    // Call virtual function at vtable offset 200 (entry 50)
    // Parameters: selectedAllocId, byte at selectedNode2+0x18, pointer to dataBuffer
    nodeField = *(char*)(selectedNode2 + 0x18);
    bool result = (*(code**)(*baseObj + 200))(selectedAllocId, nodeField, dataBuffer);

    if (result) {
        nodePairPtr[8] = 1; // Set success flag
    }
    return;
}