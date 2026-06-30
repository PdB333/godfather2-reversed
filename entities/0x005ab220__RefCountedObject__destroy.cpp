// FUNC_NAME: RefCountedObject::destroy
// Address: 0x005ab220 - Releases reference count and destroys object if last reference
class RefCountedObject {
public:
    int* m_pRefCount; // +0x28 pointer to a 48-byte reference-counted block (size 0x30)

    void destroy() __thiscall;
};

// Global deallocation function pointers (inferred from pattern)
extern void (*g_pDeallocBlock)(void* block, unsigned int size); // dealloc with size
extern void (*g_pDeallocObject)(void* obj);                     // dealloc without size

void RefCountedObject::destroy() {
    // Call first base destructor (0x005b3890)
    baseDestructor1();

    if (m_pRefCount != nullptr) {
        // Decrement reference count
        int* pCount = m_pRefCount;
        (*pCount)--;
        if (*pCount == 0) {
            // Last reference: clean up and free the shared block
            cleanupSharedBlock();   // (0x005a1b40)
            g_pDeallocBlock(m_pRefCount, 0x30);
        }
    }

    // Call second base destructor (0x005a4600)
    baseDestructor2();

    // Deallocate the object itself
    g_pDeallocObject(this);
}