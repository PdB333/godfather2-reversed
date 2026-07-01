// FUNC_NAME: SomeClass::destructor
void __thiscall SomeClass::destructor(SomeClass *this)
{
  // Set vtable pointer to the class's vtable
  this->vtable = &PTR_FUN_00d7d6bc;
  // Set function pointers at offsets 0x3C (0xF * 4) and 0x48 (0x12 * 4)
  this->field_0x3C = &PTR_LAB_00d7d6ac;
  this->field_0x48 = &PTR_LAB_00d7d6a8;
  // If the sub-object at offset 0x50 (0x14 * 4) exists, destroy it
  if (this->subObject != nullptr) {
    // Call destructor-like functions on the sub-object
    FUN_004086d0(&this->subObject);
    FUN_00408310(&this->subObject);
  }
  // Global cleanup function
  FUN_0046c640();
}