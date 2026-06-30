// FUNC_NAME: SomeClass::constructor
// Address: 0x006f3210
// Reconstructed constructor for a Godfather 2 EARS object
// Object layout (offsets in bytes from start):
// +0x00: void* vtable
// +0x3C: void* (pointer to static data)
// +0x48: void* (pointer to static data)
// +0x58: sub-object 1 (size unknown)
// +0x60: sub-object 2 (size unknown)

void __fastcall SomeClass::constructor(void* self) {
    // Set vtable pointer
    *(void**)self = &PTR_FUN_00d605b8;
    // Set data pointers at offsets 0x3C and 0x48 (indices 0x0F and 0x12 in dword units)
    *(void**)((char*)self + 0x3C) = &PTR_LAB_00d605a8;
    *(void**)((char*)self + 0x48) = &PTR_LAB_00d605a4;

    // Local copy of self for base class initialization trick
    void* selfRef = self;
    FUN_006f2ea0(&selfRef); // likely constructBase (placement new / vtable setup)

    // Initialize sub-object 1 at offset 0x58
    FUN_004086d0((char*)self + 0x58); // constructSubObject1
    FUN_00408310((char*)self + 0x58); // initSubObject1

    // Initialize sub-object 2 at offset 0x60
    FUN_004086d0((char*)self + 0x60); // constructSubObject2
    FUN_00408310((char*)self + 0x60); // initSubObject2

    // Global initialization (e.g., register with manager)
    FUN_0046c640();
}