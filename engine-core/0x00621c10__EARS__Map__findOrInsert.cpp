// FUNC_NAME: EARS::Map::findOrInsert
// Address: 0x00621c10
// Searches a binary search tree for a key. If found, returns pointer to value (at offset 0x10 in node).
// If not found, inserts a new leaf node and returns pointer to its value.
// Tree node structure (size likely 0x18):
//   +0x00: left child (pointer)
//   +0x04: ? (possibly parent, used in iteration)
//   +0x08: right child (pointer)
//   +0x0C: key (uint32_t)
//   +0x10: value (uint32_t) - returned as pointer from this function (node+4 in pointer arithmetic)
//   +0x15: flag (char): 0 = internal node, non-zero = leaf node

uint32_t* EARS::Map::findOrInsert(uint32_t* keyPtr) {
    // Retrieve root node pointer from class at offset 0x1c
    uint32_t* root = *(uint32_t**)((char*)this + 0x1c);
    uint32_t* currentNode = root;
    uint32_t* parentNode = root;  // will hold the last internal node before leaf

    // If root's first child (offset 4) is an internal node, traverse
    if (*(char*)((int)currentNode[1] + 0x15) == 0) {
        uint32_t* walkNode = (uint32_t*)currentNode[1];
        do {
            if (walkNode[3] < *keyPtr) {
                // Go right (child at offset 8)
                uint32_t* nextNode = (uint32_t*)walkNode[2];
            } else {
                // Go left (child at offset 0), update parent
                uint32_t* nextNode = (uint32_t*)*walkNode;
                parentNode = walkNode;
            }
            walkNode = nextNode;
        } while (*(char*)((int)walkNode + 0x15) == 0);
        // Now walkNode is the leaf node, parentNode is the last internal node
    }

    // If parent is root or new key is less than parent's key, we need to insert
    if ((parentNode == root) || (*keyPtr < parentNode[3])) {
        uint32_t keyBuffer[2];            // local_18: {key, 0}
        keyBuffer[0] = *keyPtr;
        keyBuffer[1] = 0;
        // Call insertion helper (address 0x006225e0)
        // Signature: int* insertionFunc(void* this, void* scratch, uint32_t* keyPair, void* something, uint32_t* parent)
        int* result = (int*)FUN_006225e0(this, local_10, keyBuffer, this, parentNode);
        int newFlag = result[0];
        uint32_t* newNode = (uint32_t*)result[1];

        // Error checks (calls FUN_00b97aea which likely throws or logs)
        if (newFlag == 0) {
            FUN_00b97aea();
        }
        if (newNode == root) {
            FUN_00b97aea();
        }

        // Return pointer to value at offset 0x10 (which is newNode + 4 in pointer arithmetic)
        return newNode + 4;
    } else {
        // Key already exists: return pointer to value from the parent node (internal node's data)
        return parentNode + 4;
    }
}