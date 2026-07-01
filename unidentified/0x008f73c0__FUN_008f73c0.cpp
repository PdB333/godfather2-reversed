// FUNC_NAME: UnknownClass::UnknownClass
// Function address: 0x008f73c0
// Constructor for a class with multiple inheritance (vtables at offsets 0x0, 0x3C, 0x48)

void* __thiscall UnknownClass::UnknownClass(void* this, void* arg) {
    // Call base class constructor
    FUN_0083f8e0(arg);
    // Set primary vtable pointer at offset 0x0
    *(void**)this = &PTR_FUN_00d81254;
    // Set secondary vtable pointer at offset 0x3C (param_1[0xf])
    *(void**)((char*)this + 0x3C) = &PTR_LAB_00d81244;
    // Set tertiary vtable pointer at offset 0x48 (param_1[0x12])
    *(void**)((char*)this + 0x48) = &PTR_LAB_00d81240;
    // Call initialization function with argument 8
    FUN_0083f970(8);
    return this;
}