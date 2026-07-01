// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(SomeClass *this)
{
  this->vtable = &PTR_FUN_00d7775c;  // +0x00: vtable pointer
  this->field_0x3c = &PTR_LAB_00d7774c;  // +0x3C: some data pointer
  this->field_0x48 = &PTR_LAB_00d77748;  // +0x48: another data pointer
  subObject_initialize(&this->subObject);  // +0x50: initialize sub-object at offset 0x50 (0x14*4)
  subObject_clear(&this->subObject);  // +0x50: clear sub-object
  globalSingletonFunction();  // some global singleton function
}