// FUNC_NAME: UnknownClass::constructor_00721440
void __thiscall UnknownClass::constructor(UnknownClass *this)
{
  // +0x00: vtable pointer
  this->vtablePtr = &PTR_FUN_00d62028; // Set primary vtable
  // +0x3C (0xF * 4)
  this->field_0x3C = &PTR_LAB_00d62018;
  // +0x48 (0x12 * 4)
  this->field_0x48 = &PTR_LAB_00d62014;
  // +0x68 (0x1A * 4)
  this->field_0x68 = &PTR_LAB_00d62010;
  // Construct sub-object at +0x6C (0x1B * 4)
  subobject_constructor_004086d0(&this->field_0x6C);
  // Initialize sub-object at +0x6C
  subobject_initialize_00408310(&this->field_0x6C);
  // Overwrite field at +0x68
  this->field_0x68 = &PTR_LAB_00e32854;
  // Global initialization (e.g., register class, allocate)
  global_initialize_0099d180();
}