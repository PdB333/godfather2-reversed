// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x006d5d50
// Constructor for a class with multiple inheritance (vtables at offsets 0x00, 0x3C, 0x48, 0x50, 0x58)
// param_2: allocation flag (bit 0 indicates whether to allocate memory for the object)

SomeClass* __thiscall SomeClass::SomeClass(SomeClass* this, byte allocFlag)
{
    // Set main vtable pointer (offset +0x00)
    this->vtable = &PTR_FUN_00d5f3f0;

    // Set vtable pointers for base classes (multiple inheritance)
    this->baseVtable1 = &PTR_LAB_00d5f3e0; // +0x3C (offset 0xF)
    this->baseVtable2 = &PTR_LAB_00d5f3dc; // +0x48 (offset 0x12)
    this->baseVtable3 = &PTR_LAB_00d5f3d8; // +0x50 (offset 0x14)
    this->baseVtable4 = &PTR_LAB_00d5f3d4; // +0x58 (offset 0x16)
    this->baseVtable5 = &PTR_LAB_00d5f3d0; // +0x58 (overwrites previous? Possibly a different base at same offset)

    // Initialize global flag (DAT_0112a878)
    g_someGlobal = 0;

    // Call base class constructor (FUN_00473880)
    BaseClass::constructor();

    // If allocation flag has bit 0 set, allocate memory for this object (size 0x230)
    if ((allocFlag & 1) != 0) {
        allocateMemory(this, 0x230); // FUN_0043b960 - likely custom memory allocation/initialization
    }

    return this;
}