// FUNC_NAME: HierarchyIndexAssigner::assignIndices
void __thiscall HierarchyIndexAssigner::assignIndices(int this, int adjacencyList, int parentIndex, int key, int rootSet) {
    // this+0x2: current write index (short)
    // this+0x8: pointer to output buffer (array of 16-byte records)
    // rootSet+0x4: pointer to array of short root keys
    // rootSet+0x8: count of root keys
    // adjacencyList+0x8: count of int entries
    // adjacencyList+0xC: pointer to array of int keys

    int i;
    short* rootKeys;
    int* adjKeys;
    short localIndices[10];

    // Part 1: If key is in rootSet, write a new record and set parentIndex to the new index
    for (i = 0; i < *(int*)(rootSet + 8); i++) {
        rootKeys = *(short**)(rootSet + 4);
        if (rootKeys[i] == key) {
            int currentIdx = *(short*)(this + 2);
            // output buffer is an array of 16-byte entries at this+8
            short* outputRecord = (short*)(*(int*)(this + 8) + currentIdx * 0x10);
            outputRecord[6] = (short)parentIndex;  // offset +0xC
            outputRecord[7] = (short)key;          // offset +0xE
            parentIndex = currentIdx;
            *(short*)(this + 2) = currentIdx + 1;
            break;
        }
    }

    // Part 2: Find all indices in adjacencyList where the int = key
    int adjCount = *(int*)(adjacencyList + 8);
    adjKeys = *(int**)(adjacencyList + 0xC);
    int found = 0;
    for (int j = 0; j < adjCount; j++) {
        if (adjKeys[j] == key) {
            localIndices[found] = (short)j;
            found++;
            if (found > 9) break;
        }
    }

    // Recursively process each found index as the new key
    for (i = 0; i < found; i++) {
        assignIndices(this, adjacencyList, parentIndex, (int)localIndices[i], rootSet);
    }
}