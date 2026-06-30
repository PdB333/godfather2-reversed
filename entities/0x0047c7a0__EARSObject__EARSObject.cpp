// FUNC_NAME: EARSObject::EARSObject
void __thiscall EARSObject::EARSObject(EARSObject *this)
{
  // Set primary vtable
  *this = &PTR_FUN_00e331b0;               // +0x00: primary vtable
  // Set secondary vtable at offset 0x3C (0xF * 4)
  this->field_0x3C = &PTR_LAB_00e331d0;    // +0x3C: secondary vtable
  // Set tertiary vtable at offset 0x48 (0x12 * 4)
  this->field_0x48 = &PTR_LAB_00e331e0;    // +0x48: tertiary vtable
  // Initialize sub-object at offset 0x14 (inherited base class or data)
  FUN_004086d0(&this->subObject_0x14);      // likely a string/array initializer
  FUN_00408310(&this->subObject_0x14);      // completes sub-object init
  // Global singleton or static initialization
  FUN_0046c640();                           // e.g., register object, increment counter
}