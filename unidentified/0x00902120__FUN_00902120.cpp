// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(SomeClass *this)
{
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d81c70;
  
  // Initialize member at offset 0x3C (0xF * 4)
  this->field_0x3C = &PTR_LAB_00d81c60;
  
  // Initialize member at offset 0x48 (0x12 * 4)
  this->field_0x48 = &PTR_LAB_00d81c5c;
  
  // Initialize sub-object at offset 0x58 (0x16 * 4)
  FUN_004086d0(&this->field_0x58);
  FUN_00408310(&this->field_0x58);
  
  // Initialize sub-object at offset 0x60 (0x18 * 4)
  FUN_004086d0(&this->field_0x60);
  FUN_00408310(&this->field_0x60);
  
  // Call some global initialization function
  FUN_0046c640();
}