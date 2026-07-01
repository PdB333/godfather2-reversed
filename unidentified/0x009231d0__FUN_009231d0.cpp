// FUNC_NAME: SomeClass::constructor
// Address: 0x009231d0
// Role: Constructor for a class with multiple base classes (vtables at offsets 0x00, 0x10, 0x4C)
// Initializes vtable pointers, calls global init, and optionally performs cleanup if param2 flag is set.

class SomeClass {
public:
    // Virtual table pointer at offset 0x00
    // Second base vtable at offset 0x10
    // Third base vtable at offset 0x4C
    void* vtable0;      // +0x00
    // ... members ...
    void* base2_vtable; // +0x10
    // ... more members ...
    void* base3_vtable; // +0x4C
    // ... more members ...

    // Constructor: param2 indicates whether to call a cleanup function (e.g., for placement new)
    __thiscall SomeClass(byte param2) {
        // Set primary vtable
        this->vtable0 = (void*)&PTR_FUN_00d86ed0;
        // Set vtable for second base class
        this->base2_vtable = (void*)&PTR_LAB_00d86ea8;
        // Set vtable for third base class (first assignment, then overwritten)
        this->base3_vtable = (void*)&PTR_LAB_00d86ea4;
        this->base3_vtable = (void*)&PTR_LAB_00d86ea0;

        // Global state initialization
        DAT_01130064 = 0;  // Global variable cleared
        FUN_005c16e0();    // Initialization routine

        // If param2's low bit is set, call cleanup function (likely destructor or deallocation)
        if ((param2 & 1) != 0) {
            FUN_005c4480(this);  // Cleanup function, may call operator delete or destructor
        }
    }

    // The function returns this pointer in assembly, but in C++ constructors return void.
};