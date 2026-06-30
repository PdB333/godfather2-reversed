// FUNC_NAME: Sentient::Sentient
undefined4 * __thiscall Sentient::Sentient(undefined4 *this, byte allocFlag)
{
  // Set primary vtable pointer (offset 0x00)
  *this = &PTR_FUN_00d5f100;
  // Set secondary vtable pointer (offset 0x3C = 0xF * 4)
  this[0xF] = &PTR_LAB_00d5f0f0;
  // Set tertiary vtable pointer (offset 0x48 = 0x12 * 4)
  this[0x12] = &PTR_LAB_00d5f0ec;
  // Call base class constructor (likely Entity or common base)
  FUN_0046c640();
  // If allocation flag bit 0 is set, allocate memory for this object (size 0x50)
  if ((allocFlag & 1) != 0) {
    FUN_0043b960(this, 0x50);
  }
  return this;
}