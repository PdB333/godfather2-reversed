// FUNC_NAME: NetSession::destroy (scalar deleting destructor)
// Address: 0x004d0160
// Removes critical sections, releases a resource pointer, clears the global singleton, optionally frees memory.

// Forward declarations for helper functions
void releaseResource(void* resource);        // FUN_009c8f10 - releases object at +0x18
void operatorDelete(void* ptr);              // FUN_009c8eb0 - global operator delete

// Global singleton pointer (DAT_012234a8)
static NetSession* s_pNetSessionInstance = nullptr;

// Vtable symbol (PTR_LAB_00e36cc4)
extern void* NetSession_vtable;

void __thiscall NetSession::destroy(NetSession* this, byte shouldFreeMemory) {
    // Delete critical sections at offsets +0x68 and +0x28
    DeleteCriticalSection((LPCRITICAL_SECTION)((uint8_t*)this + 0x68));  // +0x68: second CRITICAL_SECTION
    DeleteCriticalSection((LPCRITICAL_SECTION)((uint8_t*)this + 0x28));  // +0x28: first CRITICAL_SECTION

    // Release any pointed-to resource at +0x18
    void* resource = *(void**)((uint8_t*)this + 0x18);  // +0x18: resource pointer
    if (resource != nullptr) {
        releaseResource(resource);
    }

    // Restore vtable to base class (typical in destructor)
    *(void**)this = &NetSession_vtable;         // +0x00: vtable pointer

    // Clear global singleton
    s_pNetSessionInstance = nullptr;

    // If the low bit of shouldFreeMemory is set, free the object memory
    if ((shouldFreeMemory & 1) != 0) {
        operatorDelete(this);
    }
}