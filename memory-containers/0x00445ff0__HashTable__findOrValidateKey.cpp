// FUNC_NAME: HashTable::findOrValidateKey
// Address: 0x00445FF0
// Role: Looks up a 128-bit key in a hash table or linked list, potentially validating existence.

struct KeyNode {
    // +0x00: unknown (presumably header or other data)
    KeyNode* listNext; // +0x10: next node in a sequential list
    int listFlag;      // +0x14: non-zero if node is considered "active"/"in use"
    // +0x18-0x1F: unknown
    int keyParts[4];   // +0x20..+0x2C: the 128-bit key
    KeyNode* hashNext; // +0x30: next node in hash chain
};

// Hash table class layout (partial)
// +0x80: KeyNode** hashTable (array of pointers)
// +0x84: uint hashTableSize (size of the array)

void __thiscall HashTable::findOrValidateKey(void* this, int* key128, KeyNode* listHead) {
    int key0 = key128[0];
    
    // Skip if key is all zeros or the known "invalid" sentinel key
    if ((key0 != 0 || key128[1] != 0 || key128[2] != 0 || key128[3] != 0) &&
        !(key0 == -0x45245246 && key128[1] == -0x41104111 &&
          key128[2] == -0x153ea5ab && key128[3] == -0x6eeff6ef)) {
        if (listHead == nullptr) {
            // Use the global hash table
            int cacheResult = FUN_004461c0(key128, 0); // check some cache?
            if (cacheResult == 0) {
                // Hash lookup
                uint hash = FUN_004209c0(key128);
                uint idx = hash % *(uint*)((char*)this + 0x84);
                KeyNode* node = *(KeyNode**)(*(int*)((char*)this + 0x80) + idx * 4);
                while (node != nullptr) {
                    if (node->keyParts[0] == key0 &&
                        node->keyParts[1] == key128[1] &&
                        node->keyParts[2] == key128[2] &&
                        node->keyParts[3] == key128[3]) {
                        break; // found, node points to match
                    }
                    node = node->hashNext;
                }
                if (node == nullptr) {
                    // Key not in hash table; call error/assert handler
                    FUN_00445f30();
                }
                // If found, do nothing (implicit return)
            } else {
                // Cache gave a node, but it's not "active"? Check listFlag
                KeyNode* cacheNode = (KeyNode*)cacheResult;
                if (cacheNode->listFlag == 0) {
                    // Traverse the list from cacheNode until we find an active entry
                    while (cacheNode = cacheNode->listNext, cacheNode != nullptr) {
                        if (cacheNode->listFlag != 0) {
                            return; // found an active node, done
                        }
                    }
                    // If no active node found, fall through (no return)
                }
            }
        } else {
            // Search a custom linked list (provided by listHead)
            KeyNode* cur = listHead->listNext; // first node in the list
            while (cur != nullptr) {
                if (cur->keyParts[0] == key0 &&
                    cur->keyParts[1] == key128[1] &&
                    cur->keyParts[2] == key128[2] &&
                    cur->keyParts[3] == key128[3]) {
                    return; // found match
                }
                cur = cur->listNext;
            }
        }
    }
}