// FUNC_NAME: Trie::insert
// Address: 0x00953bc0
// Inserts a key into a trie structure with child chains per level. 
// The trie uses separate chaining at each bit position (depth level).
// Node layout: [key (4), unknown (4), childrenPtr (4)] = 12 bytes.
// Trie object layout: [root (4), maxDepth (4), pad1 (4), pad2 (4), nodeCount (4), pathArray (4)]

struct TrieNode {
    uint32_t key;          // +0x0
    uint32_t unknown;      // +0x4 (unused)
    TrieNode** children;   // +0x8 pointer to array of TrieNode* (size = maxDepth+1)
};

struct Trie {
    TrieNode* root;        // +0x0
    int32_t maxDepth;      // +0x4
    uint32_t pad1;         // +0x8
    uint32_t pad2;         // +0xC
    int32_t nodeCount;     // +0x10
    TrieNode** pathArray;  // +0x14 array of TrieNode* (size = maxDepth+1)
};

// External helpers (renamed from callees)
uint32_t getKeyLength(void);                       // FUN_00953200
TrieNode* allocateNode(void);                      // FUN_009c8e50 (12 bytes)
uint32_t* allocateChildrenBuffer(uint32_t size);  // FUN_009c8e80

void __thiscall Trie::insert(Trie* this, TrieNode** outResult, uint32_t* key) {
    int32_t depth = this->maxDepth;
    TrieNode* currentNode = this->root;

    do {
        if (depth < 0) {
            // Reached leaf level – check if key already exists as first child of current node
            TrieNode* child = *(currentNode->children); // children[0]
            if (child == nullptr || child->key != *key) {
                // Allocate new node and children array
                uint32_t keyLen = getKeyLength();
                int32_t curMaxDepth = this->maxDepth;
                if (curMaxDepth < (int32_t)keyLen) {
                    // Extend path array up to new length, filling with root pointers
                    while (++curMaxDepth <= (int32_t)keyLen) {
                        this->pathArray[curMaxDepth] = this->root;
                    }
                    this->maxDepth = keyLen;
                }

                TrieNode* newNode = allocateNode();
                if (newNode != nullptr) {
                    uint32_t bufSize = (keyLen + 1) * 4;
                    newNode->children = (TrieNode**)allocateChildrenBuffer(bufSize);
                }
                newNode->key = *key;

                // Insert new node by swapping children pointers along the path
                for (uint32_t i = 0; i <= keyLen; i++) {
                    TrieNode* pathNode = this->pathArray[i];
                    // Slot at depth i in pathNode's children array
                    TrieNode** slot = &(pathNode->children[i]);
                    newNode->children[i] = *slot; // adopt old child
                    *slot = newNode;              // point to new node
                }
                this->nodeCount++;
            }
            *outResult = currentNode;
            return;
        }

        // Follow the chain of nodes at current depth
        TrieNode** slot = &(currentNode->children[depth]);
        if (*slot != nullptr) {
            do {
                TrieNode* nextNode = *slot;
                if (*key <= nextNode->key)
                    break;
                slot = &(nextNode->children[depth]);
                currentNode = nextNode;
            } while (*slot != nullptr);
        }

        // Save current node in path array (at level = depth-1)
        this->pathArray[depth - 1] = currentNode;
        depth--;
    } while (true);
}