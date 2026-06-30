// FUNC_NAME: SimNpc::~SimNpc
// Function at 0x006dc600: Destructor for SimNpc class.
// Sets vtables to base class, frees two sub-objects at offsets 0xC8 and 0xC0,
// then calls a global cleanup function.

void __fastcall SimNpc::~SimNpc(SimNpc* this)
{
    // Set vtable pointers to base class vtables to ensure correct virtual dispatch during destruction
    this->vtable = &vtable_00d5f6a4;         // +0x00: First vtable pointer
    this->secondVtable = &secondVtable_00d5f69c; // +0x08: Second vtable pointer (multiple inheritance)

    // Free two dynamically allocated sub-objects if they exist
    if (this->field_0xC8 != 0) {           // +0xC8: Pointer to sub-object
        safeDeletePointer(&this->field_0xC8); // FUN_004daf90
    }
    if (this->field_0xC0 != 0) {           // +0xC0: Pointer to sub-object
        safeDeletePointer(&this->field_0xC0); // FUN_004daf90
    }

    // Global cleanup call specific to the engine
    someGlobalCleanup();                     // FUN_006c9820
}