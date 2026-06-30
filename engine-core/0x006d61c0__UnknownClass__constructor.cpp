// FUNC_NAME: UnknownClass::constructor
UnknownClass* __thiscall UnknownClass::constructor(UnknownClass* this, byte allocationFlag)
{
  // Set up virtual function table pointers
  this->vtable0 = (void*)&PTR_FUN_00d5f45c;   // +0x00: vtable pointer
  this->vtable3C = (void*)&PTR_LAB_00d5f44c;  // +0x3C (0xF*4): additional vtable
  this->vtable48 = (void*)&PTR_LAB_00d5f448;  // +0x48 (0x12*4): another vtable

  // Initialize sub-object at offset 0x14 (20 bytes)
  // This sub-object appears to be another base or member
  subObjectInit1((SubObjectType*)(this + 0x14)); // FUN_004086d0
  subObjectInit2((SubObjectType*)(this + 0x14)); // FUN_00408310

  // Global initialization call (likely engine-wide)
  globalInitialize(); // FUN_0046c640

  // If allocation flag has bit 0 set, deallocate this object (for placement new)
  if ((allocationFlag & 1) != 0) {
    operatorDelete(this, 0x6c); // FUN_0043b960 - size 108 bytes (0x6c)
  }

  return this;
}