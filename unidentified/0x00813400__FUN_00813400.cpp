// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(SomeClass *this)
{
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d72ff4;
  // Set additional function pointers at offsets +0x3C and +0x48
  this->field_0x3C = &PTR_LAB_00d72fe4;  // +0x3C
  this->field_0x48 = &PTR_LAB_00d72fe0;  // +0x48

  // Call base class constructor
  FUN_00812e60(this);

  // Initialize some subsystem
  FUN_00813260(0);

  // Initialize two pairs of objects at offsets +0x50 and +0x58
  FUN_004086d0(this + 0x14);  // +0x50
  FUN_00408310(this + 0x14);  // +0x50
  FUN_004086d0(this + 0x16);  // +0x58
  FUN_00408310(this + 0x16);  // +0x58

  // Call function with value at offset +0x60
  FUN_009c8f10(this->field_0x60);  // +0x60

  // Initialize some global/system
  FUN_0046c640();
}