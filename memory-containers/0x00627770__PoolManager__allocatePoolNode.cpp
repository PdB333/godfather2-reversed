// FUNC_NAME: PoolManager::allocatePoolNode
// Address: 0x00627770
// Role: Allocates and initializes a pool node (0x58 bytes) from a manager's free list.

extern "C" void* g_allocator(int, int);  // global allocator, called with (0, size)
extern void* __thiscall allocateFallback(); // fallback allocator (FUN_00635a80)
extern void __cdecl initNodeGlobal();       // global node init (FUN_00627430)

class PoolNode {
public:
    PoolNode* next;          // +0x00  linked list pointer
    uint8_t  flags_04;       // +0x04  set to 8
    uint8_t  flags_05;       // +0x05  set to 0
    uint16_t pad_06;         // +0x06  padding
    uint32_t field_08;       // +0x08  unknown
    uint32_t field_0C;       // +0x0C  unknown
    void*    poolDescriptor; // +0x10  pointer to the pool descriptor (from manager+0x10)
    uint32_t field_14;       // +0x14  zero
    // ... many more fields up to 0x58
};

class PoolManager {
private:
    /* 0x00 - 0x0F: unknown manager state */
protected:
    void*   poolDescriptor;  // +0x10  -> points to a descriptor with head at +0x0C and count at +0x24
    /* ... */
    uint32_t magicValue1;    // +0x40  value copied to node->+0x40
    uint32_t magicValue2;    // +0x44  value copied to node->+0x44
};

PoolNode* __thiscall PoolManager::allocatePoolNode() {
    PoolNode* newNode = (PoolNode*)g_allocator(0, 0x58);  // alloc 88 bytes
    if (!newNode) {
        if (this) {
            newNode = (PoolNode*)allocateFallback();
            return newNode;
        }
        return nullptr;
    }

    // Update pool's allocated byte count
    if (this) {
        int* countPtr = (int*)((char*)poolDescriptor + 0x24);
        *countPtr += 0x58;
    }

    // Insert into singly linked list (head at poolDescriptor+0x0C)
    newNode->next = *(PoolNode**)((char*)poolDescriptor + 0x0C);
    *(PoolNode**)((char*)poolDescriptor + 0x0C) = newNode;

    // Initialize several fields
    *(uint8_t*)((char*)newNode + 0x04) = 8;      // flags_04 = 8
    *(uint8_t*)((char*)newNode + 0x05) = 0;      // flags_05 = 0
    *(uint32_t*)((char*)newNode + 0x1C) = 0;
    *(uint32_t*)((char*)newNode + 0x20) = 0;
    *(uint32_t*)((char*)newNode + 0x50) = 0;
    *(uint32_t*)((char*)newNode + 0x3C) = 0;
    *(uint8_t*)((char*)newNode + 0x32) = 0;
    *(uint8_t*)((char*)newNode + 0x30) = 0;
    *(uint32_t*)((char*)newNode + 0x34) = 0;
    *(uint8_t*)((char*)newNode + 0x31) = 1;
    *(uint32_t*)((char*)newNode + 0x38) = 0;
    *(uint32_t*)((char*)newNode + 0x48) = 0;
    *(uint16_t*)((char*)newNode + 0x2C) = 0;
    *(uint16_t*)((char*)newNode + 0x2E) = 0;
    *(uint32_t*)((char*)newNode + 0x14) = 0;
    *(uint32_t*)((char*)newNode + 0x28) = 0;
    *(uint32_t*)((char*)newNode + 0x54) = 0;
    *(uint32_t*)((char*)newNode + 0x40) = 0;

    // Store the pool descriptor pointer in the node
    newNode->poolDescriptor = poolDescriptor;

    // Global node initialization
    initNodeGlobal();

    // Copy two values from manager into node (magic numbers)
    *(uint32_t*)((char*)newNode + 0x40) = magicValue1;
    *(uint32_t*)((char*)newNode + 0x44) = magicValue2;

    return newNode;
}