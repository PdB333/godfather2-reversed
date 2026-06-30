// FUNC_NAME: InstanceManager::findInstance
// Address: 0x0049c5c0
// Role: Performs hash-based lookup for a game object instance by its ID (passed in ESI).
//        Includes one-time initialization of the hash table.

#include <cstdint>  // for uint32_t

// Global hash table data (locations from binary)
extern uint32_t  g_instanceTableInitFlag;  // _DAT_01223990
extern uint32_t* g_instanceTableBuckets;   // DAT_01223980 – array of pointers to linked list heads
extern int32_t   g_instanceTableSize;      // DAT_01223984 – number of buckets in hash table

// Forward declarations of helper functions (defined elsewhere)
void initInstanceTable(void);           // FUN_0049ca20 – initializes hash table
void destroyInstanceTable(void);        // 0x00d50b90 – registered via atexit

// Hash node layout (offsets relative to node pointer):
// +0x00: (unknown, 8 bytes) – possibly previous/link or other data
// +0x08: uint32_t key (instance ID)
// +0x14: next pointer
struct HashNode {
    uint8_t  _padding[8];    // +0x00 to +0x07
    uint32_t key;            // +0x08
    HashNode* next;          // +0x14
};

// __thiscall would normally use ECX for 'this', but here the key is passed in ESI.
// This function is a static/global lookup routine that receives the key in ESI (custom ABI).
void __fastcall InstanceManager::findInstance(uint32_t key) // key in ESI (mapped to first fastcall param via convention)
{
    // One‑time initialization of the global hash table
    if ((g_instanceTableInitFlag & 1) == 0) {
        g_instanceTableInitFlag |= 1;
        initInstanceTable();
        atexit(destroyInstanceTable);
    }

    // Compute bucket index
    int bucketIdx = key % g_instanceTableSize;

    // Traverse the linked list in the selected bucket
    HashNode* node = reinterpret_cast<HashNode*>(g_instanceTableBuckets[bucketIdx]);
    while (node != nullptr && node->key != key) {
        node = node->next; // +0x14 offset
    }

    // Found node pointer is left in EAX (not explicitly returned, but caller uses it)
    // The C++ return type is void for consistency with the original binary signature.
}