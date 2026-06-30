// FUNC_NAME: ObjectPool::constructor
// Address: 0x0069ce60
// Role: Constructor for a fixed-size object pool. Initializes the pool buffer by copying a pre-initialized pattern from the end to the start, likely setting up a free list.

// Global data
extern int g_poolElementCount;          // DAT_00e506b4 - number of elements in pool (each element 8 bytes)
extern char g_poolBuffer[];             // DAT_00e506b8 - raw buffer for pool slots
extern ObjectPool* g_pTheObjectPool;    // DAT_011299d4 - singleton pointer to the pool

// Forward declaration of helper function (likely sets up free list)
void initPoolFreeList(void* dest, void* src, int count); // FUN_0069cd70

// Vtable symbol (from PTR_LAB_00d5cf10)
extern void* __vtable_ObjectPool[];

class ObjectPool {
public:
    // Constructor
    __thiscall ObjectPool() {
        int totalBytes = g_poolElementCount * 8;          // iVar1 = DAT_00e506b4 * 8
        g_pTheObjectPool = this;                          // DAT_011299d4 = param_1
        this->vtable = __vtable_ObjectPool;               // *param_1 = &PTR_LAB_00d5cf10

        // Initialize the free list: copy the last 'count' elements to the beginning
        // Arguments: dest = start of buffer, src = start + totalBytes, count = totalBytes >> 3 (number of 8-byte elements)
        initPoolFreeList(g_poolBuffer, g_poolBuffer + totalBytes, totalBytes >> 3);
    }

    void* vtable; // +0x00
};