// FUNC_NAME: SomeEarsObject::SomeEarsObject (constructor)
// Address: 0x005f59f0
// This constructor initializes an EARS object with virtual table setup and member initialization.
// The 'param_2' flag indicates whether the object was heap-allocated (bit 0 set) so that cleanup can be called on failure.

class SomeEarsObject {
public:
    void* vtable; // first vtable pointer, will be overridden later
    void* secondaryVtable; // +0x04, second vtable pointer (for multiple inheritance or delegation)

    // Constructor with heap allocation flag
    SomeEarsObject(uint8_t heapAllocatedFlag);
};

// Known global variable declarations
extern uint32_t g_someGlobalMutex; // DAT_012069c4, used for synchronization
extern void* g_anotherVtable; // PTR_LAB_00e4079c, final vtable pointer

// External helper functions
void __thiscall initBase(void* this); // FUN_004086d0 - base initialization
void __thiscall initDerived(void* this); // FUN_004083d0 - derived initialization
void __thiscall cleanupAndDelete(void* this); // FUN_009c8eb0 - destructor/deallocation helper

// Constructor implementation
SomeEarsObject::SomeEarsObject(uint8_t heapAllocatedFlag) {
    // Set initial vtable pointers
    this->vtable = &PTR_FUN_00e40788; // +0x00: first virtual table
    this->secondaryVtable = &PTR_LAB_00e4078c; // +0x04: second virtual table (likely a base class)

    // Call base initialization routines
    initBase(this); // uses g_someGlobalMutex (DAT_012069c4)
    initDerived(this);

    // Override vtable pointer with final derived class vtable
    this->vtable = &PTR_LAB_00e4079c; // +0x00: final vtable

    // Reset a global counter/flag
    g_someGlobalCounter = 0; // _DAT_0122351c: possibly reference count or state indicator

    // If object was allocated on heap, call extra cleanup action (e.g., delete if construction fails)
    if ((heapAllocatedFlag & 1) != 0) {
        cleanupAndDelete(this);
    }
}