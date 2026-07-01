// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(SomeClass *this)
{
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d73040;
  // Initialize member at offset +0x3C (0xF * 4)
  this->field_0x3C = &PTR_LAB_00d73030;
  // Initialize member at offset +0x48 (0x12 * 4)
  this->field_0x48 = &PTR_LAB_00d7302c;
  // Call sub-constructor on member at offset +0x50 (0x14 * 4)
  subConstructor1(&this->field_0x50);
  // Call sub-initializer on member at offset +0x50
  subInitializer1(&this->field_0x50);
  // Call sub-initializer on member at offset +0x58 (0x16 * 4)
  subInitializer1(&this->field_0x58);
  // Register a callback or event handler with ID 0x1FF
  registerEventHandler(0x1ff, &this->field_0x3C);
  // Call a global initialization function
  globalInitFunction();
}