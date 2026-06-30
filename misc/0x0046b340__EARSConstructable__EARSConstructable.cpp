// FUNC_NAME: EARSConstructable::EARSConstructable
// Address: 0x0046b340
// This function is a constructor for an EARS engine derived class.
// It initializes the vtable pointer to a base vtable, calls the base constructor,
// then overwrites the vtable with a derived vtable.
// If param_2 has bit 0 set ('constructFlag & 1'), it calls a deallocation/cleanup function.
// This pattern is common for EA allocator-aware constructors that support placement new with automatic cleanup.

class EARSBase {
public:
    void* vtable; // +0x00

    // Base constructor (at 0x0043e380)
    void __thiscall baseConstructor(void);
};

// Forward declaration of the deallocation function (at 0x009c8eb0)
void __cdecl deallocateOrCleanup(void* ptr);

class EARSConstructable : public EARSBase {
public:
    void* vtable; // +0x00 (overrides base vtable)

    // Constructor with a flag indicating construction mode
    // constructFlag & 1: if set, call deallocation/cleanup after construction
    // (likely used by placement new to free memory if allocation fails)
    void* __thiscall EARSConstructable(byte constructFlag) {
        // Set base vtable pointer
        vtable = (void*)0x00e326a8; // PTR_FUN_00e326a8 (base class vtable)

        // Call base class constructor
        baseConstructor();

        // Override vtable with derived class vtable
        vtable = (void*)0x00e30ea0; // PTR_LAB_00e30ea0 (derived class vtable)

        // If the flag indicates cleanup mode, deallocate/cleanup the object
        if (constructFlag & 1) {
            deallocateOrCleanup(this);
        }

        // Return this pointer (common convention for __thiscall constructors)
        return this;
    }
};