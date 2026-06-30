// FUNC_NAME: BaseObject::BaseObject
// Function address: 0x00598e10
// Role: Constructor for a basic object, initializes vtable pointer and zeroes four following fields (offsets 0x4, 0x8, 0xC, 0x10)

void __fastcall BaseObject::BaseObject(BaseObject* this)
{
    this->vtable = &g_vtable_00e3b044; // +0x00: virtual function table pointer
    this->field_04 = 0;                // +0x04
    this->field_08 = 0;                // +0x08
    this->field_0C = 0;                // +0x0C
    this->field_10 = 0;                // +0x10
    return;
}