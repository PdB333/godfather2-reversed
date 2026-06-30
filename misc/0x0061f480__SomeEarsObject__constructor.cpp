// FUNC_NAME: SomeEarsObject::constructor
// Address: 0x0061f480
// Role: Constructor for a derived EARS object. Sets base class vtable, calls base constructor,
// then replaces vtable with derived vtable. If param_2 bit 0 is set, allocates memory of size 0xE0
// via a global allocator and calls a function at offset 4 of the allocator result (placement new).

// Note: Vtable addresses: base at 0x00e41380, derived at 0x00e41338.
// The derived class size appears to be 0xE0 (224 bytes).
// The base constructor is at FUN_0061f6d0 (__thiscall on this).

// Class definitions (assumed)
class SomeEarsObjectBase { // Base class
public:
    void** vtable;
    // ... members?
    SomeEarsObjectBase(); // Constructor at FUN_0061f6d0
};

class SomeEarsObject : public SomeEarsObjectBase {
public:
    // Constructor (this function)
    void* operator new(size_t size); // The allocation mechanism
    SomeEarsObject(byte flags); // This function

    // Vtable pointer: at the start of object
    static const void* baseVtable;  // 0x00e41380
    static const void* derivedVtable; // 0x00e41338
};

// Improved signature: returns this pointer
SomeEarsObject* __thiscall SomeEarsObject::constructor(SomeEarsObject* this, byte flags) {
    int* allocFunc;

    // Set base class vtable temporarily (base class constructor will use this)
    this->vtable = &baseVtable;

    // Call base class constructor
    // Base constructor is __thiscall on this, so we call it with this pointer
    FUN_0061f6d0(this);  // Actually called as FUN_0061f6d0() with implicit this; clarified here

    // After base constructor, set derived class vtable
    this->vtable = &derivedVtable;

    // If bit 0 of flags is set, allocate memory for the object and construct using placement new
    if ((flags & 1) != 0) {
        // Get a global allocator function table (returns a pointer to a struct with vtable)
        allocFunc = (int*)FUN_009c8f80();

        // Call function at offset 4 in that allocator struct (likely a placement new or copy constructor)
        // Parameters: this pointer (object address) and size 0xE0
        (**(code**)(*allocFunc + 4))(this, 0xE0);
    }

    return this;
}