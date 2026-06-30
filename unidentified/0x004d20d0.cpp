// FUN_004d20d0: MemoryPool::freeObject

class MemoryPool {
public:
    // Global base address (0x012054ac) points to a singleton MemoryPool instance.
    // Offsets from this base:
    // +0x8004: Start of the pool block (pointer)
    // +0x8008: Size of the pool block (uint32)
    // +0x800c: Head of free list (pointer)
    // +0x8018: Number of free slots (int32)
    // +0x8020: Pointer to a vtable for custom deleter (used for objects outside the pool)
    
    void* m_poolStart;      // +0x8004
    uint32_t m_poolSize;    // +0x8008
    void* m_freeHead;       // +0x800c
    int32_t m_freeCount;    // +0x8018
    void* m_deleterVtable;  // +0x8020
};

// Global singleton (as seen in the binary)
static MemoryPool* gMemoryPool = reinterpret_cast<MemoryPool*>(0x012054ac);

// __fastcall: param_1 (ecx) is unused (maybe a pool index or leftover), param_2 (edx) is the object to free.
void __fastcall MemoryPool::freeObject(void* param_1, void* obj) {
    // param_1 is ignored; the pool is accessed globally.
    // Check if object is non-null and pool is initialized.
    if (obj == nullptr || gMemoryPool->m_poolStart == nullptr) {
        return;
    }

    // If a custom deleter is registered and the object is outside the pool range,
    // use the deleter's destructor (vtable slot at index 2, offset +8).
    void* deleter = gMemoryPool->m_deleterVtable;
    if (deleter != nullptr) {
        void* poolEnd = static_cast<char*>(gMemoryPool->m_poolStart) + gMemoryPool->m_poolSize;
        if (obj < gMemoryPool->m_poolStart || obj >= poolEnd) {
            // Call the custom deallocator (__thiscall with this = obj)
            void** vtable = *static_cast<void**>(deleter);
            using DeallocFunc = void (__thiscall*)(void*);
            DeallocFunc dealloc = reinterpret_cast<DeallocFunc>(vtable[2]); // index 2 = +8 bytes
            dealloc(obj);
            return;
        }
    }

    // Standard pool free: push object onto free list (LIFO)
    *static_cast<void**>(obj) = gMemoryPool->m_freeHead;
    gMemoryPool->m_freeCount++;
    gMemoryPool->m_freeHead = obj;
}