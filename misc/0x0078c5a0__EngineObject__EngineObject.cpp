// FUNC_NAME: EngineObject::EngineObject
// Address: 0x0078c5a0
// Role: Constructor for an engine object with a flag indicating allocation type.

class EngineObjectBase {
public:
    EngineObjectBase(); // Base constructor at 0x004083d0
};

class EngineObject : public EngineObjectBase {
public:
    // Constructor. param_2 is a byte flag; if bit0 is set, the object was dynamically allocated
    // and an additional cleanup function is called after initialization.
    // This pattern is common in EA's EARS engine for constructors that can handle both stack and heap objects.
    EngineObject(bool isAllocated);
};

// Constructor implementation
EngineObject::EngineObject(bool isAllocated) {
    // Set the vtable pointer to the object's virtual function table.
    // VTable at 0x00d587e0
    this->vtable = reinterpret_cast<uintptr_t*>(0x00d587e0);

    // Call base class constructor
    EngineObjectBase::EngineObjectBase(); // FUN_004083d0

    // If the object was allocated on the heap, perform additional cleanup or deallocation.
    // This is likely a safety measure to free memory if base construction fails,
    // but here it's executed unconditionally after base init.
    if (isAllocated) {
        // Call cleanup/destructor function at 0x009c8eb0
        // The function takes this pointer and likely performs destruction and deallocation.
        this->cleanupAndDeallocate(); // FUN_009c8eb0(this)
    }
}

// Note: The function at 0x009c8eb0 might be the destructor or a helper that frees memory.
// However, calling it in the constructor after base init is unusual; perhaps the decompilation
// order is incorrect or this is a specialized constructor for placement new with conditional delete.