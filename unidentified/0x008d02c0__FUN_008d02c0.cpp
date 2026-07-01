// FUNC_NAME: SomeClass::constructor
// Function address: 0x008d02c0
// This is a constructor for an unknown class. It initializes the vtable pointer,
// sets up secondary vtable pointers (likely for multiple inheritance), calls a base
// constructor (FUN_0083f920), and optionally deletes the object if a flag is set.
// The flag param_2 (isHeapAllocated) indicates whether this object was allocated via operator new.
// If true, the constructor calls operator delete on itself with size 0x5c (92 bytes),
// which is a pattern for "placement delete" or failure cleanup.

class SomeClass {
public:
    // Virtual function table pointer (offset +0x00)
    void* vtablePtr;

    // Secondary vtable pointers (likely for additional base classes)
    // +0x3C (0xF * 4) and +0x48 (0x12 * 4)
    void* secondaryVtable1;
    void* secondaryVtable2;

    // Constructor: takes a bool for heap allocation flag
    SomeClass(void* this, byte isHeapAllocated) {
        // Set primary vtable
        *this = &PTR_FUN_00d7ce90;   // vtable
        // Set secondary vtables
        this[0xF] = &PTR_LAB_00d7ce80;  // +0x3C
        this[0x12] = &PTR_LAB_00d7ce7c; // +0x48

        // Call base class constructor (likely a parent class)
        FUN_0083f920(); // BaseClass::constructor

        // If the object was heap-allocated, free it?
        // This is unusual: the constructor potentially deletes itself.
        if ((isHeapAllocated & 1) != 0) {
            FUN_0043b960(this, 0x5c); // operator delete(this, 92)
        }
    }
};