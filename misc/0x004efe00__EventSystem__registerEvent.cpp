// FUNC_NAME: EventSystem::registerEvent

struct BucketNode {
    uint32_t key;            // +0x00
    void* data;              // +0x04 (if any)
    BucketNode* next;        // +0x08
};

struct HashTable {
    int32_t numBuckets;      // +0x08
    BucketNode** buckets;    // +0x04
    // other fields omitted
};

// Global pointer to the hash table (DAT_01223398 + 8 points to HashTable)
extern HashTable* g_hashTable;

// Allocates memory of given size (FUN_009c8ed0)
void* allocateMemory(uint32_t size);

// Creates an event node with given parameters (FUN_004efa60)
void* createEventNode(uint32_t param1, uint32_t param2);

// Inserts a node into the hash table (FUN_00423cf0)
void hashTableInsertNode(uint32_t* registrationInfo, void* node, uint32_t bucketIndex);

void __cdecl EventSystem::registerEvent(uint32_t eventId, uint32_t extra1, uint32_t extra2, uint32_t key)
{
    HashTable* ht = g_hashTable;
    uint32_t bucketIndex = key % ht->numBuckets;
    BucketNode* current = ht->buckets[bucketIndex];
    
    // Search for existing node with matching key
    while (current != nullptr && current->key != key) {
        current = current->next;
    }
    
    // Prepare registration info structure
    uint32_t regInfo[4];
    regInfo[0] = 2;          // event type / flags
    regInfo[1] = 0x10;       // size or offset
    regInfo[2] = 0;          // some parameter
    regInfo[3] = eventId;    // the event ID to register
    
    void* newNode = nullptr;
    if (allocateMemory(0x40) == nullptr) {
        newNode = nullptr;
    } else {
        newNode = createEventNode(extra1, extra2);
    }
    
    regInfo[0] = eventId;    // overwritten? Actually local_18[0] = param_1, after regInfo[3]=eventId, now regInfo[0] gets eventId? Wait, check original: local_18[1..3] set then local_18[0] = param_1. So order: regInfo[1]=2, regInfo[2]=0x10, regInfo[3]=0, then regInfo[0]=eventId. So final: regInfo[0]=eventId, regInfo[1]=2, regInfo[2]=0x10, regInfo[3]=0.
    regInfo[0] = eventId;
    
    hashTableInsertNode(regInfo, newNode, bucketIndex);
}