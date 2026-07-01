// FUNC_NAME: EARS::RadixTree::insertNode
// Address: 0x008ab7d0
// Inserts a 32-bit key into a radix tree (PATRICIA trie). The tree stores keys in nodes and provides node-pointer lookup.
// param_1 = this (RadixTree*), param_2 = output (Node**), param_3 = key (uint32_t*)

struct RadixTreeNode {
    uint32_t key;           // +0x00
    uint32_t padding;       // +0x04
    RadixTreeNode** children; // +0x08 pointer to array of child pointers (indexed by bit depth)
};

struct RadixTree {
    RadixTreeNode* root;        // +0x00
    int32_t maxDepth;           // +0x04 current maximum number of bits used
    int32_t nodeCount;          // +0x10 (param_1[4])
    RadixTreeNode** path;       // +0x14 (param_1[5]) array of nodes at each depth from root (size maxDepth+1)
};

// Internal allocation helpers
extern void* operator new(size_t size);       // FUN_009c8e50
extern void* operator new[](size_t size);     // FUN_009c8e80
extern int32_t getRequiredBitCount();         // FUN_008a8780 - returns number of bits needed for the current key (likely based on key value)

void __thiscall RadixTree::insertNode(RadixTree* this_, RadixTreeNode** outNode, uint32_t* keyPtr) {
    int32_t depth = this_->maxDepth;
    RadixTreeNode* currentNode = this_->root;
    uint32_t key = *keyPtr;

    // Traverse tree bits from most significant to least significant
    while (depth >= 0) {
        // Get the child pointer at current bit position
        RadixTreeNode** childSlot = &currentNode->children[depth];
        RadixTreeNode* nextNode = *childSlot;

        // Follow the chain of nodes that have the same prefix at this depth
        while (nextNode != nullptr) {
            if (key <= nextNode->key) {
                break;
            }
            childSlot = &nextNode->children[depth];
            nextNode = *childSlot;
            currentNode = nextNode;
        }
        // Save the current node in the path array (index = depth + 1)
        this_->path[depth + 1] = currentNode;
        depth--;
    }

    // Reached leaf (depth < 0)
    // Check if current node's key matches the input key
    if (depth < 0) {
        // Move to the child pointed by children[some?] - actually it's a leaf: use children[2] as next node pointer?
        // The following is the original code's behavior at depth < 0.
        currentNode = (RadixTreeNode*)*currentNode->children[2]; // GET_LEAF_CHILD
        if (currentNode == nullptr || currentNode->key != key) {
            // Key not found, needs insertion
            int32_t newDepth = getRequiredBitCount(); // returns needed depth for this key (e.g., floor(log2(key))? or highest differing bit?)
            int32_t currentMaxDepth = this_->maxDepth;
            if (currentMaxDepth < newDepth) {
                // Expand the path array to accommodate the new depth
                while (currentMaxDepth < newDepth) {
                    currentMaxDepth++;
                    this_->path[currentMaxDepth] = this_->root;
                }
                this_->maxDepth = newDepth;
            }

            // Allocate a new node and its children array
            RadixTreeNode* newNode = (RadixTreeNode*)operator new(sizeof(RadixTreeNode)); // size 0xc = 12 bytes
            if (newNode != nullptr) {
                uint32_t arraySize = (newDepth + 1) * 4; // each entry is a pointer (4 bytes)
                newNode->children = (RadixTreeNode**)operator new[](arraySize);
                newNode->key = key;
                // Copy children from the path nodes? Actually copy the child pointers from the leaf node's children into the new node's children
                // The loop copies from the existing node's children (from path) to newNode's children, then updates the existing children to point to newNode.
                for (int32_t i = 0; i <= newDepth; i++) {
                    RadixTreeNode* pathNode = this_->path[i];
                    newNode->children[i] = pathNode->children[i]; // copy child from path node
                    pathNode->children[i] = newNode;              // redirect child to new node
                }
                this_->nodeCount++;
            }
            // Set output to the new node (or existing leaf if key matched)
            currentNode = newNode;
        }
        *outNode = currentNode;
    }
}