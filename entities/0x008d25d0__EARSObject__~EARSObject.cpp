// FUNC_NAME: EARSObject::~EARSObject
// Address: 0x008d25d0
// Destructor: sets vtable pointer, then releases two sub-objects at offsets +0x28 and +0x3C

void __thiscall EARSObject::~EARSObject(EARSObject* this)
{
    // Set vtable pointer (likely to base class vtable or to indicate destruction)
    this->vtable = &PTR_FUN_00d7d3d8; // vtable pointer

    // Release sub-object at offset +0x3C (param_1[0xf])
    if (this->field_0x3C != 0) {
        FUN_009c8f10(this->field_0x3C); // likely deallocation function
    }

    // Release sub-object at offset +0x28 (param_1[10])
    if (this->field_0x28 != 0) {
        FUN_009c8f10(this->field_0x28);
    }

    return;
}