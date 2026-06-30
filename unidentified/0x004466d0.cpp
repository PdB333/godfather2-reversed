// FUN_004466d0: EARS::HashMap::insertNode
// This function removes a node from its current global list (if any) and inserts it into a hash bucket chain
// using a 4-int key. The container has a global doubly linked list at offsets 0x0c/0x10 and bucket chains at 0x14/0x18.

class HashMap {
public:
    int **bucketArray;         // +0x70 array of pointers to bucket heads (each points to a node or sentinel)
    int bucketCount;           // +0x74 number of buckets
};

class HashNode {
public:
    HashNode *globalPrev;      // +0x0c
    HashNode *globalNext;      // +0x10
    HashNode *bucketPrev;      // +0x14 (used for bucket chain pointer manipulation)
    HashNode *bucketNext;      // +0x18 bucket chain next pointer (used for traversal)
    int key[4];                // +0x20
    // additional data...
};

// external functions:
unsigned int hashKey(int key[4]);            // FUN_004209c0
int* getNodeKey(HashNode *node);             // FUN_0043ab10 - returns pointer to node->key

void __thiscall HashMap::insertNode(HashNode *node, int *key)
{
    // Remove from current global list (if node is already in one)
    if (node->globalPrev != nullptr) {
        node->globalPrev->globalNext = node->globalNext;
    }
    if (node->globalNext != nullptr) {
        node->globalNext->globalPrev = node->globalPrev;
    }
    node->globalNext = nullptr;  // optional cleanup
    node->globalPrev = nullptr;

    // Copy the new key into the node
    node->key[0] = key[0];
    node->key[1] = key[1];
    node->key[2] = key[2];
    node->key[3] = key[3];

    // Determine bucket index
    unsigned int hash = hashKey(key);
    int index = hash % bucketCount;
    HashNode *bucketHead = bucketArray[index];  // pointer to the first node in that bucket chain

    // Traverse the bucket chain to find the first node with a matching key (or end)
    while (bucketHead != nullptr) {
        int *nodeKey = getNodeKey(bucketHead);
        if (nodeKey[0] == key[0] && nodeKey[1] == key[1] &&
            nodeKey[2] == key[2] && nodeKey[3] == key[3]) {
            break;  // found an existing node with the same key (duplicate? insert after it)
        }
        bucketHead = bucketHead->bucketNext;  // +0x18
    }

    // Insert node into the bucket chain after bucketHead (or at head if bucketHead is nullptr?)
    // Note: The original code uses bucketHead+0x14 (bucketPrev) as the insertion point.
    // This suggests that bucketHead is used as a sentinel or the previous node in the bucket chain.
    // We follow the original logic but with caution.
    HashNode **insertionPoint = &(bucketHead->bucketPrev);  // &(node+0x14)
    node->bucketNext = bucketHead->bucketPrev;              // node->bucketNext = *insertionPoint
    node->bucketPrev = insertionPoint;                      // node->bucketPrev = address of the slot

    if (*insertionPoint != nullptr) {
        (*insertionPoint)->bucketPrev = &(node->bucketNext); // update the preceding node's "prev" to point to node's next link
    }
    *insertionPoint = node;                                 // finally attach node
}
```