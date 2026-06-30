// FUNC_NAME: ResourceMap::findNode
// Address: 0x00446220
// Called from: 0x00840b00
// Purpose: Lookup a node in a hash table with a 128-bit primary key and a secondary integer key.
// Fields:
//   this+0x70: pointer to bucket array (array of pointers to HashNode)
//   this+0x74: number of buckets (size modulo)
// HashNode offsets:
//   0x00: pointer to key array (4 ints) – accessed via getKey()
//   0x08: secondaryKey (compared to second parameter)
//   0x10: nextSecondary (linked list for same primary key, different secondary)
//   0x18: nextCollision (hash collision chain)

#include <cstdint>

// Forward declarations (assumed from other parts of codebase)
uint32_t hashKey(int* key);  // FUN_004209c0
int* getNodeKey(void* node); // FUN_0043ab10 – returns pointer to the 4-int key of the node

class HashNode {
public:
    int* keyPtr;        // +0x00
    int unused04;       // +0x04 (likely padding or other data)
    int secondaryKey;   // +0x08
    HashNode* nextSecondary;  // +0x10
    HashNode* nextCollision;  // +0x18
};

class ResourceMap {
public:
    HashNode** bucketArray; // +0x70
    uint32_t bucketCount;   // +0x74
};

void* __thiscall ResourceMap::findNode(ResourceMap* thisPtr, int* primaryKey, int secondaryKey) {
    uint32_t hash = hashKey(primaryKey);
    uint32_t index = hash % thisPtr->bucketCount;
    HashNode* node = thisPtr->bucketArray[index];

    // Traverse collision chain to find matching primary key
    while (node != nullptr) {
        int* nodeKey = getNodeKey(node); // returns pointer to 4 ints
        if (nodeKey[0] == primaryKey[0] &&
            nodeKey[1] == primaryKey[1] &&
            nodeKey[2] == primaryKey[2] &&
            nodeKey[3] == primaryKey[3]) {
            break; // primary key match found
        }
        node = node->nextCollision;
    }

    // Now traverse secondary chain to find matching secondary key
    while (node != nullptr) {
        if (node->secondaryKey == secondaryKey) {
            return node;
        }
        node = node->nextSecondary;
    }

    return nullptr;
}