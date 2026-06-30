// FUNC_NAME: BitwiseTrie::insert
undefined4* __thiscall BitwiseTrie::insert(undefined4* outNodePtr, uint key)
{
    // unaff_ESI = this
    int bitIdx = this->maxBitIndex;              // +0x04
    Node* currentNode = this->rootNode;          // +0x00

    do {
        if (bitIdx < 0) {
            // Reached leaf level: follow the "alternate" pointer (children[0]?)
            currentNode = (Node*)currentNode->children[0];   // +0x08 (children[0] is the next pointer in some contexts)
            if (currentNode != nullptr && currentNode->key == key) {
                *outNodePtr = currentNode;
                return outNodePtr;
            }

            // Insert new node
            uint newBitCount = getBitLength();                // FUN_00429f40: returns bit length of key? Or system max?
            uint curMaxIdx = this->maxBitIndex;               // +0x04
            if (curMaxIdx < newBitCount) {
                // Expand the path array (nodeStack) up to newBitCount
                while (++curMaxIdx <= newBitCount) {
                    this->nodeStack[curMaxIdx] = this->rootNode; // +0x14 (array of Node*)
                }
                this->maxBitIndex = newBitCount;              // +0x04
            }

            Node* newNode = (Node*)operatorNew(12);           // FUN_009c8e50(size 0xc)
            if (newNode != nullptr) {
                int arraySize = (newBitCount + 1) * 4;
                uint* childArray = (uint*)operatorNewArray(arraySize); // FUN_009c8e80
                newNode->children = childArray;               // +0x08
                currentNode = newNode;
            }
            currentNode->key = key;                           // +0x00

            // Copy child pointers from the predecessor stored in nodeStack
            for (uint i = 0; i <= newBitCount; i++) {
                // For each bit index, copy the child pointer from the predecessor's node at that index
                Node* pred = (Node*)this->nodeStack[i];               // +0x14+i*4
                uint* predChildren = pred->children;                  // +0x08
                currentNode->children[i] = predChildren[i];           // copy pointer from predecessor's child array
                // Update the predecessor's child array to point to the new node (for the current bit)
                predChildren[i] = (uint)currentNode;                  // update predecessor's child at that bit
            }

            this->nodeCount++;                              // +0x10
            *outNodePtr = currentNode;
            return outNodePtr;
        }

        // Navigate the trie at the current bit level
        uint** childSlot = (uint**)(currentNode->children + bitIdx);   // +0x08 + bitIdx*4
        if (*childSlot != nullptr) {
            uint* child = *childSlot;
            // Traverse along the child chain (binary search within this bit level?)
            while (true) {
                uint* nextChild = (uint*)*childSlot;
                if (key <= *nextChild) break;
                childSlot = (uint**)(nextChild[2] + bitIdx * 4);  // nextChild->children + bitIdx
                child = nextChild;
                if (*childSlot == nullptr) break;
            }
            currentNode = (Node*)child;   // update current node (actually the child we found)
        }

        bitIdx--;
        this->nodeStack[bitIdx] = currentNode;   // +0x14 (store current node for this bit)
    } while (true);
}