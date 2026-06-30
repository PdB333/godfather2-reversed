// FUNC_NAME: SomeClass::~SomeClass
void __fastcall SomeClass::destructor(undefined4* this) {
    // Set vtable to derived class vtable for proper virtual dispatch during destruction
    *this = &PTR_FUN_00d64720;
    // Free pointer at offset 0x10 (parameter at index 4)
    if (this[4] != 0) {
        Deallocate((void**)(this + 4));
    }
    // Free pointer at offset 0x4 (parameter at index 1)
    if (this[1] != 0) {
        Deallocate((void**)(this + 1));
    }
    // Restore vtable to base class vtable after derived cleanup
    *this = &PTR_LAB_00d64708;
}