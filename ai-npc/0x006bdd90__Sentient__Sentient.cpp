// FUNC_NAME: Sentient::Sentient
undefined4 * __thiscall Sentient::Sentient(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor (likely Entity or EARSObject)
  FUN_006bd1d0(param_2);

  // Set vtable pointer
  *this = &PTR_FUN_00d5eaec;

  // Set secondary vtable pointers (multiple inheritance)
  this[0xf] = &PTR_LAB_00d5eadc;  // +0x3C (offset 60) - likely IEntity interface
  this[0x12] = &PTR_LAB_00d5ead8; // +0x48 (offset 72) - likely ICombat interface

  // Initialize various fields to zero
  this[0x20] = 0;                // +0x80 - e.g., mHealth
  *(undefined2 *)(this + 0x21) = 0; // +0x84 - 16-bit field, e.g., mArmor
  *(undefined2 *)((int)this + 0x86) = 0; // +0x86 - 16-bit field, e.g., mFlags
  this[0x25] = 0;                // +0x94 - e.g., mScore
  this[0x24] = 0;                // +0x90 - e.g., mExperience
  this[0x23] = 0;                // +0x8C - e.g., mKillCount
  this[0x22] = 0;                // +0x88 - e.g., mDamageTaken

  return this;
}