// FUNC_NAME: UnknownClass::ctor
void __thiscall UnknownClass::ctor(UnknownClass* this) {
    // Set main vtable pointer at offset 0
    this->vtable = &PTR_FUN_00d60df8;

    // Set secondary vtable pointers for multiple inheritance (offsets in bytes *4)
    this->vtbl2 = &PTR_LAB_00d60de8;   // +0x3C
    this->vtbl3 = &PTR_LAB_00d60de4;   // +0x48
    this->vtbl4 = &PTR_LAB_00d60de0;   // +0x50
    this->vtbl5 = &PTR_LAB_00d60d80;   // +0x54
    this->vtbl6 = &PTR_LAB_00d60d18;   // +0x58

    // Call base class/subobject constructor (param 0xE likely class index)
    FUN_008f67c0(0xE, this);

    // Initialize subobject at offset 0x344 (0xD1 * 4)
    FUN_00408310(this + 0xD1);

    // Clean up a dynamically allocated pointer at offset 0x4F0 (0x13C * 4)
    if (this->ptr_0x13C != nullptr) {
        *(int*)(this->ptr_0x13C + 8) = 0;
        this->ptr_0x13C = nullptr;
    }

    // Final post-construct step (static/global function)
    FUN_00708830();
}