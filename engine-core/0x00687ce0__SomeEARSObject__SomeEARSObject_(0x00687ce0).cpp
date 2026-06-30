// FUNC_NAME: SomeEARSObject::SomeEARSObject (0x00687ce0)
// Role: Constructor for a 0x60-byte EARS object with optional memory management flag.

class SomeEARSObject : public EARSBase {
public:
    // Constructor: if flags & 1, frees the allocated memory immediately (fallback cleanup).
    SomeEARSObject(byte flags);
};

SomeEARSObject::SomeEARSObject(byte flags) {
    // Call base class constructor (FUN_0090e420) - typically initializes vtable and basic fields.
    EARSBase::EARSBase(); // 0x0090e420

    // If the "allocated" flag is set (bit 0), the memory for this object was heap-allocated
    // and should be freed if construction fails. Here, after base initialization, we deallocate.
    // This pattern is used in EA's EARS engine for placement-new objects that own their buffer.
    if (flags & 1) {
        deallocateMemory(this, 0x60); // FUN_0043b960 - operator delete with size 0x60
    }
}