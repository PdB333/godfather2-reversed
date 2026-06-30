// FUNC_NAME: EARSObject::EARSObject
// Address: 0x004c8270
// Constructor for EARSObject. Sets the virtual function table pointer, calls a base class initializer,
// and conditionally invokes a cleanup routine (likely for deallocation) if flag bit 0 is set.

class EARSObject {
public:
    void** vtable; // +0x00 Virtual function table pointer

    // Constructor - takes a byte flag indicating whether to perform cleanup on construction
    EARSObject(byte flag);
};

// External functions called (decompiled from references):
void __thiscall baseConstructor(EARSObject* this); // FUN_004083d0 - base class initialization
void cleanup(EARSObject* ptr);                     // FUN_009c8eb0 - cleanup/destruction helper

EARSObject::EARSObject(byte flag) {
    // Set virtual function table pointer to the class's vtable
    this->vtable = (void**)0x00e365e0;

    // Call base class constructor (likely initializes reference counting or memory management)
    baseConstructor(this);

    // If the lowest bit of flag is set, invoke cleanup (possibly for placement new or ownership handling)
    if (flag & 1) {
        cleanup(this);
    }
}