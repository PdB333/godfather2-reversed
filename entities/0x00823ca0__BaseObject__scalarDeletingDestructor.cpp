// FUNC_NAME: BaseObject::scalarDeletingDestructor
// Address: 0x00823ca0
// Role: Scalar deleting destructor for a common base class (likely BaseObject or Entity)
// Provides the standard MSVC++ pattern: calls the real destructor, then optionally calls operator delete.
class BaseObject {
public:
    // The real destructor (called with 'this').
    void __thiscall destroyContents(); // FUN_004daf90

    // Global operator delete (or game-specific deallocator).
    static void __cdecl freeMemory(void* ptr); // FUN_009c8eb0

    // Deletion destructor – returns 'this' for chaining.
    BaseObject* __thiscall destroy(char flags) {
        // Check if the vtable pointer (first 4 bytes) is non‑zero.
        // This indicates the object has not yet been fully destroyed.
        if (*(int*)this != 0) {
            this->destroyContents();
        }
        // If bit 0 of 'flags' is set, release the memory.
        if ((flags & 1) != 0) {
            freeMemory(this);
        }
        return this;
    }
};
```