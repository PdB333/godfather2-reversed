// FUNC_NAME: PatriciaTrie::findOrInsertNode
int* PatriciaTrie::findOrInsertNode(int* thisPtr, int* outNode, int* key)
{
    int* currentNode; // piVar6
    int* childPtr; // piVar1
    int bitIndex; // iVar7
    int* pathArray; // from this+0x14 (this[5])
    int nodeCount; // this[4]
    int newDepth; // uVar3
    int* newNode; // piVar4

    // bitIndex starts at the current depth (highest bit index used)
    bitIndex = thisPtr[1]; // +0x04: current depth/bits
    currentNode = (int*)thisPtr[0]; // +0x00: root pointer

    do {
        if (bitIndex < 0) {
            // Reached a leaf node or end of bit traversal
            // Check if the node's key matches the search key
            currentNode = *(int**)(currentNode[2]); // +0x08: data pointer (actually a branch?)
            if ((currentNode != (int*)0x0) && (*currentNode == *key)) {
                *outNode = (int)currentNode;
                return outNode;
            }

            // Not found, need to insert
            // Get the new depth (maybe number of bits needed for key)
            newDepth = PatriciaTrie::computeBitDepth(); // FUN_0065dfe0
            int currentDepth = thisPtr[1]; // +0x04
            if (currentDepth < newDepth) {
                // Extend path array to accommodate new depth
                while (currentDepth = currentDepth + 1, currentDepth <= newDepth) {
                    // Fill path array entries with current root (or sentinel?)
                    *(int*)(thisPtr[5] + currentDepth * 4) = *thisPtr; // +0x14: pathArray
                }
                thisPtr[1] = newDepth; // update depth
            }

            // Allocate new node (12 bytes: key + pointer to children array)
            newNode = (int*)operatorNew(0xc);
            if (newNode != (int*)0x0) {
                // Allocate children array: (newDepth+1) * 4 bytes
                int childrenSize = (newDepth + 1) * 4;
                int childrenArray = (int)operatorNew(childrenSize);
                newNode[2] = childrenArray; // store children array pointer
            }
            newNode[0] = *key; // store key in node
            int i = 0;
            do {
                // Copy children from the path node (the node we would have taken if existing)
                int pathNodeIndex = thisPtr[5] + i * 4;
                int pathNodePtr = *(int*)(pathNodeIndex);
                int pathNodeDataPtr = *(int*)(pathNodePtr + 8); // +0x08: children array
                int childValue = *(int*)(pathNodeDataPtr + i * 4);
                // Store the child value in new node's children array
                *(int*)(newNode[2] + i * 4) = childValue;
                // Update the path node's child pointer to point to new node
                *(int*)(pathNodeDataPtr + i * 4) = (int)newNode;
                i = i + 1;
            } while (i <= newDepth);

            thisPtr[4] = thisPtr[4] + 1; // increment node count
            *outNode = (int)newNode;
            return outNode;
        }

        // Traverse the trie based on current bit
        int* childSlot = (int*)(currentNode[2] + bitIndex * 4); // +0x08: children array indexed by bit
        if (*childSlot != 0) {
            do {
                childPtr = (int*)*childSlot;
                if (*key <= *childPtr) break;
                // Move to the next child (probably linked list within same bit index slot)
                childSlot = (int*)(childPtr[2] + bitIndex * 4);
                currentNode = childPtr;
            } while (*(int*)(childPtr[2] + bitIndex * 4) != 0);
        }
        bitIndex = bitIndex - 1;
        // Store current node in path array
        *(int*)(thisPtr[5] + 4 + bitIndex * 4) = (int)currentNode; // +0x14: pathArray[bitIndex+1]?
    } while (true);
}