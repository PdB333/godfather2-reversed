// FUNC_NAME: RefCountedPtr::~RefCountedPtr

struct RefCountedBlockVtable {
    void (*Destroy)(int arg); 
};

struct RefCountedBlock {
    RefCountedBlockVtable* vtable; // +0x00
    short weakRefCount;            // +0x04 (check if non-zero before releasing)
    short strongRefCount;          // +0x06 (decremented, when zero calls vtable->Destroy)
};

struct RefCountedPtr {
    RefCountedBlock* m_pBlock; // +0xC0 (offset 0x30 * 4)
    // ... other members ...
};

extern void* g_BaseVtable; // PTR_FUN_00e39bc8, likely base vtable for RefCountedPtr
void __thiscall operatorDelete(void* ptr); // FUN_009c8eb0

void* __thiscall RefCountedPtr::~RefCountedPtr(byte deletingFlag) {
    RefCountedBlock* pBlock = this->m_pBlock;
    
    // Reset vtable to base (usually safe and prevents subsequent virtual calls)
    this->m_vtable = &g_BaseVtable;
    
    if (pBlock != nullptr) {
        // Only proceed if weak reference count is non-zero (object still considered alive)
        if (pBlock->weakRefCount != 0) {
            // Decrement strong reference count
            pBlock->strongRefCount--;
            if (pBlock->strongRefCount == 0) {
                // Last strong reference released: destroy the underlying object via virtual call
                pBlock->vtable->Destroy(1);
            }
        }
        this->m_pBlock = nullptr;
    }
    
    // If the destructor was called as part of a delete expression, free memory
    if (deletingFlag & 1) {
        operatorDelete(this);
    }
    
    return this;
}