// FUNC_NAME: ContainsMatchingIndexedNode
// Address: 0x00586c00
// Role: Searches a list of indices (pIndexList) against a linked list owned by pListOwner (head at +0x124).
// For each index, walks that many nodes in the list and checks if the node matches matchParam via FUN_00586c90.
// Returns 1 if any match found, else 0.

int ContainsMatchingIndexedNode(int* pIndexList, void* pListOwner, int matchParam)
{
    int count = *pIndexList;                                  // +0x00: number of entries in index list
    int idx = 0;
    if (count > 0) {
        int offset = 0;
        do {
            int nodeIndex = *(int*)(pIndexList[1] + offset);  // +0x04: pointer to array of 12-byte entries, first int is index
            if ((pListOwner != 0) && (nodeIndex >= 0)) {
                // Walk the linked list owned by pListOwner (head at +0x124)
                int* currentNode = *(int**)((char*)pListOwner + 0x124);
                int steps = 0;
                if (nodeIndex > 0) {
                    do {
                        currentNode = *(int**)((char*)currentNode + 0x124);
                        if (currentNode == 0) goto nextEntry;
                        steps++;
                    } while (steps < nodeIndex);
                }
                if ((currentNode != 0) && (FUN_00586c90(currentNode, matchParam) != 0)) {
                    return 1;
                }
            }
nextEntry:
            idx++;
            offset += 0x0c;  // each entry is 12 bytes (three ints)
        } while (idx < count);
    }
    return 0;
}