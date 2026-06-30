// StringMap::remove (0x0049c7f0)
// Removes a node identified by key from both the ordered list and hash chain.
void __thiscall StringMap::remove(char* key)
{
    // Node structure: 
    // +0x04: char* key
    // +0x08: uint hashValue
    // +0x10: StringMapNode* nextOrder
    // +0x14: StringMapNode* nextHash
    struct StringMapNode {
        char* key;
        uint hashValue;
        StringMapNode* nextOrder;
        StringMapNode* nextHash;
    };

    StringMapNode* prevNode = nullptr;
    StringMapNode* currentNode = *(StringMapNode**)(this + 4); // Root of ordered list

    if (currentNode == nullptr) {
        return; // Empty tree
    }

    // Compare root node's key
    int cmpResult;
    if (currentNode->key == nullptr || key == nullptr) {
        // Pointer comparison fallback for null strings
        cmpResult = (currentNode->key < key) ? -1 : (currentNode->key > key) ? 1 : 0;
    } else {
        cmpResult = __stricmp(currentNode->key, key);
    }

    if (cmpResult == 0) {
        // Remove root node
        *(StringMapNode**)(this + 4) = currentNode->nextOrder;
        removeFromHashChain(currentNode);
        freeNode(currentNode);
        return;
    }

    // Search through ordered list (prevNode and currentNode)
    prevNode = currentNode;
    currentNode = currentNode->nextOrder;
    while (currentNode != nullptr) {
        if (currentNode->key == nullptr || key == nullptr) {
            cmpResult = (currentNode->key < key) ? -1 : (currentNode->key > key) ? 1 : 0;
        } else {
            cmpResult = __stricmp(currentNode->key, key);
        }

        if (cmpResult == 0) {
            // Remove currentNode from ordered list by updating prevNode's nextOrder
            prevNode->nextOrder = currentNode->nextOrder;
            removeFromHashChain(currentNode);
            freeNode(currentNode);
            return;
        }

        prevNode = currentNode;
        currentNode = currentNode->nextOrder;
    }
}

// Helper: remove a node from the hash chain (bucket array)
void __thiscall StringMap::removeFromHashChain(StringMapNode* node)
{
    // Static hash table globals
    static bool hashTableInitialized = false;
    static uint bucketCount; // DAT_01223984
    static StringMapNode** bucketArray; // DAT_01223980
    static uint nodeCount; // DAT_01223988

    // Ensure hash table is initialized
    if (!hashTableInitialized) {
        hashTableInitialized = true;
        initHashTable(); // FUN_0049ca20
        atexit(cleanupHashTable); // _atexit(&LAB_00d50b90)
    }

    uint bucketIndex = node->hashValue % bucketCount;
    StringMapNode* prev = nullptr;
    StringMapNode* current = bucketArray[bucketIndex];

    while (current != nullptr && current != node) {
        prev = current;
        current = current->nextHash;
    }

    if (current == nullptr) {
        // Node not found in hash chain (should not happen)
        return;
    }

    if (prev == nullptr) {
        bucketArray[bucketIndex] = current->nextHash;
    } else {
        prev->nextHash = current->nextHash;
    }
    nodeCount--;
}