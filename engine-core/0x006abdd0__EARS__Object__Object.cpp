// FUNC_NAME: EARS::Object::Object
// Constructor for a class with dual vtable pointers (virtual inheritance or interface)
// Address: 0x006abdd0
// Sets up base and derived vtables, constructs base subobjects via static init.

class EARS::Object {
public:
    // vtable pointers at offsets 0 and 4 (MSVC virtual base layout)
    // +0x00: Derived vtable (initially base, then overridden)
    // +0x04: Second vtable (likely for an interface or virtual base)
    void** vtable;
    void** vtable2;
    // ... other members ...
};

EARS::Object* __thiscall EARS::Object::Object(byte allocatedFlag) {
    // Step 1: Set base class vtable pointers (temporary)
    this->vtable = &PTR_FUN_00d5da74;   // Base vtable for offset 0
    this->vtable2 = &PTR_LAB_00d5da64;  // Second vtable (virtual base or interface)

    // Step 2: Call base class constructor using a static instance
    // DAT_012069c4 may be a static reference counter or memory manager
    FUN_004086d0(&DAT_012069c4);

    // Step 3: Static initialization (e.g., register class, increment global counter)
    FUN_004083d0();

    // Step 4: Overwrite primary vtable with final derived class vtable
    this->vtable = &PTR_LAB_00d5da60;   // Actual derived class vtable

    // Step 5: Reset global static variable
    DAT_01129900 = 0;  // Possibly a reference count or construction flag

    // Step 6: If memory was allocated externally, free it on failure? (common pattern)
    if (allocatedFlag & 1) {
        FUN_009c8eb0(this);  // Likely operator delete (destructor not called directly)
    }

    return this;
}