// FUNC_NAME: SomeClass::constructor
// Function address: 0x0077eda0
// Role: Constructor for a class with multiple inheritance (sets vtable pointers at offsets 0x00, 0x3C, 0x48).
// Calls base constructor FUN_0077b6b0, initializes a global, and optionally deletes a child object at offset 0x5C.
// The 'flags' parameter controls whether to call operator delete (size 0x84) after construction (placement new pattern).

class SomeClass {
public:
    // Vtable pointer at +0x00
    void* vtable;
    // Additional vtable pointers for multiple inheritance
    void* field_0x3C; // +0x3C (offset 0xf in 4-byte words)
    void* field_0x48; // +0x48 (offset 0x12 in 4-byte words)
    // Pointer to a child object at +0x5C (offset 0x17 in words)
    void* childObject; // +0x5C

    // Constructor
    __thiscall SomeClass* constructor(SomeClass* this, byte flags) {
        // Set vtable pointers
        this->vtable = &PTR_FUN_00d6920c;
        this->field_0x3C = &PTR_LAB_00d691fc;
        this->field_0x48 = &PTR_LAB_00d691f8;

        // Initialize global data (likely a singleton or static manager)
        FUN_004086d0(&DAT_0120e93c);

        // Call base class constructor
        FUN_0077b6b0(this);

        // If a child object already exists, destroy it (re-initialization safety)
        if (this->childObject != 0) {
            FUN_009c8eb0(this->childObject);
        }

        // Additional initialization
        FUN_0046c640();

        // If flags bit 0 is set, deallocate this object (placement new pattern)
        if ((flags & 1) != 0) {
            FUN_0043b960(this, 0x84); // operator delete with size 0x84
        }

        return this;
    }
};