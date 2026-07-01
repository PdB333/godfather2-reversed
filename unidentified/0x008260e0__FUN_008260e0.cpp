// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(SomeClass *this)
{
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d734d4;
  
  // Initialize member pointers at offsets 0x3C (0xF * 4) and 0x48 (0x12 * 4)
  this->field_0x3C = &PTR_LAB_00d734c4;
  this->field_0x48 = &PTR_LAB_00d734c0;
  
  // Initialize sub-objects at offsets 0x58 (0x16 * 4), 0x60 (0x18 * 4), 0x68 (0x1A * 4)
  FUN_004086d0(&this->subObject1);  // +0x58 - likely some container/list initialization
  FUN_00408310(&this->subObject1);  // +0x58 - clear/reset
  FUN_00408310(&this->subObject2);  // +0x60 - clear/reset
  FUN_00408310(&this->subObject3);  // +0x68 - clear/reset
  
  // Call global initialization function
  FUN_0046c640();
}