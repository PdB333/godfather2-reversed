// FUNC_NAME: RadixTree::insert

// Reconstructed implementation of a radix tree insertion (bitwise trie).
// The tree uses a node structure with a key, a count, and a variable-size child pointer table.
// The tree header contains root, current depth (bit count), node count, and a path buffer.

// Node structure (sizeof=0xC)
struct RadixTreeNode {
    int key;                    // +0x00
    int childCount;             // +0x04? (unused in this function)
    int* children;              // +0x08 – pointer to an array of child pointers indexed by bit position
};

// Tree structure
struct RadixTree {
    RadixTreeNode* root;        // +0x00
    int bitDepth;               // +0x04 – number of bits currently used (highest bit index + 1)
    int pad;                    // +0x08
    int nodeCount;              // +0x0C – incremented on each insertion
    int* pathBuffer;            // +0x10 – buffer for path nodes (size = bitDepth+1)
    int field_0x14;
    int field_0x18;
};

void __thiscall RadixTree::insert(RadixTree* thisTree, RadixTreeNode** outNode, int* newKeyPtr) {
    int bitIndex;
    RadixTreeNode* currentNode;
    RadixTreeNode* nextNode;
    RadixTreeNode* newNode;
    int newKey;
    int numNodes;
    long long allocSize;
    int* childPtr;
    uint uVar3;
    uint uVar5;
    int* tempPtr;

    newKey = *newKeyPtr;
    currentNode = thisTree->root;            // start from root
    bitIndex = thisTree->bitDepth;           // work from highest bit downward

    do {
        if (bitIndex < 0) {
            // All bits processed, need to insert new node if key not found
            // First, try to go to the leaf chain under current node at bitIndex = -1
            if (currentNode != (RadixTreeNode*)0x0 && currentNode->children != (int*)0x0) {
                childPtr = (int*)(currentNode->children + (-1)); // ??? weird, but decompiled shows piVar6[2] + iVar7*4 with iVar7 = -1 -> pointer before array
                // Actually the decompiled code used piVar6 = *(int**)piVar6[2]; so child pointer at -1? That doesn't make sense.
            }
            // If node not found, do insertion
            uVar3 = FUN_008a39c0();  // probably returns current maximum bit depth needed for key
            uVar5 = thisTree->bitDepth;
            if (uVar5 < uVar3) {
                // Expand path buffer to accommodate extra bits
                while (uVar5 = uVar5 + 1, uVar5 <= uVar3) {
                    *(thisTree->pathBuffer + uVar5) = (int)thisTree->root; // store root as placeholder
                }
                thisTree->bitDepth = uVar3;   // update depth
            }

            // Allocate new node (12 bytes)
            newNode = (RadixTreeNode*)FUN_009c8e50(0xC);
            if (newNode != (RadixTreeNode*)0x0) {
                // Allocate child pointer table for (uVar3+1) entries
                allocSize = (uVar3 + 1) * 4;   // size in bytes
                newNode->children = (int*)FUN_009c8e80(allocSize); // allocate memory
                currentNode = newNode;         // set output
            }
            newNode->key = newKey;            // store key

            // Rebuild child pointers along the path
            uVar5 = 0;
            do {
                // Copy child pointer from the saved path node's children table
                *(int*)(newNode->children + uVar5 * 4) =
                    *(int*)(*(int*)(thisTree->pathBuffer[uVar5 * 4] + 8) + uVar5 * 4);
                // Update the old parent's child pointer to point to new node
                *(int**)(*(int*)(thisTree->pathBuffer[uVar5 * 4] + 8) + uVar5 * 4) = newNode;
                uVar5 = uVar5 + 1;
            } while (uVar5 <= uVar3);

            thisTree->nodeCount = thisTree->nodeCount + 1;  // increment node count
        } else {
            // Traverse using current bit index
            childPtr = currentNode->children + bitIndex * 4; // pointer to child pointer for this bit
            if (*childPtr != 0) {
                do {
                    nextNode = (RadixTreeNode*)*childPtr;
                    if (newKey <= nextNode->key) break;  // found correct sorted position
                    // Move to next sibling in chain
                    childPtr = nextNode->children + bitIndex * 4;
                    currentNode = nextNode;
                } while (*(nextNode->children + bitIndex * 4) != 0);
            }
            // Save current node in path buffer
            *(thisTree->pathBuffer + (bitIndex + 4)) = currentNode; // index adjusted? decompiled had param_1[5] + 4 + iVar7*4
        }

        bitIndex = bitIndex - 1;
    } while (true); // infinite loop, but exits via return when insertion was needed
}