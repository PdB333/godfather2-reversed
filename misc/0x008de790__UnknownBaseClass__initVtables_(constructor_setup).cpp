// FUNC_NAME: UnknownBaseClass::initVtables (constructor setup)
// Address: 0x008de790
// Sets up multiple vtable pointer fields and calls base class constructor at 0x008df8a0
// Likely part of a class with multiple inheritance or multiple virtual function tables.
// Offsets: 0x00 (vtable1), 0x3C (vtable2), 0x48 (vtable3), 0x50 (vtable4), 0x54 (vtable5), 0x58 (vtable6)

class UnknownBaseClass {
public:
    void __fastcall constructor() {
        // Set vtable pointer at offset 0x00
        *(void**)this = &PTR_FUN_00d7ec70;          // primary vtable

        // Set additional vtable-like pointers at various offsets
        *(void**)((char*)this + 0x3C) = &PTR_LAB_00d7ec60;   // +0x3C
        *(void**)((char*)this + 0x48) = &PTR_LAB_00d7ec5c;   // +0x48
        *(void**)((char*)this + 0x50) = &PTR_LAB_00d7ec58;   // +0x50
        *(void**)((char*)this + 0x54) = &PTR_LAB_00d7ebf8;   // +0x54
        *(void**)((char*)this + 0x58) = &PTR_LAB_00d7eb90;   // +0x58

        // Call base class (or further initialization) function
        FUN_008df8a0();
    }
};