// FUNC_NAME: EARSObject::EARSObject
// Constructor at 0x0046d6a0 - initializes base object fields
void __fastcall EARSObject::EARSObject(EARSObject* this)
{
    this->vtable = (void*)0x00e32a8c; // +0x00: virtual function table pointer

    // Fields initialized with global value and sentinel -1
    this->field_0x04 = DAT_00e2b1a4;      // +0x04: copied from global
    this->field_0x08 = 0xFFFFFFFF;        // +0x08: -1 sentinel
    this->field_0x0C = 0xFFFFFFFF;        // +0x0C: -1 sentinel
    this->field_0x14 = 0;                 // +0x14: zeroed
    this->field_0x20 = DAT_00e2b1a4;      // +0x20: copied from global
    this->field_0x24 = 0;                 // +0x24: zeroed
}