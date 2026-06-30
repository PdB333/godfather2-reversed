// FUNC_NAME: EAPoolManager::shutdown
typedef void (*PoolCleanupFunc)(int);   // callback function pointer type
typedef void (*ReleasePoolFunc)(void*); // pool release function type

// Global pool allocators (from static initializers)
extern void* g_poolAllocator1; // DAT_01206970
extern void* g_poolAllocator2; // DAT_01206980

struct EAPoolManager {
    // ... (other fields not used here) ...
    PoolCleanupFunc cleanupCallback;  // offset +0x130
    uint8_t flags;                    // offset +0x160
    // ...
};

void __fastcall EAPoolManager::shutdown(void) {
    // If a cleanup callback is registered, invoke it with argument 1
    if (this->cleanupCallback != nullptr) {
        this->cleanupCallback(1);
    }
    this->cleanupCallback = nullptr;

    // Release first pool allocator if owned (bit 0)
    if (this->flags & 1) {
        ((ReleasePoolFunc)0x004086d0)(g_poolAllocator1);
        this->flags &= ~1;
    }
    // Release second pool allocator if owned (bit 1)
    if (this->flags & 2) {
        ((ReleasePoolFunc)0x004086d0)(g_poolAllocator2);
        this->flags &= ~2;
    }
}