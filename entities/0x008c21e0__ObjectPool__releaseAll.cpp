// FUNC_NAME: ObjectPool::releaseAll
// This function iterates over an array of slots (each 0x1C bytes), frees the dynamically allocated object stored at offset 0x10 within each slot, then frees the slot array itself and resets the pool state.

// Structure representing one slot in the pool.
// Each slot has a pointer to a heap-allocated object at offset 0x10.
// The total slot size is 0x1C bytes.
struct PoolSlot {
    // +0x00: unknown data (possibly flags/handle)
    // +0x04: unknown
    // +0x08: unknown
    // +0x0C: unknown
    void* object;   // +0x10: pointer to the actual object
    // +0x14: unknown
    // +0x18: unknown
};  // size 0x1C

// Memory pool container.
// +0x00: pointer to array of PoolSlot
// +0x04: number of active slots (count)
// +0x08: capacity (not directly used in this function)
class ObjectPool {
public:
    PoolSlot* slots;    // +0x00
    int count;          // +0x04
    int capacity;       // +0x08

    // Releases all objects and frees the slot array.
    void __fastcall releaseAll();
};

// Callee: frees/destructs a single object. Takes the pointer as parameter.
// Prototype: void freeMemory(void* ptr);
void freeMemory(void* ptr);

void __fastcall ObjectPool::releaseAll()
{
    int idx = this->count - 1;
    if (idx >= 0)
    {
        int offset = idx * sizeof(PoolSlot); // 0x1C * idx
        do
        {
            // Read the object pointer from the slot at offset 0x10
            void* obj = *(void**)( (char*)this->slots + offset + 0x10 );
            if (obj != 0)
            {
                freeMemory(obj);
            }
            --idx;
            offset -= sizeof(PoolSlot); // move to previous slot
        } while (idx >= 0);
    }

    // Reset count
    this->count = 0;

    // Free the slot array itself
    freeMemory(this->slots);
    this->slots = 0;
    this->capacity = 0;
}