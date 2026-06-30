// FUNC_NAME: RadixTree::insertNode
void __thiscall RadixTree::insertNode(RadixTree* thisPtr, RadixNode** outNode, uint* keyPtr)
{
    int bit;
    RadixNode* currentNode;
    RadixNode* newNode;
    uint maxBits;
    uint numBits;
    uint i;

    bit = thisPtr->bitDepth;
    currentNode = thisPtr->root;

    // Loop to traverse the radix tree from the highest bit downwards.
    do {
        if (bit < 0) {
            // No exact match found; need to insert a new node.
            // Follow parent/ancestor pointers stored in pathArray to reconstruct the tree.

            // The current node is the point where insertion should happen.
            // The path array holds nodes along the path, but during insertion we need to know
            // the maximum bit depth for the key (e.g., 32 bits).
            currentNode = (RadixNode*)currentNode->children[2]; // children is at offset 8 of RadixNode
            if ((currentNode == nullptr) || (currentNode->key != *keyPtr)) {
                // Create a new node and insert it.
                maxBits = getMaxBitDepth(); // returns the number of bits in the key (e.g., 32)
                numBits = thisPtr->bitDepth;
                if (numBits < maxBits) {
                    // Extend the path array to hold up to maxBits+1 entries.
                    while (numBits < maxBits) {
                        numBits++;
                        thisPtr->pathArray[numBits] = thisPtr->root;
                    }
                    thisPtr->bitDepth = maxBits;
                }

                // Allocate a new RadixNode (12 bytes).
                newNode = (RadixNode*)allocateMemory(0xc);
                currentNode = nullptr;
                if (newNode != nullptr) {
                    // Allocate the children array for this node.
                    uint arraySize = (maxBits + 1) * 4;
                    newNode->children = (RadixNode**)allocateAlignedMemory(arraySize);
                    currentNode = newNode;
                }

                // Set the key for the new node.
                currentNode->key = *keyPtr;

                // Copy the child pointer from each ancestor node (stored in pathArray)
                // into the new node's children array, and then update the ancestor's child
                // to point to the new node. This effectively inserts the new node into the tree.
                i = 0;
                do {
                    // Copy: new_node->children[i] = pathArray[i]->children[i]
                    currentNode->children[i] = thisPtr->pathArray[i]->children[i];
                    // Update ancestor: pathArray[i]->children[i] = new_node
                    thisPtr->pathArray[i]->children[i] = currentNode;
                    i++;
                } while (i <= maxBits);

                // Increment the count of nodes in the tree.
                thisPtr->count++;
            }

            // Return the node where the key is stored (either existing or newly inserted).
            *outNode = currentNode;
            return;
        }

        // Traverse the tree at the current bit level.
        // From the current node, get the child pointer for this bit.
        // The children array is indexed by bit.
        RadixNode** childSlot = &currentNode->children[bit];
        if (*childSlot != nullptr) {
            // Walk along this chain as long as the next node's key is greater than the search key.
            do {
                RadixNode* nextNode = *childSlot;
                if (*keyPtr <= nextNode->key) break;
                childSlot = &nextNode->children[bit];
                currentNode = nextNode;
            } while (*childSlot != nullptr);
        }

        // Record the current node in the path array at the current bit index.
        bit--;
        thisPtr->pathArray[bit + 1] = currentNode; // note: pathArray indices are 0-based, but the code stores at offset 4+iVar7*4 (since iVar7 decremented before store, but they store with iVar7+1 offset? Actually code: *(uint **)(param_1[5] + 4 + iVar7 * 4) = puVar6; where iVar7 has been decremented, so it stores at index iVar7 (now one less) but plus 4? Wait this is tricky.
        // Let's re-express more clearly:
        // In the original loop, before iVar7 decrement, they have iVar7 as current bit.
        // After the inner do-while they store with iVar7-1? Actually the store is after iVar7 = iVar7 + -1; so they store at (param_1[5] + 4 + (iVar7-1)*4)? No.
        // The code: iVar7 = iVar7 + -1; then *(uint **)(param_1[5] + 4 + iVar7 * 4) = puVar6; So storing at index iVar7 (new value) but with offset +4 bytes? That seems like a mistake in my reading.
        // Possibly the pathArray is an array of uint** (pointers to nodes) and the store is at index bit+1? 
        // The code uses param_1[5] as base, and offset 4 + iVar7*4. So it's storing at pathArray[bit+1] if iVar7 is the decremented bit? Let's set bit = iVar7 after decrement.
        // I'll assume pathArray[bit+1] is correct.
        // Actually better: We'll keep the original logic: after decrementing bit, we store currentNode at pathArray[bit]. But the code adds 4 to base? That 4 bytes might be alignment? Or the pathArray might store plus one offset.
        // To be faithful, I'll directly translate the assembly logic: pathArray[bit+1] (since 4 bytes indicates one more slot).
        // I'll use: thisPtr->pathArray[bit+1] = currentNode;
        // That matches the pattern of storing at offset 4 + bit*4.
    } while (true);
}