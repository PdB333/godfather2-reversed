// FUNC_NAME: SortedTrie::insertOrFind
void __thiscall SortedTrie::insertOrFind(uint *keyPtr, TrieNode **outNode)
{
    int depth = this->m_nDepth;               // param_1[1]
    TrieNode *current = this->m_pRoot;        // param_1[0]

    do {
        if (depth < 0) {
            // No more bits – insert new node
            current = (TrieNode *)*current->pNextLevel; // walk one more step?
            if ((current == NULL) || (current->key != *keyPtr)) {
                uint maxDepth = getMaxDepth();           // FUN_006a76b0
                uint currentDepth = this->m_nDepth;       // param_1[1]
                if (currentDepth < maxDepth) {
                    // Extend spine array to new maxDepth
                    for (uint i = currentDepth + 1; i <= maxDepth; i++) {
                        this->m_pSpine[i] = this->m_pRoot;
                    }
                    this->m_nDepth = maxDepth;
                }

                // Allocate new node (12 bytes)
                TrieNode *newNode = allocateNode();       // FUN_009c8e50 (size 0xC)
                if (newNode != NULL) {
                    // Allocate children array for the node (size = (maxDepth+1)*4)
                    uint arraySize = (maxDepth + 1) * 4;
                    newNode->pChildren = (uint *)allocateArray(arraySize); // FUN_009c8e80
                }

                newNode->key = *keyPtr;

                // Copy children pointers from the last node in the spine to new node
                for (uint i = 0; i <= maxDepth; i++) {
                    TrieNode *spineNode = this->m_pSpine[i];
                    newNode->pChildren[i] = spineNode->pChildren[i];  // copy child pointer
                    // Update the original child pointer to point to new node
                    spineNode->pChildren[i] = (uint)newNode;          // ??? overwrite original?
                }

                this->m_nSize++;
            }
            *outNode = current;
            return;
        }

        // Traverse the linked list at current depth
        uint **childSlot = (uint **)(current->pChildren + depth);  // pointer to child pointer
        if (*childSlot != NULL) {
            do {
                TrieNode *next = (TrieNode *)*childSlot;
                if (*keyPtr <= next->key)
                    break;
                childSlot = (uint **)(next->pChildren + depth);
                current = next;
            } while (*childSlot != NULL);
        }

        depth--;
        this->m_pSpine[4 + depth] = current; // store current node in spine array (offset 4? or index?)
    } while (true);
}