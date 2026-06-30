//FUNC_NAME: HierarchyBuilder::buildMapping
void __thiscall HierarchyBuilder::buildMapping(int source, int targetNode, short value, int id, int idList) {
    int i;
    short *psVar3;
    int *piVar4;
    int j;
    short childIndices[10];
    int count;

    // Step 1: If the id is present in the idList, store the (value, id) pair into source's buffer
    count = *(int *)(idList + 8);
    if (0 < count) {
        psVar3 = *(short **)(idList + 4);
        for (i = 0; i < count; i++) {
            if (*psVar3 == id) {
                // Write value and id into the next slot of source's buffer
                // Buffer layout: each entry is 0x10 bytes, with value at +0xc and id at +0xe
                *(short *)(*(int *)(source + 8) + (*(short *)(source + 2) * 0x10) + 0xc) = value;
                *(short *)(*(int *)(source + 8) + (*(short *)(source + 2) * 0x10) + 0xe) = (short)id;
                // Increment the slot counter
                *(short *)(source + 2) = *(short *)(source + 2) + 1;
                break;
            }
            psVar3++;
        }
    }

    // Step 2: Find all children of targetNode that have the same id
    count = *(int *)(targetNode + 8);
    j = 0;
    i = 0;
    if (0 < count) {
        piVar4 = *(int **)(targetNode + 0xc);
        for (i = 0; i < count; i++) {
            if (*piVar4 == id) {
                childIndices[j] = (short)i;
                j++;
                if (9 < j) break;
            }
            piVar4 += 4;
        }
    }

    // Step 3: Recursively process each matching child
    for (i = 0; i < j; i++) {
        // Recursive call: source becomes targetNode, targetNode becomes value, value becomes child index, idList remains
        buildMapping(targetNode, value, childIndices[i], idList);
    }
}