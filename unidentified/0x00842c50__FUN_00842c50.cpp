// FUNC_NAME: UnknownClass::UnknownClass
undefined4 * __thiscall UnknownClass::UnknownClass(undefined4 *this, byte param_2)
{
  // Call base class constructor (likely a common base for many EA objects)
  FUN_00598de0();
  
  // Set vtable pointer to class-specific vtable (at 0x00d74620)
  *this = &PTR_LAB_00d74620;
  
  // If param_2 has bit 0 set, call additional initialization (possibly placement new or subobject constructor)
  if ((param_2 & 1) != 0) {
    FUN_00840230(this);
  }
  
  return this;
}