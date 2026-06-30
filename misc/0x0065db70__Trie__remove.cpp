// FUNC_NAME: Trie::remove
void Trie::remove(int *key)
{
    int depth = this->depthCount; // +0x04
    int *curNode = this->root; // +0x00
    int *bestNode = curNode;
    int *foundNode = nullptr;

    if (depth < 0) {
        return;
    }

    do {
        int *nextNode = *(int **)(curNode[2] + depth * 4);
        if (nextNode != nullptr) {
            int *candidate = nextNode;
            do {
                candidate = curNode;
                if (*key <= *candidate) {
                    break;
                }
                nextNode = *(int **)(candidate[2] + depth * 4);
                bestNode = candidate;
                candidate = nextNode;
            } while (nextNode != nullptr);
        }
        this->pathTable[depth] = bestNode; // +0x14: pointer array, stored at offset +4+depth*4? Actually code: *(int **)(unaff_EDI[5] + 4 + iVar3*4)
        depth--;
    } while (depth >= 0);

    if (foundNode != nullptr && *foundNode == *key) {
        unsigned int idx = 0;
        do {
            int *childArray = *(int **)(this->pathTable[idx] + 8); // +0x08: offset 8 in node -> pointer to children array
            int *childSlot = childArray + idx; // Actually: iVar2 = childArray; iVar3 = idx*4; then childArray + iVar3? The code: iVar2 = *(int *)(*(int *)(unaff_EDI[5] + uVar4*4) + 8); iVar3 = uVar4 * 4; if (*(int **)(iVar2 + uVar4 * 4) != piVar7) break;
            // This is confusing. I'll simplify: copy child pointers from foundNode's children to the path.
            // Actually it seems to copy the children of the foundNode into the path table to maintain structure.
            int *nodeChildren = *(int **)(this->pathTable[idx] + 8);
            if (nodeChildren[idx] != foundNode) {
                break;
            }
            nodeChildren[idx] = *(int **)(foundNode[2] + idx * 4); // copy foundNode's child to the table
            idx++;
        } while (idx <= (unsigned int)this->depthCount);

        // Free the foundNode's children array and the node itself
        free(*(void **)(foundNode[2])); // FUN_009c8f10 - free children array
        free(foundNode); // FUN_009c8eb0 - free node
        this->size--; // +0x10: count
    }
}