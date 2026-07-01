//FUNC_NAME: SomeClass::~SomeClass
// Function address: 0x008d2070
// Destructor for a class with multiple inheritance (3 vtable pointers).
// Cleans up a sub-object at offset 0x50, calls a global destructor hook,
// and optionally deallocates memory (size 0x70) if param_2 & 1.

// Vtable pointers (from Ghidra):
// *this = &PTR_FUN_00d7d370
// this[0x0F] = &PTR_LAB_00d7d360
// this[0x12] = &PTR_LAB_00d7d35c

// Sub-object pointer at offset 0x50 (this[0x14])
// Cleanup functions:
//   FUN_004086d0 - likely release/destroy sub-object
//   FUN_00408310 - likely additional cleanup
// Global destructor hook: FUN_0046c640
// Memory deallocation: FUN_0043b960 (operator delete with size 0x70)

undefined4* __thiscall SomeClass::~SomeClass(undefined4* this, byte param_2)
{
    // Set vtable pointers to base class vtables (for proper virtual dispatch during destruction)
    *this = &PTR_FUN_00d7d370;          // +0x00: first vtable
    this[0x0F] = &PTR_LAB_00d7d360;     // +0x3C: second vtable
    this[0x12] = &PTR_LAB_00d7d35c;     // +0x48: third vtable

    // If the sub-object pointer at offset 0x50 is non-null, clean it up
    if (this[0x14] != 0) {              // +0x50: pointer to sub-object
        // Release/destroy the sub-object (two-step cleanup)
        FUN_004086d0(this + 0x14);      // pass address of the pointer
        FUN_00408310(this + 0x14);
    }

    // Global destructor hook (e.g., notify destruction, unregister from manager)
    FUN_0046c640();

    // If param_2 & 1, deallocate the memory for this object (size 0x70)
    if ((param_2 & 1) != 0) {
        FUN_0043b960(this, 0x70);       // operator delete
    }

    return this;
}