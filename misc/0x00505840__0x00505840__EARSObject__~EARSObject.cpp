// FUNC_NAME: 0x00505840: EARSObject::~EARSObject
// Destructor for base EARSObject. Releases associated memory block and optionally deallocates this object.
// vtable at +0x00, m_pMemoryBlock at +0x10, m_nBlockSize at +0x14

class EARSObject {
public:
    void* vtable;       // +0x00
    // other fields ...
    void* m_pMemoryBlock; // +0x10
    int   m_nBlockSize;   // +0x14
};

// Global memory manager base address (DAT_01206880)
extern char* g_MemoryManager;

// Insert a freed memory block into the object pool's free list.
// The free list nodes are 8 bytes each: [vtableTag, next].
void MemoryManager_ReturnBlock(void* block)
{
    // Insert pointer is at g_MemoryManager + 0x14
    int* pWrite = (int*)(g_MemoryManager + 0x14);
    // Write vtable tag (sentinel)
    *((void***) *pWrite) = (void**) &PTR_LAB_01123be8;
    // Write next pointer (the freed block)
    *pWrite += 4;
    *(int*) *pWrite = (int)block;
    *pWrite += 4;
}

// Deallocation function (FUN_009c8eb0)
extern void operator delete(void* ptr);

void __thiscall EARSObject::~EARSObject(byte destructorFlags)
{
    this->vtable = &PTR_FUN_00e37110; // Base vtable

    if (this->m_pMemoryBlock != nullptr) {
        MemoryManager_ReturnBlock(this->m_pMemoryBlock);
        this->m_pMemoryBlock = nullptr;
        this->m_nBlockSize = 0;
    }

    if (destructorFlags & 1) {
        ::operator delete(this);
    }
}