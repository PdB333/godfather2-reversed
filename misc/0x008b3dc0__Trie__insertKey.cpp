// FUNC_NAME: Trie::insertKey
void __thiscall Trie::insertKey(uint* thisPtr, uint** outNode, uint* keyPtr)
{
    int bitPos = thisPtr[1]; // +0x04: current bit position (depth)
    uint* currentNode = (uint*)*thisPtr; // +0x00: root node

    do {
        if (bitPos < 0) {
            // Reached leaf level; check if key already exists
            currentNode = *(uint**)currentNode[5]; // +0x14: child array pointer
            if ((currentNode == nullptr) || (*currentNode != *keyPtr)) {
                // Key not found; insert new node
                uint depth = FUN_008b39e0(); // get current depth
                uint currentDepth = thisPtr[1]; // +0x04
                if (currentDepth < depth) {
                    // Expand child array if needed
                    while (currentDepth < depth) {
                        currentDepth++;
                        *(uint*)(thisPtr[5] + currentDepth * 4) = *thisPtr; // +0x14: store root? Actually this seems wrong but following decompiled logic
                    }
                    thisPtr[1] = depth;
                }

                // Allocate new node (0x18 bytes)
                uint* newNode = (uint*)FUN_009c8e50(0x18);
                currentNode = nullptr;
                if (newNode != nullptr) {
                    newNode[1] = 0; // +0x04: flag
                    uint childArraySize = (depth + 1) * 4;
                    uint* childArray = (uint*)FUN_009c8e80(childArraySize);
                    newNode[5] = (uint)childArray; // +0x14: child array pointer
                    currentNode = newNode;
                }
                *currentNode = *keyPtr; // +0x00: key

                // Update child pointers in existing nodes to point to new node
                uint idx = 0;
                do {
                    // Copy child pointer from existing node's child array to new node's child array
                    uint* existingNode = *(uint**)(thisPtr[5] + idx * 4); // +0x14: get node from array
                    uint* existingChildArray = *(uint**)(existingNode[5]); // +0x14: its child array
                    *(uint*)(currentNode[5] + idx * 4) = *(uint*)(existingChildArray + idx * 4);
                    // Update existing node's child pointer to point to new node
                    *(uint**)(existingChildArray + idx * 4) = currentNode;
                    idx++;
                } while (idx <= depth);

                thisPtr[4]++; // +0x10: increment node count
            }
            *outNode = currentNode;
            return;
        }

        // Traverse down the trie
        int* childPtr = (int*)(currentNode[5] + bitPos * 4); // +0x14: child array at bit position
        if (*(int*)(currentNode[5] + bitPos * 4) != 0) {
            do {
                uint* childNode = (uint*)*childPtr;
                if (*keyPtr <= *childNode) break;
                childPtr = (int*)(childNode[5] + bitPos * 4);
                currentNode = childNode;
            } while (*(int*)(childNode[5] + bitPos * 4) != 0);
        }
        bitPos--;
        *(uint**)(thisPtr[5] + 4 + bitPos * 4) = currentNode; // +0x14: store current node in array
    } while (true);
}