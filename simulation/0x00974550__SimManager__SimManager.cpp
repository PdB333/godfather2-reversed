// FUNC_NAME: SimManager::SimManager
undefined4 * __thiscall SimManager::SimManager(undefined4 *this, byte param_2)
{
  // Set vtable pointer at offset 0 (class vtable)
  *this = &PTR_FUN_00d8f668;
  // Set secondary vtable or interface pointer at offset 0x10
  this[4] = &PTR_LAB_00d8f640;
  // Set another pointer at offset 0x4C (first assignment, possibly base class)
  this[0x13] = &PTR_LAB_00d8f63c;
  // Override the same offset with derived class vtable
  this[0x13] = &PTR_LAB_00d8f638;
  // Clear global initialization flag
  DAT_01130010 = 0;
  // Call base initialization routine
  FUN_005c16e0();
  // If param_2 has bit 0 set, call additional cleanup/init function
  if ((param_2 & 1) != 0) {
    FUN_005c4480(this);
  }
  return this;
}