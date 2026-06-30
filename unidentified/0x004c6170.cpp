// FUNC_004c6170: EARSManagedObject::EARSManagedObject(bool isDynamic)
// Constructor for a managed object in EA EARS engine.
// Sets up multiple vtables and optionally registers with the global memory manager.

class EARSManagedObject {
public:
    void* vtable;               // +0x00
    // ... other members ...
    void* secondVTable;         // +0x3C (offset 0xF * 4)
    void* thirdVTable;          // +0x48 (offset 0x12 * 4)
    // ... more members ...

    // Constructor: if isDynamic is true, the object is heap-allocated and must be tracked
    __thiscall EARSManagedObject(bool isDynamic);
};

// Global memory manager (assuming a well-known global pointer)
extern MemoryManager* gMemoryManager;  // DAT_01223410

EARSManagedObject::EARSManagedObject(bool isDynamic) {
    // Set primary vtable (likely for the most derived class)
    this->vtable = reinterpret_cast<void**>(0x00e363a0);

    // Set secondary vtable pointers for multiple inheritance (offset 0x3C and 0x48)
    this->secondVTable = reinterpret_cast<void**>(0x00e363bc);
    this->thirdVTable  = reinterpret_cast<void**>(0x00e363cc);

    // Call static initialization function (e.g., initializes base class members)
    FUN_0046c640();  // Assumed static function that initializes static data or base subobject

    // If the object is dynamically allocated, register it with the memory manager
    if (isDynamic) {
        // Get the memory manager's virtual function table from offset 0x2D4
        void* memMgrVTable = *reinterpret_cast<void**>(reinterpret_cast<char*>(gMemoryManager) + 0x2D4);
        // Call the second virtual function (offset +4) with (this, 0)
        // This likely registers the object for proper deallocation
        typedef void (__thiscall* RegisterFunc)(void* obj, int flag);
        RegisterFunc registerFunc = reinterpret_cast<RegisterFunc>(*reinterpret_cast<void**>(memMgrVTable) + 0x4);
        registerFunc(this, 0);
    }
}