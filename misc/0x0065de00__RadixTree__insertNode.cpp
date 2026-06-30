// FUNC_NAME: RadixTree::insertNode
// Function at 0x0065de00: insert a key into a radix tree (Patricia trie). 
// The tree uses integer keys. Nodes are 12 bytes: key (int), unused (int), children array pointer (int*).
// The children array is allocated separately and contains pointers to child nodes indexed by bit positions.
// The tree's depth is stored in the object at offset +0x04.
// A path array (offset +0x14) stores the nodes visited during traversal for insertion/fixup.

struct RadixNode {
    int key;            // +0x00
    int _pad;           // +0x04
    int* children;      // +0x08 (pointer to array of child node pointers)
};

class RadixTree {
public:
    RadixNode* root;        // +0x00
    int depth;              // +0x04 (current highest bit level)
    int nodeCount;          // +0x10 (offset 4 ints? Actually offset +0x10)
    RadixNode** pathArray;  // +0x14 (offset 5 ints? Actually offset +0x14)
    // ... other fields likely exist but not used here

    // returns the node pointer in *outNode
    int* insertNode(int** outNode, const int* keyPtr);
};

// external: compute highest differing bit between two keys
extern int computeNewDepth(int key1, int key2);  // FUN_0065dfe0
extern void* operator_new(size_t size);          // FUN_009c8e50 (allocates node)
extern void* operator_new_array(size_t size);    // FUN_009c8e80 (allocates children array)

int* RadixTree::insertNode(int** outNode, const int* keyPtr) {
    int currentDepth = this->depth;
    RadixNode* currentNode = this->root;  // +0x00

    // Traverse the tree according to bits of the key, from high to low
    while (true) {
        if (currentDepth < 0) {
            // Reached bottom: follow the linked list (first child of the node) to find matching key
            currentNode = (RadixNode*)*(currentNode->children); // treat children[0] as linked list head
            if (currentNode != nullptr && currentNode->key == *keyPtr) {
                *outNode = currentNode;
                return outNode;
            }

            // Key not found: compute the highest bit where the key differs from existing keys
            int newDepth = computeNewDepth(*keyPtr, currentNode ? currentNode->key : 0);
            int oldDepth = this->depth;
            // Expand the path array to new depth if necessary
            if (oldDepth < newDepth) {
                while (oldDepth + 1 <= newDepth) {
                    this->pathArray[oldDepth + 1] = (RadixNode*)this->root;
                    ++oldDepth;
                }
                this->depth = newDepth;
            }

            // Allocate a new node (12 bytes)
            RadixNode* newNode = (RadixNode*)operator_new(0xc);
            if (newNode == nullptr) {
                // allocation failure (should not happen)
                *outNode = nullptr;
                return outNode;
            }
            // Allocate children array for the new node (size = (newDepth+1) * 4)
            newNode->children = (int*)operator_new_array((uint)(newDepth + 1) * 4);
            newNode->key = *keyPtr;
            // Initialize children array: copy child pointers from the old path nodes, and update old nodes to point to new node
            for (int idx = 0; idx <= newDepth; ++idx) {
                // Source: child pointer at pathArray[idx]'s children array + idx
                RadixNode* pathNode = this->pathArray[idx];
                newNode->children[idx] = pathNode->children[idx];  // copy child pointer
                // Update the old node's child pointer to point to the new node
                pathNode->children[idx] = (int)newNode;
            }
            this->nodeCount++;
            *outNode = newNode;
            return outNode;
        }

        // Current depth >= 0: traverse using the bit at currentDepth
        int* childArray = currentNode->children;  // pointer to child pointers array
        RadixNode* nextNode = (RadixNode*)childArray[currentDepth];
        if (nextNode != nullptr) {
            // Walk down the linked list at this bit position until key order is correct
            while (true) {
                RadixNode* current = nextNode;
                if (*keyPtr <= current->key) break;
                nextNode = (RadixNode*)current->children[currentDepth];
                currentNode = current;
                if (nextNode == nullptr) break;
            }
        }
        // Save the current node to the path array for insertion fixup
        this->pathArray[currentDepth] = currentNode;
        // Move to next bit (decrease depth)
        currentDepth--;
    }
}