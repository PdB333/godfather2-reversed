// FUNC_NAME: EARSObject::Constructor
// Function address: 0x00598e10
// Role: Constructor for an EARS engine object, sets vtable pointer and zeroes four following fields.

void __thiscall EARSObject::Constructor(EARSObject *this)
{
  this->vtablePtr = (void *)&PTR_LAB_00e3b044; // +0x00
  this->field_0x04 = 0;                        // +0x04
  this->field_0x08 = 0;                        // +0x08
  this->field_0x0C = 0;                        // +0x0C
  this->field_0x10 = 0;                        // +0x10
}