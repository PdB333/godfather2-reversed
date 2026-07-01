// FUNC_NAME: UnknownClass::UnknownClass
// Constructor for a class with multiple inheritance (vtable at offset 0 and at offset 0x214)
// Calls base constructor at 0x004c26c0, then initializes fields and sets vtables.
// Offsets are in dword units (multiply by 4 for byte offset).
// +0x208 (param_1[0x82]): field1 (int) initialized to 0
// +0x20C (param_1[0x83]): field2 (int) initialized to 0
// +0x210 (param_1[0x84]): field3 (int) initialized to 0
// +0x21C (param_1[0x87]): field4 (int) initialized to 0
// +0x214 (param_1[0x85]): base class vtable pointer (initially set to &PTR_FUN_00e2f19c, then overwritten to &PTR_LAB_00d825f4)
// +0x218 (param_1[0x86]): field5 (int) initialized to 1
// +0x000 (param_1[0]): derived class vtable pointer set to &PTR_FUN_00d82604

#include <cstdint>

class UnknownClass {
public:
    // Vtable pointer at offset 0
    void** vtable; // +0x00

    // Other members (offsets approximate)
    int32_t field1; // +0x208
    int32_t field2; // +0x20C
    int32_t field3; // +0x210
    int32_t field4; // +0x21C
    void** baseVtable; // +0x214 (base class vtable)
    int32_t field5; // +0x218

    // Constructor
    UnknownClass() {
        // Call base class constructor (sets baseVtable to &PTR_FUN_00e2f19c)
        FUN_004c26c0();

        // Initialize fields to 0
        field1 = 0;
        field2 = 0;
        field3 = 0;
        field4 = 0;

        // Set base vtable to a temporary pointer (will be overwritten)
        baseVtable = &PTR_FUN_00e2f19c;

        // Set field5 to 1
        field5 = 1;

        // Set derived class vtable
        vtable = &PTR_FUN_00d82604;

        // Override base vtable with derived class's base vtable
        baseVtable = &PTR_LAB_00d825f4;
    }
};