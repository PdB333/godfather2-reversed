// FUNC_NAME: SomeClass::destructor

void __fastcall SomeClass::destructor(SomeClass *this)
{
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d6e258;
  this->field_0x3c = &PTR_LAB_00d6e248;  // +0x3C
  this->field_0x48 = &PTR_LAB_00d6e244;  // +0x48

  // Decrement global reference counter
  DAT_0112ba0c--;
  if (DAT_0112ba0c < 0) {
    DAT_0112ba0c = 0;
  }

  // Clean up various sub-objects (likely arrays or containers)
  FUN_004086d0(&this->field_0x50);  // +0x50
  FUN_00408310(&this->field_0x50);  // +0x50
  FUN_004086d0(&this->field_0x58);  // +0x58
  FUN_00408310(&this->field_0x58);  // +0x58
  FUN_004086d0(&this->field_0x6c);  // +0x6C
  FUN_00408310(&this->field_0x6c);  // +0x6C
  FUN_004086d0(&this->field_0x74);  // +0x74
  FUN_00408310(&this->field_0x74);  // +0x74
  FUN_00408310(&this->field_0x98);  // +0x98
  FUN_00408310(&this->field_0xa0);  // +0xA0

  // Clean up global object
  FUN_004086d0(&DAT_0120e93c);

  // Delete dynamically allocated objects
  if (this->field_0x80 != 0) {  // +0x80
    FUN_004daf90(&this->field_0x80);  // +0x80
  }
  if (this->field_0x64 != 0) {  // +0x64
    FUN_004daf90(&this->field_0x64);  // +0x64
  }

  // Final cleanup
  FUN_0046c640();
}